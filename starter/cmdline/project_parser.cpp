
#include "project_parser.h"
#include <iostream>
#include <map>
#include <signal.h>
#include <unistd.h>
#include <thread>
#include "backend_cmdline/roviz_item_base_cmdline.h"
#include "backend_cmdline/config_impl_base_cmdline.h"

bool ProjectParser::parseProject(const std::string &pro_file, const ItemLoader &loader)
{
    tinyxml2::XMLDocument doc;

    doc.LoadFile(pro_file.c_str());
    if(doc.ErrorID())
    {
        roviz::logger->critical("Cannot open file {}", pro_file);
        return false;
    }

    tinyxml2::XMLElement *project = doc.RootElement();
    if(project == nullptr)
    {
        roviz::logger->critical("Project file is not in XML format", pro_file);
        return false;
    }

    if(!this->loadItems(project, loader))
        return false;

    if(!this->loadConnections(project))
        return false;

    for(auto &item : this->items)
        item.second->start();

    return true;
}

void ProjectParser::exec()
{
    std::thread sig_check(&ProjectParser::signalChecker, *this);

    for(auto &item : this->items)
        item.second->join();

    kill(::getpid(), SIGINT);
}

void ProjectParser::signalChecker()
{
    sigset_t signal_mask;
    int sig_caught;

    sigemptyset(&signal_mask);
    sigaddset(&signal_mask, SIGINT);
    sigaddset(&signal_mask, SIGKILL);

    sigwait(&signal_mask, &sig_caught);

    for(auto &item : this->items)
        item.second->stop();
}

bool ProjectParser::loadItems(tinyxml2::XMLElement *project, const ItemLoader &loader)
{
    int id;
    RovizItemBaseCmdline *item;
    tinyxml2::XMLElement *xml_item = project->FirstChildElement("GraphicsItem");
    tinyxml2::XMLElement *xml_top_item = xml_item;

    do
    {
        // We have to do that before or the goto's will fail
        const char *id_cstr = xml_item->Attribute("id");
        const char *type_cstr = xml_item->Attribute("type");

        if(id_cstr == nullptr)
        {
            roviz::logger->critical("Project file is invalid (item without ID)");
            return false;
        }
        id = atoi(id_cstr);

        if(type_cstr == nullptr)
        {
            roviz::logger->cirtical("Projcet file is invalid (item without type)");
            return false;
        }

        item = loader.newItem(type_cstr);
        if(item == nullptr)
        {
            roviz::logger->critical("Plugin not found ({})", type_cstr);
            return false;
        }

        items[id] = item;

        xml_item = xml_item->FirstChildElement("GraphicsItemData");
        if(xml_item != nullptr)
        {
            xml_item = xml_item->FirstChildElement("SettingsScope");
            if(xml_item != nullptr)
            {
                if(!this->loadTrimsAndConfigs(xml_item, item))
                {
                    roviz::logger->critical("Failed to load trims and configs for item ",type_cstr);
                    return false;
                }
            }
        }

        xml_item = xml_top_item->NextSiblingElement("GraphicsItem");
        xml_top_item = xml_item;
    } while(xml_item);

    return true;
}

bool ProjectParser::loadConnections(tinyxml2::XMLElement *project)
{
    tinyxml2::XMLElement *item = project->FirstChildElement("GraphicsItemConnector");
    if(item == nullptr)
    {
        roviz::logger->warn("No connections found");
        return false;
    }

    do
    {
        const char *from_cstr = item->Attribute("fromItem");
        if(from_cstr == nullptr)
        {
            roviz::logger->critical("Malformed connection");
            return false;
        }
        int from = atoi(from_cstr);

        const char *to_cstr = item->Attribute("toItem");
        if(to_cstr == nullptr)
        {
            roviz::logger->critical("Malformed connection");
            return false;
        }
        int to = atoi(to_cstr);

        const char *output_cstr = item->Attribute("fromIndex");
        if(output_cstr == nullptr)
        {
            roviz::logger->critical("Malformed connection");
            return false;
        }

        int output = atoi(output_cstr);
        if(output >= (int)items.size())
        {
            roviz::logger->critical("Malformed connection");
            return false;
        }

        const char *input_cstr = item->Attribute("toIndex");
        if(input_cstr == nullptr)
        {
            roviz::logger->critical("Malformed connection");
            return false;
        }

        int input = atoi(input_cstr);
        if(input >= (int)items.size())
        {
            roviz::logger->critical("Malformed connection");
            return false;
        }

        if(!items[to]->connect(input, items[from], output))
        {
            roviz::logger->critical("Connection failed");
            return false;
        }

    } while((item = item->NextSiblingElement("GraphicsItemConnector")));

    return true;
}

bool ProjectParser::loadTrimsAndConfigs(tinyxml2::XMLElement *xml_ss, RovizItemBaseCmdline *item)
{
    tinyxml2::XMLElement *xml_setting = xml_ss->FirstChildElement("Setting");
    if(xml_setting == nullptr)
    {
        roviz::logger->critical("Malformed setting");
        return false;
    }

    do
    {
        const char *name_cstr = xml_setting->Attribute("name");
        if(name_cstr == nullptr)
        {
            roviz::logger->critical("Malformed settings (no name)");
            return false;
        }
        std::string name = name_cstr;

        if(name.substr(0, 5) == "Trim/")
        {
            name = name.substr(5);

            const char *value_cstr = xml_setting->Attribute("value");
            if(value_cstr == nullptr)
            {
                roviz::logger->critical("Malformed trim (no value)");
                return false;
            }

            double value = atof(value_cstr);

            item->setTrim(name, value);
        }
        else if(name.substr(0, 7) == "Config/")
        {
            name = name.substr(7);

            const char *value_cstr = xml_setting->Attribute("value");
            if(value_cstr == nullptr)
            {
                roviz::logger->critical("Malformed config (no value)");
                return false;
            }

            // Get rid of the type, we don't need that
            name.erase(0, name.find('/') + 1);

            auto config = item->_this_base->configs.find(name);
            if(config == item->_this_base->configs.cend())
            {
                roviz::logger->critical("Config not found for item");
                return false;
            }

            config->second->load(value_cstr);
        }
    } while((xml_setting = xml_setting->NextSiblingElement("Setting")));

    return true;
}

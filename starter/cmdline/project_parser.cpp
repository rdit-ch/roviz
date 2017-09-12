
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
        std::cout << "Error: Cannot open file " << pro_file << std::endl;
        return false;
    }

    tinyxml2::XMLElement *project = doc.RootElement();
    if(project == nullptr)
    {
        std::cout << "Error: Project file is not in XML format" << std::endl;
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
            std::cout << "Error: Project file is invalid (item without ID)" << std::endl;
            return false;
        }
        id = atoi(id_cstr);

        if(type_cstr == nullptr)
        {
            std::cout << "Error: Projcet file is invalid (item without type)" << std::endl;
            return false;
        }

        item = loader.newItem(type_cstr);
        if(item == nullptr)
        {
            std::cout << "Error: Plugin not found (" << type_cstr << ")" << std::endl;
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
                    std::cout << "Error: Failed to load trims and configs for item " << type_cstr << std::endl;
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
        std::cout << "Error: No connections found (this is kinda useless)" << std::endl;
        return false;
    }

    do
    {
        const char *from_cstr = item->Attribute("fromItem");
        if(from_cstr == nullptr)
        {
            std::cout << "Error: Malformed connection" << std::endl;
            return false;
        }
        int from = atoi(from_cstr);

        const char *to_cstr = item->Attribute("toItem");
        if(to_cstr == nullptr)
        {
            std::cout << "Error: Malformed connection" << std::endl;
            return false;
        }
        int to = atoi(to_cstr);

        const char *output_cstr = item->Attribute("fromIndex");
        if(output_cstr == nullptr)
        {
            std::cout << "Error: Malformed connection" << std::endl;
            return false;
        }

        int output = atoi(output_cstr);
        if(output >= (int)items.size())
        {
            std::cout << "Error: Malformed connection" << std::endl;
            return false;
        }

        const char *input_cstr = item->Attribute("toIndex");
        if(input_cstr == nullptr)
        {
            std::cout << "Error: Malformed connection" << std::endl;
            return false;
        }

        int input = atoi(input_cstr);
        if(input >= (int)items.size())
        {
            std::cout << "Error: Malformed connection" << std::endl;
            return false;
        }

        if(!items[to]->connect(input, items[from], output))
        {
            std::cout << "Error: Connection failed" << std::endl;
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
        std::cout << "Error: Malformed setting" << std::endl;
        return false;
    }

    do
    {
        const char *name_cstr = xml_setting->Attribute("name");
        if(name_cstr == nullptr)
        {
            std::cout << "Error: Malformed settings (no name)" << std::endl;
            return false;
        }
        std::string name = name_cstr;

        if(name.substr(0, 5) == "Trim/")
        {
            name = name.substr(5);

            const char *value_cstr = xml_setting->Attribute("value");
            if(value_cstr == nullptr)
            {
                std::cout << "Error: Malformed trim (no value)" << std::endl;
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
                std::cout << "Error: Malformed config (no value)" << std::endl;
                return false;
            }

            // Get rid of the type, we don't need that
            name.erase(0, name.find('/') + 1);

            auto config = item->_this_base->configs.find(name);
            if(config == item->_this_base->configs.cend())
            {
                std::cout << "Error: Config not found for item" << std::endl;
                return false;
            }

            config->second->load(value_cstr);
        }
    } while((xml_setting = xml_setting->NextSiblingElement("Setting")));

    return true;
}

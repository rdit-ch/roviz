
#include "config_message_test_item.h"

#include <iostream>

ConfigMessageTestItem::ConfigMessageTestItem()
    : RovizItem("ConfigMessageTest")
{
    ROVIZ_INIT_ITEM(ConfigMessageTest);

    this->output = this->addOutput<Message>("Output");

    std::function<bool (std::string&)> checker = [](std::string &str)
    {
        if(str == "Hello" || str == "World")
            return true;
        else
            return false;
    };

    this->list_values = { "1", "Two", "3.0" };

    this->conf_int = this->addConfig<int>("Int (0-100)", 50, 0, 100, false);
    this->conf_double = this->addConfig<double>("Double (-1-1)", 0., -1., 1., false);
    this->conf_string = this->addConfig<std::string>("String (Hello/World)", "Hello", checker, false);
    this->conf_list = this->addConfig<std::vector<std::string> >("List (1, Two, 3.0)", 0, this->list_values, false);
    this->conf_bool = this->addConfig<bool>("Bool", false, false);

    this->conf_path_any = this->addConfig<FilePath>("Path Any (*)", {""}, FilePath::AnyFile, "All File (*)", true);
    this->conf_path_dir = this->addConfig<FilePath>("Path Dir (*)", {""}, FilePath::Directory, "All Files (*)", true);
    this->conf_path_ex = this->addConfig<FilePath>("Path Ex (*.png)", {""}, FilePath::ExistingFile, "PNG Images (*.png)", true);
    this->conf_path_mult = this->addConfig<FilePath>("Path Mult (*.c, *.h)", {""}, FilePath::MultipleFiles, "C-Files (*.c, *.h)", true);
}

ConfigMessageTestItem::~ConfigMessageTestItem()
{
    this->stop();
}

void ConfigMessageTestItem::thread()
{
    std::cout << "Config/Message test started" << std::endl;

    while(this->wait())
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        MessageMutable msg("Config/Message Test", {}, 9);

        msg.append("Int", this->conf_int.value());
        msg.append("Double", this->conf_double.value());
        msg.append("String", this->conf_string.value());
        msg.append("List", this->list_values[this->conf_list.value()]);
        msg.append("Bool", this->conf_bool.value());

        msg.append("Path/Any", listToString(this->conf_path_any.value()));
        msg.append("Path/Directories", listToString(this->conf_path_dir.value()));
        msg.append("Path/Existing Files", listToString(this->conf_path_ex.value()));
        msg.append("Path/Multiple Files", listToString(this->conf_path_mult.value()));

        this->output.pushOut(msg);
    }

    std::cout << "Config/Message test stopped" << std::endl;
}

std::string ConfigMessageTestItem::listToString(const std::vector<std::string> &list)
{
    std::string out;

    for(const auto &element : list)
        out.append(element + "; ");

    // Truncate the "; " at the end
    out.erase(out.cend() - 2, out.cend());

    return out;
}

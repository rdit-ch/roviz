
#include <iostream>
#include <errno.h>
#include "item_loader.h"
#include "project_parser.h"
#include "core/logger.h"

int main(int argc, char **argv)
{
    ItemLoader loader;
    ProjectParser parser;

    roviz::initLogger();

    if(argc != 2 && argc != 4)
    {
        roviz::logger->critical("No project file specified");;
        return -EINVAL;
    }

    if(argc == 4 && std::string(argv[1]) == "-p")
    {
        if(!loader.load(argv[2]))
        {
            roviz::logger->critical("Failed to load plugins from {}", argv[2]);
            return -EINVAL;
        }

        if(!parser.parseProject(argv[3], loader))
        {
            roviz::logger->critical("Failed to parse project file {}", argv[3]);
            return -EINVAL;
        }
    }
    else
    {
        if(!loader.load("/usr/lib/roviz/cmdline", true))
        {
            if(!loader.load("/usr/local/lib/roviz/cmdline"))
            {
                roviz::logger->critical("Failed to load plugins from default plugin directory");
                return -EINVAL;
            }
        }

        if(!parser.parseProject(argv[1], loader))
        {
            roviz::logger->critical("Failed to parse project file {}", argv[3]);
            return -EINVAL;
        }
    }

    parser.exec();

    return 0;
}


#include <iostream>
#include <errno.h>
#include "item_loader.h"
#include "project_parser.h"

int main(int argc, char **argv)
{
    ItemLoader loader;
    ProjectParser parser;

    if(argc != 2 && argc != 4)
    {
        std::cout << "Error: Please specify a project file to parse" << std::endl;
        return -EINVAL;
    }

    if(argc == 4 && std::string(argv[1]) == "-p")
    {
        if(!loader.load(argv[2]))
            return -EINVAL;

        if(!parser.parseProject(argv[3], loader))
            return -EINVAL;
    }
    else
    {
        if(!loader.load("/usr/lib/roviz/cmdline", true))
            if(!loader.load("/usr/local/lib/roviz/cmdline"))
                return -EINVAL;

        if(!parser.parseProject(argv[1], loader))
            return -EINVAL;
    }

    parser.exec();

    return 0;
}

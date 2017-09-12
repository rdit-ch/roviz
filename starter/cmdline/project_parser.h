#ifndef PROJECT_PARSER_H
#define PROJECT_PARSER_H

#include <string>
#include <tinyxml2.h>
#include "item_loader.h"

class ProjectParser
{
public:
    enum Error {
        NoError,
        XMLErrorOpenDocument,
        XMLErrorParseNoProject,
        PluginErrorNotFound,
        UserInterrupted
    };

    bool parseProject(const std::string &pro_file, const ItemLoader &loader);
    void exec(void);
    void signalChecker(void);

private:
    std::map<int, RovizItemBaseCmdline*> items;

    bool loadItems(tinyxml2::XMLElement *project, const ItemLoader &loader);
    bool loadConnections(tinyxml2::XMLElement *project);
    bool loadTrimsAndConfigs(tinyxml2::XMLElement *xml_ss, RovizItemBaseCmdline *item);
};

#endif // PROJECT_PARSER_H

#ifndef ROVIZ_ITEM_BASE_CMDLINE_P_H
#define ROVIZ_ITEM_BASE_CMDLINE_P_H

#include <map>
#include <vector>
#include <string>

namespace roviz
{

class ConfigImplBaseCmdline;
class TrimImplCmdline;
class InputPrivate;
class OutputPrivate;

/**
 * @brief Private part of RovizItemBaseCmdline
 *
 * \sa RovizItemBaseCmdline
 */
class ItemBaseCmdlinePrivate
{
public:
    std::vector<InputPrivate*> inputs;
    std::vector<OutputPrivate*> outputs;
    std::map<std::string, TrimImplCmdline*> trims;
    std::map<std::string, ConfigImplBaseCmdline*> configs;
};

}

#endif // ROVIZ_ITEM_BASE_CMDLINE_P_H

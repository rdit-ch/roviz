#ifndef ITEM_LOADER_H
#define ITEM_LOADER_H

#include <string>
#include <list>
#include <map>
#include <functional>

namespace roviz
{
    class ItemBaseCmdline;
}

class ItemLoader
{
public:
    ItemLoader() = default;
    ~ItemLoader();
    bool load(std::string path, bool silent = false);
    roviz::ItemBaseCmdline *newItem(const std::string type) const;

private:
    std::map<std::string, roviz::ItemBaseCmdline *(*)()> factories;
    std::list<void*> lib_handles;
};

#endif // ITEM_LOADER_H

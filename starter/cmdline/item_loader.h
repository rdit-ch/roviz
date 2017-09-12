#ifndef ITEM_LOADER_H
#define ITEM_LOADER_H

#include <string>
#include <list>
#include <map>
#include <functional>

class RovizItemBaseCmdline;

class ItemLoader
{
public:
    ItemLoader() = default;
    ~ItemLoader();
    bool load(std::string path, bool silent = false);
    RovizItemBaseCmdline *newItem(const std::string type) const;

private:
    std::map<std::string, RovizItemBaseCmdline *(*)()> factories;
    std::list<void*> lib_handles;
};

#endif // ITEM_LOADER_H

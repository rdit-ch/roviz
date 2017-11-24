
#include "item_loader.h"
#include <iostream>
#include "core/roviz_item.h"
#include "core/logger.h"

#ifdef _WIN32
    #error Windows not supported yet
#else
    #include <dlfcn.h>
    #include <sys/types.h>
    #include <dirent.h>
#endif

ItemLoader::~ItemLoader()
{
    for(const auto &lib_handle : this->lib_handles)
        dlclose(lib_handle);
}

bool ItemLoader::load(std::string path, bool silent)
{
#ifdef _WIN32
    #error Windows is not supported yet
#else
    struct dirent *file;
    DIR *dir = opendir(path.c_str());
    if(dir == nullptr)
    {
        if(!silent)
            roviz::logger->critical("Could not open plugin directory ({})", path);
        return false;
    }

    while((file = readdir(dir)))
    {
        std::string libpath = path + "/" + file->d_name;
        void *lib_handle = dlopen(libpath.c_str(), RTLD_LAZY);
        if(lib_handle == nullptr)
            continue;

        const char **name_ptr = (const char**)dlsym(lib_handle, "rovizItemName");
        if(name_ptr == nullptr)
            goto fail;

        roviz::ItemBaseCmdline *(*fn)();
        *(void**)(&fn) = dlsym(lib_handle, "rovizItemFactory");
        if(fn == nullptr)
            goto fail;

        // Not exactly safe, but we're going to run an arbitrary function that the plugin
        // provides, so we have to trust the plugin anyway
        this->factories[*name_ptr] = fn;
        this->lib_handles.push_back(lib_handle);

        continue;

fail:   dlclose(lib_handle);
        roviz::logger->warn("Invalid plugin ({})", libpath);
    }
#endif

    return true;
}

roviz::ItemBaseCmdline *ItemLoader::newItem(const std::string type) const
{
    auto factory = this->factories.find(type);
    if(factory == this->factories.end())
        return nullptr;

    return factory->second();
}

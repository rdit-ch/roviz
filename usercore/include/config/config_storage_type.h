#ifndef CONFIG_STORAGE_TYPE_H
#define CONFIG_STORAGE_TYPE_H

#include "config/file_path.h"

/**
 * @brief Class that connects a type that can be stored in a config and it's
 * value type.
 *
 * Example: list<string> is a class that can be used as a config, but it's value
 * is of type int, because we only store the current index and not the whole
 * list.
 *
 * \sa Config
 * \sa FilePath
 */
template<typename T>
class ConfigStorageType
{ public: typedef T type;};

template<>
class ConfigStorageType<std::list<std::string> >
{ public: typedef int type; };

template<>
class ConfigStorageType<FilePath>
{ public: typedef std::list<std::string> type; };

#endif // CONFIG_STORAGE_TYPE_H

#ifndef FILE_PATH_H
#define FILE_PATH_H

#include "core/export_handling.h"

namespace roviz
{

/**
 * @brief Class used as a tag for file paths
 *
 * A string and a file path are basically the same thing, but they have
 * different meanings and widgets for a config. You can use this as the type
 * for a config and you'll get a nice file-selector widget. The value of the
 * config will be a string list (because you can select multiple file).
 *
 * \sa Config
 * \sa ConfigStorageType
 */
class ROVIZ_EXPORT FilePath
{
COPY_DEFAULT(FilePath)
MOVE_DEFAULT(FilePath)

public:
    FilePath() = default;
    ~FilePath() = default;

    enum Mode
    {
        AnyFile,
        ExistingFile,
        MultipleFiles,
        Directory
    };
};

}

#endif // FILE_PATH_H

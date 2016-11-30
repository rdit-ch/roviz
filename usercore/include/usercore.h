#ifndef USERCORE_H
#define USERCORE_H

#include <QtGlobal>

/**
 * @brief The USERCORE_EXPORT sets the correct dllexport/dllimport attribute on classes on the core that should be exported.
 * All Classes in the usercore which are part of the Public API must have this Macro after the class/struct keyword.
 * Exception: Classes which are header-only and have no Q_OBJECT or Q_GADGET macro
 */
#if defined USERCORE_BUILD
#define USERCORE_EXPORT Q_DECL_EXPORT
#else
#define USERCORE_EXPORT Q_DECL_IMPORT
#endif

#define USERCORE_TEST_EXPORT USERCORE_EXPORT

#include "usercore.h"

struct USERCORE_EXPORT LinkerHelper
{
    static void ensureUserCoreGetsLinked();
};

#endif // USERCORE_H


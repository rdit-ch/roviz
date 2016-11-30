#ifndef ROBOT_CORE_GLOBAL_H
#define ROBOT_CORE_GLOBAL_H

#include <QtCore/qglobal.h>

/** \mainpage roviz
 *
 * This is a combined documentation of the roviz framework and the itemframework.
 * If you would like to start writing a plugin for the roviz framework, have
 * a look at the overeview of the Robot Framework under 'Modules'. You can
 * also find out more about the itemframework under 'Related Pages'. You can
 * find a short description of the project and its source code under
 * https://github.com/rdit-ch/roviz
 *
 */

#if defined(ROBOT_CORE_LIBRARY)
#  define ROBOTCORE_EXPORT Q_DECL_EXPORT
#else
#  define ROBOTCORE_EXPORT Q_DECL_IMPORT
#endif

#endif // ROBOT_CORE_GLOBAL_H

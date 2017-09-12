#ifndef TYPEDECL_H
#define TYPEDECL_H

#include <string>
#include "core/strong_typedef.h"

class ItemInput;
class ItemOutput;
class QSlider;

struct InputTag{};
struct OutputTag{};

#ifdef ROVIZ_EXPORT
// Insert the typdefs for the exported case here
#else
/**
 * @brief Input of an RovizItem
 *
 * \sa RovizItem
 */
typedef StrongTypedef<InputTag, ItemInput*, nullptr> Input;

/**
 * @brief Output of an RovizItem
 *
 * \sa RovizItem
 */
typedef StrongTypedef<OutputTag, ItemOutput*, nullptr> Output;

class RovizItem;
/**
 * @brief Use RovizItemNoExport for simulation-only items
 *
 * This type will be undefined when exporting, making it easier to detect
 * the error when trying to export a simulation-only item.
 *
 * \sa RovizItem
 */
typedef RovizItem RovizItemNoExport;
#endif

#endif // TYPEDECL_H

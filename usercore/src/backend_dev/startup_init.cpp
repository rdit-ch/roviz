
#include "backend_dev/startup_init.h"

#include <map>
#include <string>
#include <QColor>
#include "item/abstract_item.h"
#include "helper/startup_helper.h"
#include "core/template_decl.h"
#include "streams/all_streams.h"

/*
 * We use a little trick here to assign the colors. Out macro only gets
 * one argument (the type of the stream) and somehow has to get a color
 * for that type. Because we can't map that directly, we first convert
 * the typename to a string and then we use a string map to get the
 * corresponding color. This prevents a lot of duplication and if you
 * add a stream without specifying its color, it won't fail horribly.
 * The only thing that happens is that the key is not found in the map
 * and thus the color will default to black.
 */

static const std::map<std::string, QColor> colors =
{
    { "Image",            Qt::green },
    { "Message",          Qt::red   },
    { "Sparse<Point2D>",  Qt::blue  },
    { "Sparse<Point2F>",  Qt::blue  },
    { "Sparse<Point3D>",  Qt::blue  },
    { "Sparse<Point3F>",  Qt::blue  },
    { "Sparse<Rect>",     Qt::blue  },
    { "Sparse<RectF>",    Qt::blue  },
    { "Sparse<Circle>",   Qt::blue  },
    { "Sparse<CircleF>",  Qt::blue  },
};

#define STRINGIFY_P(T)  #T
#define STRINGIFY(T)    STRINGIFY_P(T)

#define REGISTER_CONNECTOR(color, T)  AbstractItem::registerConnectorStyle(color, qMetaTypeId<T>());
#define REGISTER_CONNECTOR_COLOR(T)   REGISTER_CONNECTOR(colors.at(STRINGIFY(T)), T)

// With this, the itemframework will call the init function on startup
STARTUP_ADD_COMPONENT(StartupInit)

void StartupInit::init()
{
    DO_FOR_ALL_STREAMS(REGISTER_CONNECTOR_COLOR)
}

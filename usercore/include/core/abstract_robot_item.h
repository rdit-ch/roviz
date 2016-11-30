#ifndef ABSTRACTROBOTITEM_H
#define ABSTRACTROBOTITEM_H

#include <QObject>
#include <QLabel>
#include <QSlider>
#include <QImage>
#include <QLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSignalMapper>
#include <QMap>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QScopedPointer>
#include <QMenu>
#include "gui/gui_manager.h"
#include "item/abstract_item.h"
#include "gui/shared_window.h"
#include "gui/slider_label.h"
#include "gui/image_widget.h"
#include "helper/settings_scope.h"
#include "item/item_input.h"
#include "item/item_output.h"
#include "core/image_stream.h"
#include "core/stream_to_image_input_mapper.h"
#include "core/stream_to_message_input_mapper.h"
#include "gui/config_dialog.h"
#include "core/message_stream.h"

class AbstractRobotItemPrivate;

// To be able to be the base class of PortableItem
class AbstractRobotItem;
typedef AbstractRobotItem PortableItemBase;

/**
 * @brief Base class that binds PortableItem to traviz/Qt
 * \ingroup robot_framework
 */
class ROBOTCORE_EXPORT AbstractRobotItem : public AbstractItem
{
    Q_OBJECT
    friend class AbstractRobotItemPrivate;

public:
    explicit AbstractRobotItem(std::string typeName);
    virtual ~AbstractRobotItem();

    /**
     * @return The main widget of the item
     *
     * Can be overwritten to show a custom widget. (Enclose in #ifdef QT_PRESENT when overriding)
     *
     * \sa SharedWindow
     */
    virtual QWidget *widget(void);

    /**
     * @name Interface implementation
     *
     * Implementation of the interface that PortableItem demands.
     * See the documentation of PortableItem to see what these functions
     * do.
     */
    ///@{
protected:
    virtual bool running(void) = 0;
    virtual void *addImageInput(std::string name);
    virtual void *addImageOutput(std::string name);
    virtual void pushImageOut(const PortableImage img, void *output);
    virtual void *addTrim(std::string name, int min, int max);
    virtual void *addTrim(std::string name, double min, double max, int steps);
    virtual double trimValue(void *trim);
    virtual void trimChanged(void *trim, double value);
    virtual void addConfig(std::string name, std::string *value, std::function<std::string (std::string)> checker = [](std::string a){return a;});
    virtual void addConfig(std::string name, int *value, std::function<int (int)> checker = [](int a){return a;});
    virtual void addConfig(std::string name, double *value, std::function<double (double)> checker = [](double a){return a;});
    virtual void addConfig(std::string name, bool *value);
    virtual void addConfig(std::string name, std::vector<std::string> possibilities, int *index);
    virtual void *addMessageOutput(std::string name);
    virtual void *addMessageInput(std::string name);
    virtual void outputMessage(void *output, Message message);

public slots:
    virtual void start(void);
    virtual void stop(void);
    void restart(void);
    virtual void pause(void) = 0;
    virtual void unpause(void) = 0;

protected slots:
    virtual void pushImageIn(const PortableImage img, void *input) = 0;
    virtual void newMessageReceived(void *input, Message message) = 0;
    ///@}

protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override;
    void contextMenuPrepare(QMenu &menu) const override;

private:
    QScopedPointer<AbstractRobotItemPrivate> _this;
};

#endif // ABSTRACTROBOTITEM_H

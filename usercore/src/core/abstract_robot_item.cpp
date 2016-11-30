
#include "core/abstract_robot_item.h"
#include "core/abstract_robot_item_p.h"

AbstractRobotItem::AbstractRobotItem(std::string typeName)
    : AbstractItem(QString::fromStdString(typeName)),
      _this(new AbstractRobotItemPrivate(this))
{
    _this->main_widget = new QWidget();
    _this->main_layout = new QHBoxLayout();
    _this->main_control_layout = new QHBoxLayout();
    _this->main_image_layout = new QHBoxLayout();
    _this->control_base = new QWidget();
    _this->collapse_btn = new QPushButton();
    QHBoxLayout *hlayout = new QHBoxLayout();

    _this->control_base->setLayout(_this->main_control_layout);
    _this->collapse_btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    _this->collapse_btn->setFixedWidth(20);
    _this->collapse_btn->setFixedHeight(20);
    _this->collapse_btn->setText("-");
    hlayout->addWidget(_this->collapse_btn);
    hlayout->addWidget(_this->control_base);
    _this->main_layout->addLayout(hlayout);
    connect(_this->collapse_btn, &QPushButton::clicked,
            _this.data(), &AbstractRobotItemPrivate::collapseBtnClicked);

    _this->main_layout->addLayout(_this->main_image_layout);
    _this->main_widget->setLayout(_this->main_layout);

    hlayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    _this->main_layout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    _this->main_control_layout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    _this->main_image_layout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    hlayout->setAlignment(_this->collapse_btn, Qt::AlignTop | Qt::AlignLeft);

    _this->conf_diag = new ConfigDialog(GuiManager::instance()->widgetReference());
    _this->config_present = false;
    _this->conf_loaded = false;
    connect(_this->conf_diag, &ConfigDialog::itemsChanged,
            _this.data(), &AbstractRobotItemPrivate::restartIfRunning);
    connect(_this->conf_diag, &ConfigDialog::itemsChanged,
            _this.data(), &AbstractRobotItemPrivate::saveConfigs);

    // Hide the collapse button as long as there is nothing to collapse
    _this->collapse_btn->hide();
    connect(this->settingsScope(), &SettingsScope::parentScopeChanged,
            _this.data(), &AbstractRobotItemPrivate::parentScopeChanged);
    _this->main_widget->hide();
}

AbstractRobotItem::~AbstractRobotItem()
{
    if(this->settingsScope()->parentScope() != nullptr)
        SharedWindow::instance(this->settingsScope()->parentScope())->removeItem(this);
}

QWidget *AbstractRobotItem::widget()
{
    return _this->main_widget;
}

void AbstractRobotItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    AbstractItem::mouseDoubleClickEvent(event);
    SharedWindow::instance(this->settingsScope()->parentScope())->load();
    _this->main_widget->parentWidget()->show();
    _this->main_widget->show();
}

void AbstractRobotItem::contextMenuPrepare(QMenu &menu) const
{
    if(!_this->conf_loaded)
    {
        _this->conf_diag->load(this->settingsScope());
        _this->conf_loaded = true;
    }

    if(_this->config_present)
        menu.addAction("Configure", [this]{_this->conf_diag->show();});
}

void AbstractRobotItem::stop()
{
    for(ImageWidget* iw : _this->out_widgets)
        iw->reset();
}

void AbstractRobotItem::restart()
{
    this->stop();
    this->start();
}

void *AbstractRobotItem::addImageInput(std::string name)
{
    ItemInput *in;

    in = this->addInput(qMetaTypeId<ImageStream*>(), QString::fromStdString(name));
    connect(in, &ItemInput::dataChanged,
            _this.data(), &AbstractRobotItemPrivate::imageInputStateChanged);

    return in;
}

void *AbstractRobotItem::addImageOutput(std::string name)
{
    ItemOutput *out;
    ImageWidget *img;

    out = this->addOutput(qMetaTypeId<ImageStream*>(), QString::fromStdString(name));
    this->setOutputData(out, new ImageStream(this));
    img = new ImageWidget();
    _this->out_widgets.insert(out, img);
    _this->main_image_layout->addWidget(img);

    return out;
}

void AbstractRobotItem::pushImageOut(const PortableImage img, void *output)
{
    ItemOutput *out;
    ImageStream *stream;

    out = static_cast<ItemOutput*>(output);
    if(out == nullptr || out->data() == nullptr)
        return;

    stream = qobject_cast<ImageStream*>(out->data());
    if(stream == nullptr)
        return;

    emit stream->newImage(img);

    // Prevent overwriting the default image, if the item is not running
    if(this->running())
        _this->out_widgets.value(output)->setImage(img);
}

void *AbstractRobotItem::addTrim(std::string name, int min, int max)
{
    return this->addTrim(name, min, max, (max - min) + 1);
}

void *AbstractRobotItem::addTrim(std::string name, double min, double max, int steps)
{
    QSlider *slider = new QSlider();
    QVBoxLayout *layout = new QVBoxLayout();
    SliderLabel *label = new SliderLabel(min, max, steps, QString::fromStdString(name));

    slider->setMinimum(0);
    slider->setMaximum(steps - 1);
    slider->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    slider->setFixedWidth(50);
    layout->addWidget(new QLabel(QString::fromStdString(name)));
    layout->addWidget(slider);
    layout->addWidget(label);
    layout->setAlignment(Qt::AlignCenter | Qt::AlignHCenter);
    _this->main_control_layout->addLayout(layout);

    connect(slider, &QSlider::valueChanged,
            _this.data(), &AbstractRobotItemPrivate::trimChangedSlot);

    _this->collapse_btn->show();

    slider->setObjectName(QString::fromStdString(name));
    _this->sliders.append(slider);
    _this->slider_to_label.insert(slider, label);
    return slider;
}

double AbstractRobotItem::trimValue(void *trim)
{
    QSlider *s;

    s = static_cast<QSlider*>(trim);
    if(s)
        return _this->slider_to_label[s]->value();
    else
        return 0.0f;
}

void AbstractRobotItem::trimChanged(void *, double )
{
}

void AbstractRobotItem::addConfig(std::string name, std::string *value, std::function<std::string (std::string)> checker)
{
    _this->conf_diag->addItem(name, value, checker);
    _this->config_present = true;
}

void AbstractRobotItem::addConfig(std::string name, int *value, std::function<int (int)> checker)
{
    _this->conf_diag->addItem(name, value, checker);
    _this->config_present = true;
}

void AbstractRobotItem::addConfig(std::string name, double *value, std::function<double (double)> checker)
{
    _this->conf_diag->addItem(name, value, checker);
    _this->config_present = true;
}

void AbstractRobotItem::addConfig(std::string name, bool *value)
{
    _this->conf_diag->addItem(name, value);
    _this->config_present = true;
}

void AbstractRobotItem::addConfig(std::string name, std::vector<std::string> possibilities, int *index)
{
    _this->conf_diag->addItem(name, possibilities, index);
    _this->config_present = true;
}

void *AbstractRobotItem::addMessageOutput(std::string name)
{
    ItemOutput *out;

    out = this->addOutput(qMetaTypeId<MessageStream*>(),  QString::fromStdString(name));
    this->setOutputData(out, new MessageStream(this));

    return out;
}

void *AbstractRobotItem::addMessageInput(std::string name)
{
    ItemInput *in;

    in = this->addInput(qMetaTypeId<MessageStream*>(), QString::fromStdString(name));
    connect(in, &ItemInput::dataChanged,
            _this.data(), &AbstractRobotItemPrivate::messageInputStateChanged);

    return in;
}

void AbstractRobotItem::outputMessage(void *output, Message message)
{
    ItemOutput *out;
    MessageStream *stream;

    out = static_cast<ItemOutput*>(output);
    if(out == nullptr)
        return;

    stream = qobject_cast<MessageStream*>(out->data());
    if(stream == nullptr)
        return;

    emit stream->newMessage(message);
}

void AbstractRobotItem::start()
{
    // TODO The itemframework should have an 'initialization complete' signal
    if(!_this->conf_loaded)
    {
        _this->conf_diag->load(this->settingsScope());
        _this->conf_loaded = true;
    }
}

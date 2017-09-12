
#include "backend_dev/trim_dev_base.h"

#include <cmath>
#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QSlider>
#include <QVBoxLayout>
#include <QLabel>
#include "helper/settings_scope.h"
#include "core/roviz_item.h"

TrimDevBase::TrimDevBase(RovizItem *item, std::string name, double min, double max, int steps, bool logarithmic, std::function<void (double)> notifier_func)
    : _this(new TrimDevBasePrivate())
{
    QLabel *label_name = new QLabel(QString::fromStdString(name));
    QLabel *label_value = new QLabel();

    _this->loaded = false;
    _this->name = name;
    _this->item = item;

    // steps == 0 means a step size of 1
    if(steps <= 0)
        steps = max - min;

    _this->main_slider = new QSlider();
    _this->main_layout = new QVBoxLayout();
    _this->main_slider->setMinimum(0);
    _this->main_slider->setMaximum(steps);
    _this->main_slider->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    _this->main_slider->setFixedWidth(50);
    _this->main_layout->addWidget(label_name);
    _this->main_layout->addWidget(_this->main_slider);
    _this->main_layout->addWidget(label_value);
    _this->main_layout->setAlignment(Qt::AlignCenter | Qt::AlignHCenter);

    if(logarithmic)
    {
        min = std::log(min);
        max = std::log(max);
    }

    double factor = (max - min) / steps;
    TrimDevBasePrivate *t = _this.get();
    QObject::connect(_this->main_slider, &QSlider::valueChanged,
                     [t, factor, min, label_value, notifier_func, logarithmic](int value)
    {
        if(logarithmic)
            t->val = std::exp(min + (factor * static_cast<double>(value)));
        else
            t->val = min + (factor * static_cast<double>(value));
        label_value->setText(QString::number(t->val));
        t->item->settingsScope()->setValue("Trim/" + QString::fromStdString(t->name), value);
        notifier_func(t->val);
    });

    QObject::connect(_this->item->settingsScope(), &SettingsScope::parentScopeChanged,
                     [t](){t->load();});

    // TODO Why?
//    slider->setObjectName(QString::fromStdString(name));
}

TrimDevBase::TrimDevBase(TrimDevBase &&trim)
    : _this(trim._this.get())
{
    trim._this.release();
}

TrimDevBase &TrimDevBase::operator=(TrimDevBase &&trim)
{
    _this.reset(trim._this.get());
    trim._this.release();
    return *this;
}

QLayout *TrimDevBase::layout() const
{
    return _this->main_layout;
}

double TrimDevBase::value() const
{
    return _this->val;
}


#include "backend_dev/trim_impl_dev.h"

#include <cmath>
#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QSlider>
#include <QVBoxLayout>
#include <QLabel>
#include "helper/settings_scope.h"
#include "core/roviz_item.h"
#include "backend_dev/roviz_item_base_dev.h"

namespace roviz
{

TrimImplDev::TrimImplDev(ItemBaseDev *item, std::string name, double default_value, double min, double max, int steps, bool logarithmic, std::function<void (double)> notifier_func)
    : item(item), name(name), default_value(default_value), min(min), logarithmic(logarithmic), notifier_func(notifier_func)
{
    // steps == 0 means a step size of 1
    if(steps <= 0)
        steps = max - min;

    QLabel *label_name = new QLabel(QString::fromStdString(name));
    this->label_value = new QLabel();
    this->slider = new QSlider();
    this->main_layout = new QVBoxLayout();

    this->slider->setMinimum(0);
    this->slider->setMaximum(steps);
    this->slider->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    this->slider->setFixedWidth(50);

    this->main_layout->addWidget(label_name);
    this->main_layout->addWidget(this->slider);
    this->main_layout->addWidget(label_value);
    this->main_layout->setAlignment(Qt::AlignCenter | Qt::AlignHCenter);

    if(logarithmic)
    {
        this->min = std::log(min);
        max = std::log(max);
    }

    // The ratio between the int value of the QSlider and the real value the user gets
    this->scale_factor = (max - this->min) / steps;

    connect(this->slider, &QSlider::valueChanged,
            this, &TrimImplDev::valueChanged);

    // The settings scope is not ready yet during construction
    this->load_conn = connect(this->item->settingsScope(), &SettingsScope::parentScopeChanged,
                              this, &TrimImplDev::load);
}

QLayout *TrimImplDev::layout() const
{
    return this->main_layout;
}

double TrimImplDev::value()
{
    return this->val;
}

void TrimImplDev::load()
{
    double value = this->default_value;
    int int_value;

    // We have to make sure this gets only called once. It could happen that parentScopeChanged()
    // is emitted again (e.g. during destruction), so we disconnect this function now just to be sure.
    disconnect(this->load_conn);

    QVariant var = this->item->settingsScope()->value("Trim/" + QString::fromStdString(this->name));
    if(var.isValid())
        value = var.toDouble();

    if(this->logarithmic)
        int_value = (std::log(value) - this->min) / this->scale_factor;
    else
        int_value = (value - this->min) / this->scale_factor;

    this->slider->setValue(int_value);
    this->label_value->setText(QString::number(this->val));
}

void TrimImplDev::valueChanged(int int_value)
{
    if(this->logarithmic)
        this->val = std::exp(this->min + (this->scale_factor * static_cast<double>(int_value)));
    else
        this->val = min + (this->scale_factor * static_cast<double>(int_value));

    this->label_value->setText(QString::number(this->val));
    this->item->settingsScope()->setValue("Trim/" + QString::fromStdString(this->name), this->val);

    // It is probably faster to just call an empty function than to first check if it's empty
    // and only call it if it's not.
    this->notifier_func(this->val);
}

}

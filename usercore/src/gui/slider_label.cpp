
#include "gui/slider_label.h"

SliderLabel::SliderLabel(double min, double max, int steps, QString name, QWidget *parent)
    : QLabel(parent)
{
    this->min = min;
    this->max = max;
    this->steps = steps - 1;
    this->slider_value = min;
    this->_name = name;
}

double SliderLabel::value()
{
    return this->slider_value;
}

QString SliderLabel::name()
{
    return this->_name;
}

void SliderLabel::setValue(int val)
{
    this->slider_value = this->min + ((this->max - this->min) * (static_cast<double>(val) / this->steps));
    this->setText(QString::number(this->slider_value));
}

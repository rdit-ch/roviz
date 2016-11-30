#ifndef SLIDERLABEL_H
#define SLIDERLABEL_H

#include <QWidget>
#include <QLabel>

/**
 * @brief A QLabel that can be directly connected to a QSlider
 *
 * \ingroup robot_framework
 */
class SliderLabel : public QLabel
{
Q_OBJECT

public:
    SliderLabel(double min, double max, int steps, QString name, QWidget *parent = nullptr);
    double value(void);
    QString name(void);

private:
    QString _name;
    double min, max, slider_value;
    int steps;

public slots:
    void setValue(int slider_value);
};

#endif // SLIDERLABEL_H

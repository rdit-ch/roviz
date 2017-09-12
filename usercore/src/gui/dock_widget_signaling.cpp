
#include "gui/dock_widget_signaling.h"

#include <QWidget>
#include <QCloseEvent>
#include <QShowEvent>

DockWidgetSignaling::DockWidgetSignaling(QString title, QWidget *parent)
    : QDockWidget(title, parent)
{
}

void DockWidgetSignaling::closeEvent(QCloseEvent *event)
{
    this->hide();
    event->accept();
    emit this->closed();
}

void DockWidgetSignaling::showEvent(QShowEvent *event)
{
    emit this->shown();
    QDockWidget::showEvent(event);
}

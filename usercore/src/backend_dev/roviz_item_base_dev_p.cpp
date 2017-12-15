
#include "backend_dev/roviz_item_base_dev.h"
#include "backend_dev/roviz_item_base_dev_p.h"

#include <QString>
#include <QWidget>
#include <QSlider>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPropertyAnimation>
#include <QDialog>
#include "item/item_input.h"
#include "helper/settings_scope.h"
#include "gui/gui_manager.h"
#include "backend_dev/config_impl_base_dev.h"
#include "gui/shared_window.h"

RovizItemBaseDevPrivate::RovizItemBaseDevPrivate(RovizItemBaseDev *q)
{
    this->_this = q;
}

void RovizItemBaseDevPrivate::collapseBtnClicked()
{
    QPropertyAnimation *an = new QPropertyAnimation(this->control_base, "maximumWidth");
    an->setDuration(500);

    if(this->control_base->width() < 2)
    {
        // Qt needs some SERIOUS forcing to recalculate it's dimensions...
        this->control_base->hide();
        this->control_base->setMaximumWidth(65535);
        this->control_base->show();

        an->setStartValue(0);
        an->setEndValue(this->control_base->width());
        qobject_cast<QPushButton*>(this->collapse_btn)->setText("-");
    }
    else
    {
        an->setStartValue(this->control_base->width());
        an->setEndValue(0);
        qobject_cast<QPushButton*>(this->collapse_btn)->setText("+");
    }
    an->start();
}

void RovizItemBaseDevPrivate::parentScopeChanged(SettingsScope *old)
{
    if(old != nullptr)
        SharedWindow::instance(old)->removeItem(_this);

    if(_this->settingsScope()->parentScope() != nullptr)
        SharedWindow::instance(_this->settingsScope()->parentScope())->addItem(_this);
}

void RovizItemBaseDevPrivate::showConfigWindow()
{
    this->config_dialog.showDialog();
}

void RovizItemBaseDevPrivate::initConfigImpl(ConfigImplBaseDev *impl)
{
    connect(_this, &RovizItemBaseDev::parentChanged,
            [impl](){impl->load();});

    this->config_dialog.addConfig(impl);
    this->config_present = true;
}

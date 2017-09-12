
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

    for(const auto &conf : this->config_impls)
        conf->load();
}

void RovizItemBaseDevPrivate::showConfigWindow()
{
    // Gets redone everytime the config window is shown to allow
    // inserting/modifying configs on-the-fly
    QDialog *dialog = new QDialog(GuiManager::instance()->widgetReference());
    QVBoxLayout *main_layout = new QVBoxLayout();
    QVBoxLayout *conf_layout = new QVBoxLayout();
    QHBoxLayout *button_layout = new QHBoxLayout();
    QPushButton *btn_ok = new QPushButton("Ok");
    QPushButton *btn_cancel = new QPushButton("Cancel");

    for(auto &conf : this->config_impls)
        conf_layout->addWidget(conf->widget());

    button_layout->addWidget(btn_ok);
    button_layout->addWidget(btn_cancel);
    main_layout->addLayout(conf_layout);
    main_layout->addLayout(button_layout);
    dialog->setLayout(main_layout);
    dialog->setLayout(conf_layout);

    connect(btn_ok, &QPushButton::clicked,
            dialog, &QDialog::accept);

    connect(btn_cancel, &QPushButton::clicked,
            dialog, &QDialog::reject);

    if(dialog->exec() == QDialog::Accepted)
        for(auto &conf : this->config_impls)
            conf->refresh();
}

void RovizItemBaseDevPrivate::initConfigImpl(ConfigImplBaseDev *impl)
{
    connect(_this, &RovizItemBaseDev::parentChanged,
            [impl](){impl->load();});

    this->config_impls.append(impl);
    this->config_present = true;
}


#include "config_dialog.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include "gui/gui_manager.h"
#include "backend_dev/config_impl_base_dev.h"

ConfigDialog::ConfigDialog()
    : QDialog(GuiManager::instance()->widgetReference())
{
    this->conf_layout = new QVBoxLayout();
    QVBoxLayout *main_layout = new QVBoxLayout();
    QHBoxLayout *button_layout = new QHBoxLayout();
    QPushButton *btn_ok = new QPushButton("Ok");
    QPushButton *btn_cancel = new QPushButton("Cancel");

    button_layout->addWidget(btn_ok);
    button_layout->addWidget(btn_cancel);
    main_layout->addLayout(this->conf_layout);
    main_layout->addLayout(button_layout);
    this->setLayout(main_layout);

    connect(btn_ok, &QPushButton::clicked,
            this, &QDialog::accept);

    connect(btn_cancel, &QPushButton::clicked,
            this, &QDialog::reject);
}

void ConfigDialog::addConfig(ConfigImplBaseDev *config)
{
    this->configs.push_back(config);
}

void ConfigDialog::showDialog()
{
    // Gets redone everytime the config window is shown to allow
    // inserting/modifying configs on-the-fly
    while(this->conf_layout->takeAt(0));
    for(auto &conf : this->configs)
        this->conf_layout->addWidget(conf->widget());

    if(this->exec() == QDialog::Accepted)
        for(auto &conf : this->configs)
            conf->refresh();
}

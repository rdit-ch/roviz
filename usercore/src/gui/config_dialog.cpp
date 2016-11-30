
#include "gui/config_dialog.h"

ConfigDialog::ConfigDialog(QWidget *parent)
    : QDialog(parent)
{
    QVBoxLayout *vbox = new QVBoxLayout(this);
    QHBoxLayout *hbox = new QHBoxLayout();
    this->grid = new QGridLayout();
    QPushButton *btn_ok = new QPushButton("Ok");
    QPushButton *btn_cancel = new QPushButton("Cancel");
    QPushButton *btn_apply = new QPushButton("Apply");

    btn_ok->setFixedSize(70, 30);
    btn_cancel->setFixedSize(70, 30);
    btn_apply->setFixedSize(70, 30);

    connect(btn_ok, &QPushButton::clicked,
            this, &ConfigDialog::itemsChanged);
    connect(btn_ok, &QPushButton::clicked,
            this, &ConfigDialog::close);
    connect(btn_ok, &QPushButton::clicked,
            this, &ConfigDialog::updateDefault);
    connect(btn_cancel, &QPushButton::clicked,
            this, &ConfigDialog::restore);
    connect(btn_cancel, &QPushButton::clicked,
            this, &ConfigDialog::close);
    connect(btn_apply, &QPushButton::clicked,
            this, &ConfigDialog::itemsChanged);
    connect(btn_apply, &QPushButton::clicked,
            this, &ConfigDialog::updateDefault);

    hbox->addWidget(btn_ok);
    hbox->addWidget(btn_cancel);
    hbox->addWidget(btn_apply);

    vbox->addLayout(this->grid);
    vbox->addLayout(hbox);

    connect(this, &ConfigDialog::itemsChanged,
            this, &ConfigDialog::updateDefault);
}

void ConfigDialog::addItem(std::string name, std::string *value, std::function<std::string (std::string)> checker)
{
    QLineEdit *edit = new QLineEdit(QString::fromStdString(*value));

    int row = this->grid->rowCount();
    this->grid->addWidget(new QLabel(QString::fromStdString(name)), row, 0);
    this->grid->addWidget(edit, row, 1);

    this->val_str.insert(edit, Triple<std::string>(name, value, checker));
    connect(edit, &QLineEdit::textEdited,
            this, &ConfigDialog::strChanged);

    // Show a file browser button
    if(!checker)
    {
        ConfigBrowseButton *browse = new ConfigBrowseButton("Browse...");
        this->grid->addWidget(browse, row, 2);
        connect(browse, &ConfigBrowseButton::clicked,
                browse, &ConfigBrowseButton::wrapperSlot);
        connect(browse, &ConfigBrowseButton::wrapperSignal,
                edit, &QLineEdit::textEdited);
    }
}

void ConfigDialog::addItem(std::string name, int *value, std::function<int (int)> checker)
{
    QLineEdit *edit = new QLineEdit(QString::number(*value));

    int row = this->grid->rowCount();
    this->grid->addWidget(new QLabel(QString::fromStdString(name)), row, 0);
    this->grid->addWidget(edit, row, 1);

    this->val_int.insert(edit, Triple<int>(name, value, checker));
    connect(edit, &QLineEdit::textEdited,
            this, &ConfigDialog::intChanged);
}

void ConfigDialog::addItem(std::string name, double *value, std::function<double (double)> checker)
{
    QLineEdit *edit = new QLineEdit(QString::number(*value));

    int row = this->grid->rowCount();
    this->grid->addWidget(new QLabel(QString::fromStdString(name)), row, 0);
    this->grid->addWidget(edit, row, 1);

    this->val_double.insert(edit, Triple<double>(name, value, checker));
    connect(edit, &QLineEdit::textEdited,
            this, &ConfigDialog::doubleChanged);
}

void ConfigDialog::addItem(std::string name, bool *value)
{
    QCheckBox *cb = new QCheckBox();
    cb->setChecked(*value);

    int row = this->grid->rowCount();
    this->grid->addWidget(new QLabel(QString::fromStdString(name)), row, 0);
    this->grid->addWidget(cb, row, 1);

    this->val_bool.insert(cb, Tuple<bool>(name, value));
    connect(cb, &QCheckBox::toggled,
            this, &ConfigDialog::boolChanged);
}

void ConfigDialog::addItem(std::string name, std::vector<std::string> possibilities, int *index)
{
    QComboBox *cb = new QComboBox();
    for(auto p : possibilities)
        cb->addItem(QString::fromStdString(p));

    int row = this->grid->rowCount();
    this->grid->addWidget(new QLabel(QString::fromStdString(name)), row, 0);
    this->grid->addWidget(cb, row, 1);

    this->val_list.insert(cb, Tuple<int>(name, index));
    connect(cb, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this, &ConfigDialog::listChanged);
}

void ConfigDialog::save(SettingsScope *scope)
{
    for(const auto &v : this->val_str)    scope->setValue("Configs/" + QString::fromStdString(v.name), QString::fromStdString(*v.value));
    for(const auto &v : this->val_int)    scope->setValue("Configs/" + QString::fromStdString(v.name), *v.value);
    for(const auto &v : this->val_double) scope->setValue("Configs/" + QString::fromStdString(v.name), *v.value);
    for(const auto &v : this->val_bool)   scope->setValue("Configs/" + QString::fromStdString(v.name), *v.value);
    for(const auto &v : this->val_list)   scope->setValue("Configs/" + QString::fromStdString(v.name), *v.value);
}

void ConfigDialog::load(SettingsScope *scope)
{
    for(auto &v : this->val_str)    v.default_value = v.set(scope->value("Configs/" + QString::fromStdString(v.name), QString::fromStdString(v.default_value), false).toString().toStdString());
    for(auto &v : this->val_int)    v.default_value = v.set(scope->value("Configs/" + QString::fromStdString(v.name), v.default_value, false).toInt());
    for(auto &v : this->val_double) v.default_value = v.set(scope->value("Configs/" + QString::fromStdString(v.name), v.default_value, false).toDouble());
    for(auto &v : this->val_bool)   v.default_value = v.set(scope->value("Configs/" + QString::fromStdString(v.name), v.default_value, false).toBool());
    for(auto &v : this->val_list)   v.default_value = v.set(scope->value("Configs/" + QString::fromStdString(v.name), v.default_value, false).toInt());
    this->restore();
}

void ConfigDialog::strChanged()
{
    QLineEdit *edit = qobject_cast<QLineEdit*>(sender());
    if(!this->val_str[edit].checker)
        edit->setText(QString::fromStdString(this->val_str[edit].value->assign(QFileDialog::getOpenFileName(this, "Browse...").toStdString())));
    else
        edit->setText(QString::fromStdString(this->val_str[edit].set(edit->text().toStdString())));
}

void ConfigDialog::intChanged()
{
    QLineEdit *edit = qobject_cast<QLineEdit*>(sender());
    edit->setText(QString::number(this->val_int[edit].set(edit->text().toInt())));
}

void ConfigDialog::doubleChanged()
{
    QLineEdit *edit = qobject_cast<QLineEdit*>(sender());
    edit->setText(QString::number(this->val_double[edit].set(edit->text().toDouble())));
}

void ConfigDialog::boolChanged()
{
    QCheckBox *cb = qobject_cast<QCheckBox*>(sender());
    *this->val_bool[cb].value = cb->isChecked();
}

void ConfigDialog::listChanged()
{
    QComboBox *cb = qobject_cast<QComboBox*>(sender());
    *this->val_list[cb].value = cb->currentIndex();
}

void ConfigDialog::restore()
{
    for(const auto &k : this->val_str.keys())    k->setText(QString::fromStdString(this->val_str[k].reset()));
    for(const auto &k : this->val_int.keys())    k->setText(QString::number(this->val_int[k].reset()));
    for(const auto &k : this->val_double.keys()) k->setText(QString::number(this->val_double[k].reset()));
    for(const auto &k : this->val_bool.keys())   k->setChecked(this->val_bool[k].reset());
    for(const auto &k : this->val_list.keys())   k->setCurrentIndex(this->val_list[k].reset());
}

void ConfigDialog::updateDefault()
{
    for(auto &v : this->val_str)    v.default_value = *v.value;
    for(auto &v : this->val_int)    v.default_value = *v.value;
    for(auto &v : this->val_double) v.default_value = *v.value;
    for(auto &v : this->val_bool)   v.default_value = *v.value;
    for(auto &v : this->val_list)   v.default_value = *v.value;
}

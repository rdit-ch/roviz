
#include "backend_dev/config_impl_dev.h"

#include <mutex>
#include <QtGlobal>
#include <QObject>
#include <QString>
#include <QVariant>
#include <QStringList>
#include <QLineEdit>
#include <QLabel>
#include <QIntValidator>
#include <QDoubleValidator>
#include <QComboBox>
#include <QCheckBox>
#include <QFileDialog>
#include <QPushButton>
#include <QHBoxLayout>
#include "backend_dev/config_parent.h"
#include "helper/settings_scope.h"
#include "gui/gui_manager.h"
#include "core/template_decl.h"
#include "core/roviz_item.h"

template<>
ConfigImplDev<int>::ConfigImplDev(ConfigParent *parent, const std::string &name, const typename ConfigStorageType<int>::type &default_value, int min, int max, bool restart_when_changed)
    : parent(parent), name(name), val(default_value), restart_after_change(restart_when_changed), has_changed(false), tmp_changed(false)
{
    QLineEdit *edit = new QLineEdit();
    QIntValidator *valid = new QIntValidator(min, max);

    edit->setValidator(valid);
    QObject::connect(edit, &QLineEdit::textEdited,
                     [this](QString text)
    {
        std::lock_guard<std::mutex> lock(this->mtx);

        this->tmp_changed = true;
        this->tmp_val = text.toInt();
    });
    this->initMainWidget(edit);
    this->data_widget = edit;
}

template<>
ConfigImplDev<double>::ConfigImplDev(ConfigParent *parent, const std::string &name, const typename ConfigStorageType<double>::type &default_value, double min, double max, bool restart_when_changed)
    : parent(parent), name(name), val(default_value), restart_after_change(restart_when_changed), has_changed(false), tmp_changed(false)
{
    QLineEdit *edit = new QLineEdit();
    QDoubleValidator *valid = new QDoubleValidator(min, max, 1000); // 1000 is the default

    edit->setValidator(valid);
    QObject::connect(edit, &QLineEdit::textEdited,
                     [this](QString text)
    {
        std::lock_guard<std::mutex> lock(this->mtx);

        this->tmp_changed = true;
        this->tmp_val = text.toDouble();
    });
    this->initMainWidget(edit);
    this->data_widget = edit;
}

template<>
ConfigImplDev<std::string>::ConfigImplDev(ConfigParent *parent, const std::string &name, const typename ConfigStorageType<std::string>::type &default_value, std::function<bool (std::string &)> checker, bool restart_when_changed)
    : parent(parent), name(name), val(default_value), restart_after_change(restart_when_changed), has_changed(false), tmp_changed(false)
{
    QLineEdit *edit = new QLineEdit();

    QObject::connect(edit, &QLineEdit::textEdited,
                     [this, checker, edit](QString text)
    {
        std::string text_str = text.toStdString();
        if(checker(text_str))
        {
            std::lock_guard<std::mutex> lock(this->mtx);

            this->tmp_val = text_str;
            this->tmp_changed = true;
        }
        else
        {
            edit->setText(QString::fromStdString(this->tmp_val));
        }
    });

    this->initMainWidget(edit);
    this->data_widget = edit;
}

template<>
ConfigImplDev<std::vector<std::string> >::ConfigImplDev(ConfigParent *parent, const std::string &name, const typename ConfigStorageType<std::vector<std::string > >::type &default_value, const std::vector<std::string> &possibilities, bool restart_when_changed)
    : parent(parent), name(name), val(default_value), restart_after_change(restart_when_changed), has_changed(false), tmp_changed(false)
{
    QComboBox *combo = new QComboBox();

    for(const auto &entry : possibilities)
        combo->addItem(QString::fromStdString(entry));

    QObject::connect(combo, QOverload<int>::of(&QComboBox::currentIndexChanged),
                     [combo, this](int)
    {
        std::lock_guard<std::mutex> lock(this->mtx);

        this->tmp_changed = true;
        this->tmp_val = combo->currentIndex();
    });
    this->initMainWidget(combo);
    this->data_widget = combo;
}

template<>
ConfigImplDev<bool>::ConfigImplDev(ConfigParent *parent, const std::string &name, const typename ConfigStorageType<bool>::type &default_value, bool restart_when_changed)
    : parent(parent), name(name), val(default_value), restart_after_change(restart_when_changed), has_changed(false), tmp_changed(false)
{
    QCheckBox *box = new QCheckBox();

    QObject::connect(box, &QCheckBox::toggled,
                     [this](bool checked)
    {
        std::lock_guard<std::mutex> lock(this->mtx);

        this->tmp_changed = true;
        this->tmp_val = checked;
    });
    this->initMainWidget(box);
    this->data_widget = box;
}

template<>
ConfigImplDev<FilePath>::ConfigImplDev(ConfigParent *parent, const std::string &name, const typename ConfigStorageType<FilePath>::type &default_value, FilePath::Mode file_mode, const std::string &filter, bool restart_when_changed)
    : parent(parent), name(name), val(default_value), restart_after_change(restart_when_changed), has_changed(false), tmp_changed(false)
{
    QFileDialog::FileMode mode;

    switch(file_mode)
    {
        case FilePath::AnyFile:       mode = QFileDialog::AnyFile; break;
        case FilePath::ExistingFile:  mode = QFileDialog::ExistingFile; break;
        case FilePath::MultipleFiles: mode = QFileDialog::ExistingFiles; break;
        case FilePath::Directory:     mode = QFileDialog::Directory; break;
        default:                      mode = QFileDialog::ExistingFile; break;
    }

    QWidget *widget = new QWidget();
    QHBoxLayout *hlayout = new QHBoxLayout();
    QLineEdit *edit = new QLineEdit();
    QPushButton *button = new QPushButton("File...");

    hlayout->addWidget(edit);
    hlayout->addWidget(button);
    widget->setLayout(hlayout);
    edit->setReadOnly(true);

    QObject::connect(button, &QPushButton::clicked,
                     [this, edit, mode, filter](void)
    {
        QFileDialog diag(GuiManager::instance()->widgetReference(),
                         "Select...",
                         "",
                         QString::fromStdString(filter));
        diag.setFileMode(mode);
        if(!diag.exec())
            return;

        QStringList files = diag.selectedFiles();
        this->tmp_val.clear();
        edit->setText("");

        // We don't want a ';' in the beginning
        this->tmp_val.push_back(files.front().toStdString());
        edit->setText(edit->text() + files.front());
        files.pop_front();

        for(const auto &file : files)
        {
            this->tmp_val.push_back(file.toStdString());
            edit->setText(edit->text() + "; " + file);
        }
        this->tmp_changed = true;
    });

    this->initMainWidget(widget);
    this->data_widget = edit;
}

template<typename T>
QWidget *ConfigImplDev<T>::widget() const
{
    return this->main_widget;
}

template<>
void ConfigImplDev<int>::load(void)
{
    QVariant var = this->parent->getSettingsScope()->value("Config/int/" + QString::fromStdString(this->name));
    if(var.isValid())
        this->val =  var.toInt();
    qobject_cast<QLineEdit*>(this->data_widget)->setText(QString::number(this->val));
}

template<>
void ConfigImplDev<double>::load(void)
{
    QVariant var = this->parent->getSettingsScope()->value("Config/double/" + QString::fromStdString(this->name));
    if(var.isValid())
        this->val = var.toDouble();
    qobject_cast<QLineEdit*>(this->data_widget)->setText(QString::number(this->val));
}

template<>
void ConfigImplDev<std::string>::load(void)
{
    QVariant var = this->parent->getSettingsScope()->value("Config/string/" + QString::fromStdString(this->name));
    if(var.isValid())
        this->val = var.toString().toStdString();
    qobject_cast<QLineEdit*>(this->data_widget)->setText(QString::fromStdString(this->val));
}

template<>
void ConfigImplDev<std::vector<std::string> >::load(void)
{
    QVariant var = this->parent->getSettingsScope()->value("Config/list/" + QString::fromStdString(this->name));
    if(var.isValid())
        this->val = var.toInt();
    qobject_cast<QComboBox*>(this->data_widget)->setCurrentIndex(this->val);
}

template<>
void ConfigImplDev<bool>::load(void)
{
    QVariant var = this->parent->getSettingsScope()->value("Config/bool/" + QString::fromStdString(this->name));
    if(var.isValid())
        this->val = var.toBool();
    qobject_cast<QCheckBox*>(this->data_widget)->setChecked(this->val);
}

template<>
void ConfigImplDev<FilePath>::load(void)
{
    QVariant var = this->parent->getSettingsScope()->value("Config/file_path/" + QString::fromStdString(this->name));
    if(!var.isValid())
        return;

    QStringList list = var.toStringList();
    this->val.clear();
    for(const auto &path : list)
        this->val.push_back(path.toStdString());

    // We don't want a ';' in the beginning
    QString str = list.front();
    list.pop_front();
    for(const auto &path : list)
        str += "; " + path;
    qobject_cast<QLineEdit*>(this->data_widget)->setText(str);
}

template<typename T>
bool ConfigImplDev<T>::changed()
{
    return this->has_changed;
}

template<typename T>
void ConfigImplDev<T>::refresh()
{
    std::lock_guard<std::mutex> lock(this->mtx);

    // Only proceed if this item really changed
    if(!this->tmp_changed)
        return;

    this->has_changed = true;
    this->tmp_changed = false;

    this->val = this->tmp_val;
    this->save();

    if(this->restart_after_change)
        this->parent->restart();
}

template<typename T>
void ConfigImplDev<T>::lock()
{
    this->mtx.lock();
}

template<typename T>
void ConfigImplDev<T>::unlock()
{
    this->mtx.unlock();
}

template<typename T>
void *ConfigImplDev<T>::value()
{
    // This isn't exactly safe (and very, very ugly), but we have to count on
    // Config<T> being the only class to ever call this method and that it will
    // use the propper locking and typecasts.
    return &this->val;
}

template<typename T>
void ConfigImplDev<T>::initMainWidget(QWidget *sub_widget)
{
    QHBoxLayout *hlayout;
    QLabel *name_label;
    this->main_widget = new QWidget();

    // We assume that is the default layout. Specialize init() if that is not
    // the case.
    hlayout = new QHBoxLayout();
    name_label = new QLabel(QString::fromStdString(this->name));
    hlayout->addWidget(name_label);
    hlayout->addWidget(sub_widget);
    this->main_widget->setLayout(hlayout);
}

template<>
void ConfigImplDev<int>::save()
{ this->parent->getSettingsScope()->setValue("Config/int/" + QString::fromStdString(this->name), this->val); }

template<>
void ConfigImplDev<double>::save()
{ this->parent->getSettingsScope()->setValue("Config/double/" + QString::fromStdString(this->name), this->val); }

template<>
void ConfigImplDev<std::string>::save()
{ this->parent->getSettingsScope()->setValue("Config/string/" + QString::fromStdString(this->name), QString::fromStdString(this->val)); }

template<>
void ConfigImplDev<std::vector<std::string> >::save()
{ this->parent->getSettingsScope()->setValue("Config/list/" + QString::fromStdString(this->name), this->val); }

template<>
void ConfigImplDev<bool>::save()
{ this->parent->getSettingsScope()->setValue("Config/bool/" + QString::fromStdString(this->name), this->val); }

template<>
void ConfigImplDev<FilePath>::save()
{
    QStringList list;
    for(const auto &path : this->val)
        list.append(QString::fromStdString(path));
    this->parent->getSettingsScope()->setValue("Config/file_path/" + QString::fromStdString(this->name), list);
}

#define INSTANTIATE_CONFIG_IMPL(T) template class ConfigImplDev<T>;

DO_FOR_ALL_CONFIG_TYPES(INSTANTIATE_CONFIG_IMPL)

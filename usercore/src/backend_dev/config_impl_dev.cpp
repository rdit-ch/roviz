
#include "backend_dev/config_impl_dev.h"

#include <mutex>
#include <QtGlobal>
#include <QRegularExpression>
#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QIntValidator>
#include <QDoubleValidator>
#include <QComboBox>
#include <QCheckBox>
#include <QVariant>
#include <QFileDialog>
#include <QPushButton>
#include "helper/settings_scope.h"
#include "gui/gui_manager.h"
#include "config/config_p.h"
#include "core/template_decl.h"
#include "core/roviz_item.h"

template<typename T>
ConfigImplDev<T>::ConfigImplDev(ConfigPrivate<T> *config)
{
    _this = config;
}

template<typename T>
QWidget *ConfigImplDev<T>::widget() const
{
    return this->main_widget;
}

template<>
void ConfigImplDev<int>::load(void)
{
    QVariant var = _this->parent->settingsScope()->value("Config/int/" + QString::fromStdString(_this->name));
    if(var.isValid())
        _this->val =  var.toInt();
    qobject_cast<QLineEdit*>(this->data_widget)->setText(QString::number(_this->val));
}

template<>
void ConfigImplDev<double>::load(void)
{
    QVariant var = _this->parent->settingsScope()->value("Config/double/" + QString::fromStdString(_this->name));
    if(var.isValid())
        _this->val = var.toDouble();
    qobject_cast<QLineEdit*>(this->data_widget)->setText(QString::number(_this->val));
}

template<>
void ConfigImplDev<std::string>::load(void)
{
    QVariant var = _this->parent->settingsScope()->value("Config/string/" + QString::fromStdString(_this->name));
    if(var.isValid())
        _this->val = var.toString().toStdString();
    qobject_cast<QLineEdit*>(this->data_widget)->setText(QString::fromStdString(_this->val));
}

template<>
void ConfigImplDev<std::list<std::string> >::load(void)
{
    QVariant var = _this->parent->settingsScope()->value("Config/list/" + QString::fromStdString(_this->name));
    if(var.isValid())
        _this->val = var.toInt();
    qobject_cast<QComboBox*>(this->data_widget)->setCurrentIndex(_this->val);
}

template<>
void ConfigImplDev<bool>::load(void)
{
    QVariant var = _this->parent->settingsScope()->value("Config/bool/" + QString::fromStdString(_this->name));
    if(var.isValid())
        _this->val = var.toBool();
    qobject_cast<QCheckBox*>(this->data_widget)->setChecked(_this->val);
}

template<>
void ConfigImplDev<FilePath>::load(void)
{
    QVariant var = _this->parent->settingsScope()->value("Config/file_path/" + QString::fromStdString(_this->name));
    if(!var.isValid())
        return;

    QStringList list = var.toStringList();
    _this->val.clear();
    for(const auto &path : list)
        _this->val.push_back(path.toStdString());

    // We don't want a ';' in the beginning
    QString str = list.front();
    list.pop_front();
    for(const auto &path : list)
        str += "; " + path;
    qobject_cast<QLineEdit*>(this->data_widget)->setText(str);
}

template<typename T>
bool ConfigImplDev<T>::restartAfterChange() const
{
    return _this->restart_after_change;
}

template<>
void ConfigImplDev<int>::init(int min, int max)
{
    QLineEdit *edit = new QLineEdit();
    QIntValidator *valid = new QIntValidator(min, max);

    edit->setValidator(valid);
    QObject::connect(edit, &QLineEdit::textEdited,
                     [this](QString text)
    {
        std::lock_guard<std::mutex> lock(_this->mtx);

        this->tmp_changed = true;
        this->tmp_val = text.toInt();
    });
    this->initMainWidget(edit);
    this->data_widget = edit;
}

template<>
void ConfigImplDev<double>::init(double min, double max)
{
    QLineEdit *edit = new QLineEdit();
    QDoubleValidator *valid = new QDoubleValidator(min, max, 1000); // 1000 is the default

    edit->setValidator(valid);
    QObject::connect(edit, &QLineEdit::textEdited,
                     [this](QString text)
    {
        std::lock_guard<std::mutex> lock(_this->mtx);

        this->tmp_changed = true;
        this->tmp_val = text.toDouble();
    });
    this->initMainWidget(edit);
    this->data_widget = edit;
}

template<>
void ConfigImplDev<std::string>::init(std::function<bool (std::string&)> checker)
{
    QLineEdit *edit = new QLineEdit();

    QObject::connect(edit, &QLineEdit::textEdited,
                     [this, checker](QString text)
    {
        std::lock_guard<std::mutex> lock(_this->mtx);

        this->tmp_val = text.toStdString();
        this->tmp_changed = checker(this->tmp_val);
    });
    this->initMainWidget(edit);
    this->data_widget = edit;
}

template<>
void ConfigImplDev<std::list<std::string> >::init(const std::list<std::string> &possibilities)
{
    QComboBox *combo = new QComboBox();

    for(const auto &entry : possibilities)
        combo->addItem(QString::fromStdString(entry));

    QObject::connect(combo, QOverload<int>::of(&QComboBox::currentIndexChanged),
                     [combo, this](int)
    {
        std::lock_guard<std::mutex> lock(_this->mtx);

        this->tmp_changed = true;
        this->tmp_val = combo->currentIndex();
    });
    this->initMainWidget(combo);
    this->data_widget = combo;
}

template<>
void ConfigImplDev<bool>::init()
{
    QCheckBox *box = new QCheckBox();

    QObject::connect(box, &QCheckBox::toggled,
                     [this](bool checked)
    {
        std::lock_guard<std::mutex> lock(_this->mtx);

        this->tmp_changed = true;
        this->tmp_val = checked;
    });
    this->initMainWidget(box);
    this->data_widget = box;
}

template<>
void ConfigImplDev<FilePath>::init(const std::string &filter, enum FilePath::Mode file_mode)
{
    QFileDialog::FileMode mode;

    switch(file_mode)
    {
        case FilePath::AnyFile:       mode = QFileDialog::AnyFile; break;
        case FilePath::ExistingFile:  mode = QFileDialog::ExistingFile; break;
        case FilePath::MultipleFiles: mode = QFileDialog::ExistingFiles; break;
        case FilePath::Directory:     mode = QFileDialog::Directory; break;
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
void ConfigImplDev<T>::changed()
{
    std::lock_guard<std::mutex> lock(_this->mtx);

    // Only proceed if this item really changed
    if(!this->tmp_changed)
        return;

    _this->changed = true;
    this->tmp_changed = false;

    _this->val = this->tmp_val;
    this->save();

    if(_this->restart_after_change)
        _this->parent->restart();
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
    name_label = new QLabel(QString::fromStdString(_this->name));
    hlayout->addWidget(name_label);
    hlayout->addWidget(sub_widget);
    this->main_widget->setLayout(hlayout);
}

template<>
void ConfigImplDev<int>::save()
{ _this->parent->settingsScope()->setValue("Config/int/" + QString::fromStdString(_this->name), _this->val); }

template<>
void ConfigImplDev<double>::save()
{ _this->parent->settingsScope()->setValue("Config/double/" + QString::fromStdString(_this->name), _this->val); }

template<>
void ConfigImplDev<std::string>::save()
{ _this->parent->settingsScope()->setValue("Config/string/" + QString::fromStdString(_this->name), QString::fromStdString(_this->val)); }

template<>
void ConfigImplDev<std::list<std::string> >::save()
{ _this->parent->settingsScope()->setValue("Config/list/" + QString::fromStdString(_this->name), _this->val); }

template<>
void ConfigImplDev<bool>::save()
{ _this->parent->settingsScope()->setValue("Config/bool/" + QString::fromStdString(_this->name), _this->val); }

template<>
void ConfigImplDev<FilePath>::save()
{
    QStringList list;
    for(const auto &path : _this->val)
        list.append(QString::fromStdString(path));
    _this->parent->settingsScope()->setValue("Config/file_path/" + QString::fromStdString(_this->name), list);
}

INSTANTIATE_CONFIG_IMPL

#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QList>
#include <QPushButton>
#include <QVariant>
#include <QFileDialog>
#include <functional>
#include "helper/settings_scope.h"

// Ugly hack that makes a string and a path distinguishable.
// ONLY use as checker function for addItem() with a string config!
#define CONFIG_IS_PATH nullptr

/**
 * @brief Shows a dialog window to adjust configs
 *
 * See PortableItem to learn more about configs.
 */
// NOTE I know all of this is rather ugly, but I couldn't think of a more
//      elegant way. Feel free to change it if you find one.
class ConfigDialog : public QDialog
{
    Q_OBJECT

public:
    ConfigDialog(QWidget *parent = nullptr);
    // Call with CONFIG_IS_PATH as checker to get a file selector
    void addItem(std::string name, std::string *value, std::function<std::string (std::string)> checker = [](std::string a){return a;});
    void addItem(std::string name, int *value, std::function<int (int)> checker = [](int a){return a;});
    void addItem(std::string name, double *value, std::function<double (double)> checker = [](double a){return a;});
    void addItem(std::string name, bool *value);
    void addItem(std::string name, std::vector<std::string> possibilities, int *index);
    void save(SettingsScope *scope);
    void load(SettingsScope *scope);

private:
    template<class T>
    class Tuple
    {
    public:
        std::string name;
        T* value;
        T default_value;
        Tuple(){}
        Tuple(std::string n, T *v) : name(n), value(v), default_value(*v){}
        T reset(void){*this->value = this->default_value; return *this->value;}
        T set(T v){*this->value = v; return v;}
    };

    template<class T>
    class Triple : public Tuple<T>
    {
    public:
        std::function<T (T)> checker;
        Triple(){}
        Triple(std::string n, T *v, std::function<T (T)> c) : Tuple<T>(n, v), checker(c){}
        T set(T v){*this->value = this->checker ? this->checker(v) : v; return *this->value;}
    };

    QGridLayout *grid;
    QMap<QLineEdit*, Triple<std::string> > val_str;
    QMap<QLineEdit*, Triple<int> >         val_int;
    QMap<QLineEdit*, Triple<double> >      val_double;
    QMap<QCheckBox*, Tuple<bool> >         val_bool;
    QMap<QComboBox*, Tuple<int> >          val_list;

private slots:
    void strChanged(void);
    void intChanged(void);
    void doubleChanged(void);
    void boolChanged(void);
    void listChanged(void);
    void restore(void);
    void updateDefault(void);

signals:
    void itemsChanged(void);
};

class ConfigBrowseButton : public QPushButton
{
    Q_OBJECT
    using QPushButton::QPushButton;
    signals: void wrapperSignal(const QString& = QString());
    public slots: void wrapperSlot(bool){emit this->wrapperSignal();}
};

#endif // CONFIGDIALOG_H

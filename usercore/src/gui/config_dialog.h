#ifndef CONFIG_DIALOG_H
#define CONFIG_DIALOG_H

#include <QDialog>

class ConfigImplBaseDev;
class QVBoxLayout;

class ConfigDialog : public QDialog
{
Q_OBJECT

public:
    ConfigDialog();
    void addConfig(ConfigImplBaseDev *config);
    void showDialog(void);

private:
    QVBoxLayout *conf_layout;
    std::list<ConfigImplBaseDev*> configs;
};

#endif // CONFIG_DIALOG_H


#include <QApplication>
#include <QSettings>
#include "helper/startup_helper.h"
#include "usercore.h"
#include "core/logger.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    QApplication::setOrganizationName("rdit.ch");
    QApplication::setOrganizationDomain("rdit.ch");
    QApplication::setApplicationName("roviz");
    QApplication::setApplicationDisplayName("roviz 0.7");
    QApplication::setApplicationVersion("0.7");

    roviz::initLogger();

    // We need to do this because the itemframework won't find
    // the plugins otherwise
    {
        QSettings settings;
        settings.beginGroup("Plugins");
        if(!settings.value("pluginPath").isValid())
            settings.setValue("pluginPath", QStringList({"/usr/lib/roviz/dev", "/usr/local/lib/roviz/dev"}));
        settings.endGroup();
    }

    StartupHelper::ensureCoreGetsLinked();
    LinkerHelper::ensureUserCoreGetsLinked();

    return a.exec();
}

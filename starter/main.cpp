#include <QApplication>
#include "helper/startup_helper.h"
#include "usercore.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    QApplication::setOrganizationName("rdit.ch");
    QApplication::setOrganizationDomain("rdit.ch");
    QApplication::setApplicationName("roviz");
    QApplication::setApplicationDisplayName("roviz 0.6");
    QApplication::setApplicationVersion("0.6");

    StartupHelper::ensureCoreGetsLinked();
    LinkerHelper::ensureUserCoreGetsLinked();

    return a.exec();
}

#include <QGuiApplication>
#include <QQmlApplicationEngine>

/*#include "src/mock-server/mockserver.h"
#include "src/mock-server/mockresponse.h"
#include "src/mock-server/mockendpoint.h"
#include "src/mock-server/mockhost.h"*/

#include "src/gui/gui.h"
#include "src/gui/projectmodel.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QCoreApplication::setOrganizationName("Absender");
    QCoreApplication::setOrganizationDomain("absender.com");
    QCoreApplication::setApplicationName("Absender");

    QGuiApplication app(argc, argv);


    Gui gui(&app);


    gui.start();

    return app.exec();
}

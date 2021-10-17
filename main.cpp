#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "src/mock-server/mockserver.h"
#include "src/mock-server/mockresponse.h"
#include "src/mock-server/mockendpoint.h"
#include "src/mock-server/mockhost.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    MockServer server;

    MockResponse res("{\"result\": \"ok\"}", {
                         {"Content-Type", "application/json"}
                     });
    MockEndpoint ep1("/", "GET", res);
    MockEndpoint ep2("/users", "GET", MockResponse("{\"users\": []}", {{"Content-Type", "application/json"}}));
    MockEndpoint ep3("/points", "GET", MockResponse("", {{"Content-Type", "application/json"}}, 404));
    MockHost host("test.com");
    host.addEndpoint(&ep1);
    host.addEndpoint(&ep2);
    host.addEndpoint(&ep3);

    server.addHost(&host);
    server.start();



    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}

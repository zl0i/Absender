#include "gui.h"

Gui::Gui(QGuiApplication *app) : app(app)
{

    url.setUrl(QStringLiteral("qrc:/main.qml"));
    connect(&engine, &QQmlApplicationEngine::objectCreated, app, [=](QObject *obj, const QUrl &objUrl) {
        if (!obj && this->url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

}

void Gui::start()
{
    engine.load(url);
}

void Gui::setContextProperty(QString name, QObject *obj)
{
    engine.rootContext()->setContextProperty(name, obj);
}

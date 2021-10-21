#include "gui.h"

Gui::Gui(QGuiApplication *app) : app(app)
{

    url.setUrl(QStringLiteral("qrc:/main.qml"));
    connect(&engine, &QQmlApplicationEngine::objectCreated, app, [=](QObject *obj, const QUrl &objUrl) {
        if (!obj && this->url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);


    setContextProperty("recents", &projects);
    setContextProperty("gui", this);

}

void Gui::start()
{
    engine.load(url);
}

void Gui::setContextProperty(QString name, QObject *obj)
{
    engine.rootContext()->setContextProperty(name, obj);
}

void Gui::createNewProject(QString name, QString)
{
    QFile file("../" + name + ".abs");
    QFileInfo info(file);
    if(file.open(QIODevice::ReadWrite)) {
        qDebug() << "new project created";
        projects.append(name, info.absoluteFilePath());
        QJsonObject obj {
            {"name", name},
            {"path", info.absoluteFilePath()}
        };
    }
}

void Gui::openProject(QString path)
{
    QFile file(path);
    if(file.open(QIODevice::ReadOnly)) {
       QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
       project = new Project(doc.object());
    }
}


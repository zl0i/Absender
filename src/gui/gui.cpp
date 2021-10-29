#include "gui.h"

Gui::Gui(QGuiApplication *app) : app(app)
{

    url.setUrl(QStringLiteral("qrc:/main.qml"));
    connect(&engine, &QQmlApplicationEngine::objectCreated, app, [=](QObject *obj, const QUrl &objUrl) {
        if (!obj && this->url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    project = new Project(QJsonObject {});

    setContextProperty("recents", &projects);
    setContextProperty("gui", this);
    setContextProperty("project", project);

}

Gui::~Gui()
{
    delete project;
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
        projects.append(name, info.absoluteFilePath());
        QJsonObject obj {
            {"name", name},
            {"path", info.absoluteFilePath()}
        };
        QJsonDocument doc(QJsonObject {
                              {"name", name},
                              {"services", QJsonObject {}}
                          });
        file.write(doc.toJson());
        file.close();
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


#ifndef GUI_H
#define GUI_H

#include <QObject>
#include <QGuiApplication> //TO DO to QApplication
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QFile>
#include <QFileInfo>
#include <QJsonObject>
#include <QJsonDocument>

#include "project.h"
#include "projectmodel.h"

class Gui : public QObject
{
    Q_OBJECT
public:
    explicit Gui(QGuiApplication *app);
    ~Gui();

    void start();
    void setContextProperty(QString name, QObject* obj);

private:
    QQmlApplicationEngine engine;
    QGuiApplication *app;
    QUrl url;

    ProjectModel projects;
    Project *project;
signals:

public slots:
    void createNewProject(QString name, QString);
    void openProject(QString path);

};

#endif // GUI_H

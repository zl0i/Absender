#ifndef PROJECTCONTROLLER_H
#define PROJECTCONTROLLER_H

#include <QObject>
#include <QSettings>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>
#include <QFileInfo>

#include "projectmodel.h"

class ProjectController : public QObject
{
    Q_OBJECT
public:
    explicit ProjectController(ProjectModel *model);



private:
    QSettings *settings = new QSettings("projects");
    ProjectModel *model;
    QJsonArray recent;
signals:

public slots:
    void createNewProject(QString name, QString path);
    void openProject(QString path);

};

#endif // PROJECTCONTROLLER_H

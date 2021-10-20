#include "projectcontroller.h"

ProjectController::ProjectController(ProjectModel *model) : model(model)
{
    recent = settings->value("recent").toJsonArray();
    QJsonArray arr;
    model->insertRows(0, 1);
    for(int i = 0; i < recent.count(); i++) {
        QJsonObject project = recent.at(i).toObject();
        if(QFile::exists(project.value("path").toString())) {
            model->append(project.value("name").toString(), project.value("path").toString());
            arr.append(project);
        }
    }
    settings->setValue("recent", arr);
}

void ProjectController::createNewProject(QString name, QString)
{
    QFile file("../" + name + ".abs");
    QFileInfo info(file);
    if(file.open(QIODevice::ReadWrite)) {
        qDebug() << "new project created";
        model->append(name, info.absoluteFilePath());
        QJsonObject obj {
            {"name", name},
            {"path", info.absoluteFilePath()}
        };
        recent.append(obj);
        settings->setValue("recent", recent);
    }
}

void ProjectController::openProject(QString path)
{
   QFile file(path);
   if(file.open(QIODevice::ReadOnly)) {

   }
}

#include "projectmodel.h"

ProjectModel::ProjectModel() :  QAbstractListModel()
{
    QJsonArray recent = settings->value("recent").toJsonArray();
    QJsonArray existProjects;
    this->insertRows(0, recent.count());
    for(int i = 0; i < recent.count(); i++) {
        QJsonObject project = recent.at(i).toObject();
        if(QFile::exists(project.value("path").toString())) {
            projects.append(QJsonObject {
                                {"name", project.value("name").toString()},
                                {"path", project.value("path").toString()}
                            });
            existProjects.append(project);
        }
    }
    settings->setValue("recent", existProjects);
}

int ProjectModel::rowCount(const QModelIndex &) const
{
    return projects.count();
}

QVariant ProjectModel::data(const QModelIndex &index, int role) const
{
    if(index.row() >= projects.count())
        return QVariant();

    QJsonObject p = projects.at(index.row()).toObject();

    switch (role) {
    case NameRole:
        return p.value("name");
    case PathRole:
        return p.value("path");
    default:
        return QVariant();
    }
}

void ProjectModel::append(QString name, QString path)
{

    emit beginInsertRows(QModelIndex(), rowCount(), rowCount());
    projects.append(QJsonObject {
                        {"name", name},
                        {"path", path}
                    });
    emit endInsertRows();
    emit dataChanged(index(0,0), index(rowCount(), 0));
    settings->setValue("recent", projects);
}

QHash<int, QByteArray> ProjectModel::roleNames() const
{
    QHash<int, QByteArray> hash;

    hash[NameRole] = "name";
    hash[PathRole] = "path";
    return hash;
}

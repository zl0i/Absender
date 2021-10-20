#include "projectmodel.h"

ProjectModel::ProjectModel() :  QAbstractListModel()
{

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
}

QHash<int, QByteArray> ProjectModel::roleNames() const
{
    QHash<int, QByteArray> hash;

    hash[NameRole] = "name";
    hash[PathRole] = "path";
    return hash;
}

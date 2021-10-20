#ifndef PROJECTMODEL_H
#define PROJECTMODEL_H

#include <QObject>
#include <QModelIndex>
#include <QJsonArray>
#include <QJsonObject>

class ProjectModel : public  QAbstractListModel
{
    Q_OBJECT

public:
    explicit ProjectModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    void append(QString name, QString path);

    QHash<int, QByteArray> roleNames() const;

    enum {
        NameRole = Qt::UserRole+1,
        PathRole,
    } RoleTypes;

private:

    QJsonArray projects;

signals:

};

#endif // PROJECTMODEL_H

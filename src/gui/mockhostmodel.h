#ifndef MOCKHOSTMODEL_H
#define MOCKHOSTMODEL_H

#include <QObject>
#include <QAbstractListModel>

#include "../mock-server/mockhost.h"
#include "mockendpointsmodel.h"


class MockHostModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit MockHostModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    void append(MockHost *host);
    void append(QList<MockHost*> *hosts);

    QHash<int, QByteArray> roleNames() const;

    enum {
        HostNameRole = Qt::UserRole+1,
        EndpointsRole,
    } RoleTypes;

private:
    QList<MockHost*> hosts;

signals:

};


#endif // MOCKHOSTMODEL_H

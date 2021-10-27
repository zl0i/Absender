#ifndef MOCKSERVERMODEL_H
#define MOCKSERVERMODEL_H

#include <QObject>
#include <QAbstractListModel>

#include "mockhostmodel.h"
#include "../mock-server/mockserver.h"


class MockServerModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit MockServerModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    void append(MockServer *host);

    QHash<int, QByteArray> roleNames() const;

    enum {
        NameRole = Qt::UserRole+1,
        HostsRole,
    } RoleTypes;

private:
    QList<MockServer*> servers;

signals:

};

#endif // MOCKSERVERMODEL_H

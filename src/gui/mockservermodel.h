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
    bool setData(const QModelIndex &index, const QVariant &data, int role = Qt::EditRole);
    void append(MockServer *host);

    QHash<int, QByteArray> roleNames() const;

    enum {
        NameRole = Qt::UserRole+1,
        HostsRole,
    } RoleTypes;

private:
    QList<MockServer*> servers;
    QList<MockHostModel*> hosts;

signals:

public slots:
    void append();

};

#endif // MOCKSERVERMODEL_H

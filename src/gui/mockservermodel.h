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
    ~MockServerModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &data, int role = Qt::EditRole);

    QHash<int, QByteArray> roleNames() const;

    QJsonArray toJSON();
    MockServer* at(int i);

    enum {
        NameRole = Qt::UserRole+1,
        PortRole,
        HostsRole,
    } RoleTypes;

private:
    QList<MockServer*> servers;
    QList<MockHostModel*> hosts;

signals:

public slots:
    void append(MockServer *host);
    void appendHost(int index, QString hostname);

};

#endif // MOCKSERVERMODEL_H

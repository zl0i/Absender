#include "mockservermodel.h"

MockServerModel::MockServerModel(QObject *parent) : QAbstractListModel(parent)
{

}

int MockServerModel::rowCount(const QModelIndex &) const
{
    return servers.count();
}

QVariant MockServerModel::data(const QModelIndex &index, int role) const
{
    if(index.row() >= servers.count())
        return QVariant();

    MockServer *s = servers.at(index.row());

    switch (role) {
    case NameRole:
        return "Mock Server " + QString::number(index.row()+1);
    case HostsRole:
        MockHostModel *hosts = new MockHostModel();
        hosts->append(s->hosts());
        return QVariant::fromValue(hosts);
    }
    return QVariant();
}

void MockServerModel::append(MockServer *server)
{
    emit beginInsertRows(QModelIndex(), rowCount(), rowCount());
    servers.append(server);
    emit endInsertRows();
    emit dataChanged(index(0,0), index(rowCount(), 0));
}

QHash<int, QByteArray> MockServerModel::roleNames() const
{
    QHash<int, QByteArray> hash;

    hash[NameRole] = "name";
    hash[HostsRole] = "hosts";
    return hash;
}

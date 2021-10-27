#include "mockhostmodel.h"

MockHostModel::MockHostModel(QObject *parent) : QAbstractListModel(parent)
{

}

int MockHostModel::rowCount(const QModelIndex &) const
{
    return hosts.count();
}

QVariant MockHostModel::data(const QModelIndex &index, int role) const
{
    if(index.row() >= hosts.count())
        return QVariant();

    MockHost *h = hosts.at(index.row());

    switch (role) {
    case HostNameRole:
        return h->hostname();
    case EndpointsRole:
        MockEndpointsModel *model = new MockEndpointsModel();
        model->append(h->endpoints());
        return QVariant::fromValue(model);
    }
    return QVariant();

}

void MockHostModel::append(MockHost *host)
{
    emit beginInsertRows(QModelIndex(), rowCount(), rowCount());
    hosts.append(host);
    emit endInsertRows();
    emit dataChanged(index(0,0), index(rowCount(), 0));
}

void MockHostModel::append(QList<MockHost*> *hosts)
{
    emit beginInsertRows(QModelIndex(), rowCount(), rowCount());
    for(int i =0; i < hosts->length(); i++) {
        this->hosts.append(hosts->at(i));
    }
    emit endInsertRows();
    emit dataChanged(index(0,0), index(rowCount(), 0));
}

QHash<int, QByteArray> MockHostModel::roleNames() const
{
    QHash<int, QByteArray> hash;

    hash[HostNameRole] = "hostname";
    hash[EndpointsRole] = "endpoints";
    return hash;
}

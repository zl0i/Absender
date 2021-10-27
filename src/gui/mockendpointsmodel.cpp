#include "mockendpointsmodel.h"

MockEndpointsModel::MockEndpointsModel(QObject *parent) : QAbstractListModel(parent)
{

}

int MockEndpointsModel::rowCount(const QModelIndex &) const
{
    return endpoints.count();
}

QVariant MockEndpointsModel::data(const QModelIndex &index, int role) const
{
    if(index.row() >= endpoints.count())
        return QVariant();

    MockEndpoint *e = endpoints.at(index.row());

    switch (role) {
    case PathRole:
        return e->path();
    case MethodRole:
        return e->method();
    case ResponseRole:
        return e->response().toJSON();
    default:
        return QVariant();
    }
}

void MockEndpointsModel::append(MockEndpoint *endpoint)
{
    emit beginInsertRows(QModelIndex(), rowCount(), rowCount());
    endpoints.append(endpoint);
    emit endInsertRows();
    emit dataChanged(index(0,0), index(rowCount(), 0));
}

void MockEndpointsModel::append(QList<MockEndpoint*> *endpoints)
{
    emit beginInsertRows(QModelIndex(), rowCount(), rowCount());
    for(int i =0; i < endpoints->length(); i++) {
       this->endpoints.append(endpoints->at(i));
    }
    emit endInsertRows();
    emit dataChanged(index(0,0), index(rowCount(), 0));
}

QHash<int, QByteArray> MockEndpointsModel::roleNames() const
{
    QHash<int, QByteArray> hash;

    hash[MethodRole] = "method";
    hash[PathRole] = "path";
    hash[ResponseRole] = "response";
    return hash;
}

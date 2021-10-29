#include "mockservermodel.h"

MockServerModel::MockServerModel(QObject *parent) : QAbstractListModel(parent)
{

}

MockServerModel::~MockServerModel()
{
    for(int i = 0; i < rowCount(); i++) {
        at(i)->stop();
    }
}

int MockServerModel::rowCount(const QModelIndex &) const
{
    return servers.count();
}

QVariant MockServerModel::data(const QModelIndex &index, int role) const
{
    if(index.row() >= servers.count())
        return QVariant();

    switch (role) {
    case NameRole:
        return "Mock Server " + QString::number(index.row()+1);
    case HostsRole: {
        MockHostModel *model = hosts.at(index.row());
        return QVariant::fromValue(model);
    }
    }
    return QVariant();
}

bool MockServerModel::setData(const QModelIndex &index, const QVariant &data, int role)
{
    if(index.row() >= servers.count())
        return false;

    //MockServer *s = servers.at(index.row());

    switch (role) {
    case NameRole:
        return true;
    case HostsRole:

        return true;
    }
    return false;
}

void MockServerModel::append(MockServer *server)
{
    emit beginInsertRows(QModelIndex(), rowCount(), rowCount());

    servers.append(server);
    MockHostModel *model = new MockHostModel(this);
    model->append(server->hosts());
    hosts.append(model);

    emit endInsertRows();
    emit dataChanged(index(0,0), index(rowCount(), 0));
}

void MockServerModel::append()
{
    emit beginInsertRows(QModelIndex(), rowCount(), rowCount());
    MockServer *srv = new MockServer();
    servers.append(srv);
    emit endInsertRows();
    emit dataChanged(index(0,0), index(rowCount(), 0));
}

void MockServerModel::appendHost(int row, QString hostname)
{
    MockHost *host = new MockHost(hostname);
    MockServer *server = servers.at(row);
    server->addHost(host);
    MockHostModel *model = hosts.at(row);
    model->append(host);
    emit dataChanged(index(row, 0), index(row, 0));
}


QHash<int, QByteArray> MockServerModel::roleNames() const
{
    QHash<int, QByteArray> hash;

    hash[NameRole] = "name";
    hash[HostsRole] = "hosts";
    return hash;
}

QJsonArray MockServerModel::toJSON()
{
    QJsonArray jservers;
    for(int i = 0; i < servers.count(); i++) {
        jservers.append(QJsonObject {
                            {"name", "Mock Server " + QString::number(i+1)},
                            {"hosts", hosts.at(i)->toJSON()},
                        });
    }
    return jservers;
}

MockServer *MockServerModel::at(int i)
{
    return servers.at(i);
}

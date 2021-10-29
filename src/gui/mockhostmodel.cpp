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
        MockEndpointsModel *model = endpoints.at(index.row());
        return QVariant::fromValue(model);
    }
    return QVariant();

}

bool MockHostModel::setData(const QModelIndex &index, const QVariant &data, int role)
{
    if(index.row() >= hosts.count())
        return false;

    MockHost *h = hosts.at(index.row());

    switch (role) {
    case HostNameRole: {
        h->setHostname(data.toString());
        return true;
    }
    }
    return false;
}

void MockHostModel::append(MockHost *host)
{
    emit beginInsertRows(QModelIndex(), rowCount(), rowCount());
    hosts.append(host);
    MockEndpointsModel *model = new MockEndpointsModel(this);
    connect(model, &MockEndpointsModel::dataChanged, this, &MockHostModel::dataChanged);
    for(int i = 0; i < host->endpoints()->count(); i++) {
        model->append(host->endpoints()->at(i));
    }
    endpoints.append(model);
    emit endInsertRows();
    emit dataChanged(index(0,0), index(rowCount(), 0));
}

void MockHostModel::append(QList<MockHost*> *hosts)
{
    emit beginInsertRows(QModelIndex(), rowCount(), rowCount());
    for(int i =0; i < hosts->length(); i++) {
        MockHost *host = hosts->at(i);
        this->hosts.append(host);
        MockEndpointsModel *model = new MockEndpointsModel(this);
        connect(model, &MockEndpointsModel::dataChanged, this, &MockHostModel::dataChanged);
        for(int i = 0; i < host->endpoints()->count(); i++) {
            model->append(host->endpoints()->at(i));
        }
        endpoints.append(model);
    }
    emit endInsertRows();
    emit dataChanged(index(0,0), index(rowCount(), 0));
}

void MockHostModel::appendEndpoint(int row, QString path)
{
    MockEndpoint *ep = new MockEndpoint(path);
    MockHost *host = hosts.at(row);
    host->addEndpoint(ep);
    MockEndpointsModel *epmodel = endpoints.at(row);
    connect(epmodel, &MockEndpointsModel::dataChanged, this, &MockHostModel::dataChanged);
    epmodel->append(ep);
    emit dataChanged(index(row, 0), index(row, 0));
}


QHash<int, QByteArray> MockHostModel::roleNames() const
{
    QHash<int, QByteArray> hash;

    hash[HostNameRole] = "hostname";
    hash[EndpointsRole] = "endpoints";
    return hash;
}

QJsonArray MockHostModel::toJSON()
{
    QJsonArray jhosts;
    for(int i = 0; i < hosts.count(); i++) {
        QJsonObject host;
        host.insert("hostname", hosts.at(i)->hostname());
        host.insert("endpoints", endpoints.at(i)->toJSON());
        jhosts.append(host);
    }
    return jhosts;
}

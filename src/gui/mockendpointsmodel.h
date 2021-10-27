#ifndef MOCKENDPOINTSMODEL_H
#define MOCKENDPOINTSMODEL_H

#include <QObject>
#include <QAbstractListModel>

#include "../mock-server/mockendpoint.h"

class MockEndpointsModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit MockEndpointsModel(QObject *parent = nullptr);


    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    void append(MockEndpoint *endpoint);
    void append(QList<MockEndpoint*> *endpoints);

    QHash<int, QByteArray> roleNames() const;

    enum {
        MethodRole = Qt::UserRole+1,
        PathRole,
        ResponseRole
    } RoleTypes;

private:
    QList<MockEndpoint*> endpoints;

signals:

};

#endif // MOCKENDPOINTSMODEL_H

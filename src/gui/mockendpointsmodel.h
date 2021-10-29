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


    int rowCount(const QModelIndex &parent = QModelIndex()) const override ;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &data ,int role = Qt::EditRole) override;


    QJsonArray toJSON();

    QHash<int, QByteArray> roleNames() const override;

    enum {
        MethodRole = Qt::UserRole+1,
        PathRole,
        ResponseRole
    } RoleTypes;

private:
    QList<MockEndpoint*> endpoints;

signals:

public slots:
    void append(MockEndpoint *endpoint);
    void append(QList<MockEndpoint*> *endpoints);
    void append(QString method, QString path);

};

#endif // MOCKENDPOINTSMODEL_H

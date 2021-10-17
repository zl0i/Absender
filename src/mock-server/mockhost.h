#ifndef MOCKHOST_H
#define MOCKHOST_H

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>

#include "mockendpoint.h"

class MockHost
{
public:
    explicit MockHost(QString hostname);

    void setHostname(QString hostname) { this->_hostname = hostname; }
    QString hostname() { return _hostname; }

    void addEndpoint(MockEndpoint* endpoint);
    void removeEndpoint(QString path, QString method);
    QList<MockEndpoint*> endpoints() { return _endpoints; }


    QJsonObject toJSON();



private:
    QString _hostname;
    QList<MockEndpoint*> _endpoints;


};

#endif // MOCKHOST_H

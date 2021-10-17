#include "mockhost.h"

MockHost::MockHost(QString hostname): _hostname(hostname)
{

}

void MockHost::addEndpoint(MockEndpoint *endpoint)
{
    _endpoints.append(endpoint);
}

void MockHost::removeEndpoint(QString path, QString method)
{
    for(int i = 0; i < _endpoints.length(); i++) {
        MockEndpoint *endpoint = _endpoints[i];
        if(endpoint->path() == path && endpoint->method() == method) {
            delete  endpoint;
            _endpoints.removeAt(i);
        }
    }
}

QJsonObject MockHost::toJSON()
{
    QJsonObject obj;
    QJsonArray array;
    for(int i = 0; i < _endpoints.length(); i++) {
        array.append(_endpoints.at(i)->toJSON());
    }
    obj.insert("hostname", _hostname);
    obj.insert("endpoints", array);
    return obj;
}


#include "mockendpoint.h"

MockEndpoint::MockEndpoint(QString path, QString method, MockResponse response): _path(path), _method(method.toUpper()), _response(response)
{

}

MockEndpoint::~MockEndpoint()
{

}

QJsonObject MockEndpoint::toJSON()
{
    QJsonObject obj;
    obj.insert("path", _path);
    obj.insert("method", _method);
    obj.insert("response", _response.toJSON());
    return obj;
}



#include "mockresponse.h"

MockResponse::MockResponse(QString body, std::initializer_list<QPair<QString, QString>> headers, int status): _body(body), _statusCode(status)
{   
    for (const auto &h : headers) {
        _headers.append(new Header(h.first, h.second));
    }
}

MockResponse::~MockResponse()
{
}

void MockResponse::addHeader(QString name, QString value)
{
    _headers.append(new Header(name, value));
}

void MockResponse::removeHeader(QString name)
{
    for(int i = 0; i < _headers.length(); i++) {
        if(_headers.at(i)->name() == name) {
            delete _headers.at(i);
            _headers.removeAt(i);
        }
    }
}

void MockResponse::setBody(QString data)
{
    this->_body = data;
}

QJsonObject MockResponse::toJSON()
{
    QJsonObject obj;
    QJsonArray array;
    for(int i = 0; i < _headers.length(); i++) {
        array.append(QJsonObject {
                         { "name", _headers.at(i)->name() },
                         { "value", _headers.at(i)->value() }
                     });
    }
    obj.insert("headers", array);
    obj.insert("body", _body);
    obj.insert("statusCode", _statusCode);

    return obj;
}

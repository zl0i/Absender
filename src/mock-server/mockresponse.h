#ifndef MOCKRESPONSE_H
#define MOCKRESPONSE_H

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>

#include "src/utils/header.h"

class MockResponse
{

public:
    MockResponse(QString body = "", std::initializer_list<QPair<QString, QString>> headers = std::initializer_list<QPair<QString, QString>> {}, int status = 200);
    ~MockResponse();

    void addHeader(QString name, QString value);
    void removeHeader(QString name);
    void setBody(QString data);
    void setStatusCode(int code);

    QList<Header *> *headers() { return &_headers; }
    QString body() { return this->_body; }
    int statusCode() { return _statusCode; }

    QJsonObject toJSON();

private:
    QString _body;
    int _statusCode = 200;
    QList<Header*> _headers;

};

#endif // MOCKRESPONSE_H

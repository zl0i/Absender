#ifndef MOCKENDPOINT_H
#define MOCKENDPOINT_H

#include <QObject>
#include <QJsonObject>

#include "mockresponse.h"

class MockEndpoint
{

public:
    MockEndpoint(QString path, QString method = "GET", MockResponse response = MockResponse());
    ~MockEndpoint();

    void setPath(QString path) { this->_path = path;}
    void setMethod(QString method) { this->_method = method.toUpper(); }
    void setResponse(MockResponse response) { this->_response = response; }

    QString path() { return _path; }
    QString method() { return _method; }
    MockResponse response() { return _response; }

    QJsonObject toJSON();

private:
    QString _path;
    QString _method;
    MockResponse _response;

};

#endif // MOCKENDPOINT_H

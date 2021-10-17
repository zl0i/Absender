#include "mockserver.h"

MockServer::MockServer(QObject *parent) : QObject(parent)
{

}

void MockServer::setHost(QString)
{
    QFile file("C:\\Windows\\System32\\drivers\\etc\\hosts");
    if(file.open(QIODevice::ReadOnly)) {
        qDebug() << file.readAll();
    } else {
        qDebug() << "file not open";
    }
}

void MockServer::start()
{
    mock.start("./plugins/mock-server/server.exe");
}

void MockServer::stop()
{

}

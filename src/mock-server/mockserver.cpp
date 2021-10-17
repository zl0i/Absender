#include "mockserver.h"

MockServer::MockServer(QObject *parent) : QObject(parent)
{
    QFile file("C:\\Windows\\System32\\drivers\\etc\\hosts");
    if(file.open(QIODevice::ReadOnly)) {
        qDebug() << "file opened for read";
    } else {
        qDebug() << "file not open";
    }
}

void MockServer::addHost(MockHost *host)
{
    _hosts.append(host);
}

void MockServer::removeHost(QString hostname)
{
    for(int i = 0; i < _hosts.length(); i++) {
        if(_hosts.at(i)->hostname() == hostname) {
            delete _hosts.at(i);
            _hosts.removeAt(i);
        }
    }
}

QJsonObject MockServer::serialize()
{
    QJsonObject obj;
    QJsonArray hosts_json;
    for(int i = 0; i < _hosts.length(); i++) {
        hosts_json.append(_hosts.at(i)->toJSON());
    }
    obj.insert("version", "v0.0.1");
    obj.insert("hosts", hosts_json);
    return obj;
}

void MockServer::init()
{
    QJsonDocument doc(serialize());
    QFile file("./options.json");
    if(file.open(QIODevice::ReadWrite)) {
        file.write(doc.toJson());
        file.close();
    } else {
        qDebug() << "file did't writed";
    }
}

void MockServer::start()
{
    init();
    //mock.start("./plugins/mock-server/server.exe");
}

void MockServer::stop()
{

}

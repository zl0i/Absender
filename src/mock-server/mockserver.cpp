#include "mockserver.h"
#include <QtGlobal>

MockServer::MockServer(QObject *parent) : QObject(parent)
{
    process.setProcessChannelMode(QProcess::MergedChannels);
    connect(&process, &QProcess::readyRead, this, &MockServer::consoleData);
    connect(&process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this, &MockServer::serverFinished);
    connect(&process, &QProcess::errorOccurred, this, &MockServer::serverError);
}

MockServer::~MockServer()
{
    stop();
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
        file.resize(0);
        file.write(doc.toJson());
        file.close();
    } else {
        qDebug() << "file did't writed";
    }
}

void MockServer::writeHostsFile()
{
    QFile file("C:\\Windows\\System32\\drivers\\etc\\hosts");
    if(file.open(QIODevice::ReadWrite)) {
        qDebug() << "hosts file opened";
        file.seek(file.size());
        for(int i = 0; i < _hosts.length(); i++) {
            file.write(QString("127.0.0.1 " + _hosts.at(i)->hostname() + "\n").toLocal8Bit());
        }
        file.close();
    } else {
        qDebug() << "hosts file not open";
    }
}

void MockServer::cleanHostsFile()
{
    QFile file("C:\\Windows\\System32\\drivers\\etc\\hosts");
    QString s;
    QTextStream t(&file);
    if(file.open(QIODevice::ReadWrite)) {
        while(!t.atEnd()) {
            QString line = t.readLine();
            bool contains = false;
            for(int i = 0; i < _hosts.length(); i++) {
                if(line.contains(_hosts.at(i)->hostname())) {
                    contains = true;
                }
            }
            if(!contains)
                s.append(line + "\n");
        }
        file.resize(0);
        t << s;
        file.close();
    }
}

void MockServer::start()
{
    init();
    writeHostsFile();

    QStringList arguments;
    arguments.append("-f ./../options.json");
    process.start(jsserver, arguments);
}

void MockServer::stop()
{
    process.kill();
    cleanHostsFile();
}

void MockServer::consoleData()
{
    process.setReadChannel(QProcess::StandardError);
    QByteArray error = process.readAll();
    if(!error.isEmpty())
        emit newErrorData(error);

    process.setReadChannel(QProcess::StandardOutput);
    QByteArray log = process.readAll();
    if(!log.isEmpty())
        emit newLogData(log);
}

void MockServer::serverFinished()
{

}

void MockServer::serverError()
{

}

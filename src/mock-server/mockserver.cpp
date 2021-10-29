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

void MockServer::setName(QString name)
{
    _name = name;
}

void MockServer::setPort(int port)
{
    _port = port;
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
    QJsonArray jhost;
    for(int i = 0; i < _hosts.length(); i++) {
        jhost.append(_hosts.at(i)->toJSON());
    }
    obj.insert("name", _name);
    obj.insert("port", _port);
    obj.insert("version", "v0.0.1");
    obj.insert("hosts", jhost);
    return obj;
}

void MockServer::init()
{
    QJsonDocument doc(serialize());
    QString name = "t"
            + QString::number(QDateTime::currentMSecsSinceEpoch())
            + "-" + _name
            + "-options.json";
    configFile = new QFile("./" + name);
    if(configFile->open(QIODevice::ReadWrite)) {
        configFile->resize(0);
        configFile->write(doc.toJson());
        configFile->close();
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
    QFileInfo info(*configFile);
    arguments.append("-f " + info.absoluteFilePath());
    process.start(jsserver, arguments);
}

void MockServer::stop()
{
    process.kill();
    cleanHostsFile();
    configFile->remove();
    configFile->deleteLater();
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

void MockServer::configChanged()
{
    init();
}

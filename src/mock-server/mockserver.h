#ifndef MOCKSERVER_H
#define MOCKSERVER_H

#include <QObject>
#include <QProcess>
#include <QFile>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QDebug>
#include <QFileInfo>

#include "mockhost.h"

class MockServer : public QObject
{
    Q_OBJECT
public:
    explicit MockServer(QObject *parent = nullptr);
    ~MockServer();

    QString name() { return _name; }
    void setName(QString name);
    int port() { return _port; }
    void setPort(int port);

    void addHost(MockHost *host);
    void removeHost(QString hostname);
    QList<MockHost*> *hosts() { return &_hosts; }

private:
#ifdef QT_NO_DEBUG
    const QString jsserver = "./plugins/mock-server/main.exe";
#else
    const QString jsserver = "../Absender/plugins/mock-server/main.exe";
#endif

    QList<MockHost*> _hosts;
    QProcess process;
    QString _name = "Mock Server";
    int _port = 0;

    QFile *configFile;

    QJsonObject serialize();
    void init();

    void writeHostsFile();
    void cleanHostsFile();


public slots:
    void start();
    void stop();
    void consoleData();

    void serverFinished();
    void serverError();

    void configChanged();

signals:

    void newErrorData(QString data);
    void newLogData(QString data);

};

#endif // MOCKSERVER_H

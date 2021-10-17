#ifndef MOCKSERVER_H
#define MOCKSERVER_H

#include <QObject>
#include <QProcess>
#include <QFile>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

#include <QDebug>
#include "mockhost.h"

class MockServer : public QObject
{
    Q_OBJECT
public:
    explicit MockServer(QObject *parent = nullptr);

    void addHost(MockHost *host);
    void removeHost(QString hostname);
    QList<MockHost*>* hosts() { return &_hosts; }


private:

    QList<MockHost*> _hosts;
    QProcess mock;

    QJsonObject serialize();
    void init();


public slots:
    void start();
    void stop();

signals:

};

#endif // MOCKSERVER_H

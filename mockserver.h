#ifndef MOCKSERVER_H
#define MOCKSERVER_H

#include <QObject>
#include <QProcess>
#include <QFile>

#include <QDebug>

class MockServer : public QObject
{
    Q_OBJECT
public:
    explicit MockServer(QObject *parent = nullptr);

    void setHost(QString host);
    void start();
    void stop();
private:

    QString host;
    QProcess mock;

signals:

};

#endif // MOCKSERVER_H

#ifndef PROJECT_H
#define PROJECT_H

#include <QObject>
#include <QJsonObject>
#include <QStandardItemModel>

#include "mockservermodel.h"

class Project : public QObject
{
    Q_OBJECT
    Q_PROPERTY(MockServerModel *mocks READ mocks NOTIFY mocksChanged)
    Q_PROPERTY(bool isMockStart READ isMockStart NOTIFY isMockStartChanged)

public:
    explicit Project(QJsonObject project);
    ~Project();

    QJsonObject toJson();

    MockServerModel *mocks() { return  _mocks; }
    bool isMockStart() { return _isMockStart; }


private:
    QString name;
    QString path;

    //QObjectList *_mocks = new QObjectList();


    MockServerModel *_mocks = new MockServerModel();
    bool _isMockStart = false;



signals:
    void mocksChanged();
    void isMockStartChanged();

public slots:
    void startMockServers();
    void stopMockServers();
    void saveMockServers();

};

#endif // PROJECT_H

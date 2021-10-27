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
public:
    explicit Project(QJsonObject project);

    QJsonObject toJson();

    MockServerModel *mocks() { return  _mocks; }


private:
    QString name;
    QString path;

    //QObjectList *_mocks = new QObjectList();


    MockServerModel *_mocks = new MockServerModel();



signals:
    void mocksChanged();

};

#endif // PROJECT_H

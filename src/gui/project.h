#ifndef PROJECT_H
#define PROJECT_H

#include <QObject>
#include <QJsonObject>

class Project : public QObject
{
    Q_OBJECT
public:
    explicit Project(QJsonObject project);

    QJsonObject toJson();


private:
    QString name;
    QString path;



signals:

};

#endif // PROJECT_H

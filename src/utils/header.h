#ifndef HEADER_H
#define HEADER_H

#include <QObject>

class Header
{

public:
    explicit Header(QString name, QString value);

    void setName(QString name);
    void setValue(QString value);

    QString name();
    QString value();

private:
    QString _name;
    QString _value;

signals:

};

#endif // HEADER_H

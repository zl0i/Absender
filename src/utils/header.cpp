#include "header.h"

Header::Header(QString name, QString value)
{
    this->_name = name;
    this->_value = value;
}

void Header::setName(QString name)
{
    this->_name = name;
}

void Header::setValue(QString value)
{
    this->_value = value;
}

QString Header::name()
{
    return _name;
}

QString Header::value()
{
    return  _value;
}

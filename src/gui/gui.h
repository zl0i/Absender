#ifndef GUI_H
#define GUI_H

#include <QObject>
#include <QGuiApplication> //TO DO to QApplication
#include <QQmlApplicationEngine>
#include <QQmlContext>

class Gui : public QObject
{
    Q_OBJECT
public:
    explicit Gui(QGuiApplication *app);

    void start();
    void setContextProperty(QString name, QObject* obj);

private:
    QQmlApplicationEngine engine;
    QGuiApplication *app;
    QUrl url;
signals:

};

#endif // GUI_H

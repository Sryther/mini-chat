#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>
#include <QEvent>
#include <QApplication>

class Application : public QApplication
{
public:
    Application(int& argc, char** argv);
    bool notify(QObject* receiver, QEvent* event);
};

#endif // APPLICATION_H

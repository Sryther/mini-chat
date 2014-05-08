#ifndef USER_H
#define USER_H

#include <QString>
#include <QFile>

class UserPersistent
{
private:
    UserPersistent();
    ~UserPersistent();
    static UserPersistent* _instance;
public:
    static UserPersistent* getInstance();

private:
    QString _username;
    int _port;
    QString _color;
    QFile* _savefile;
public:
    QString getUsername() { return _username; };
    void setUsername(QString username) { _username = username; };

    int getPort() { return _port; };
    void setPort(int port) { _port = port; };

    QString getColor() { return _color; };
    void setColor(QString color) { _color = color; };

    void savePersistent();
    void loadPersistent();
};

#endif // USER_H

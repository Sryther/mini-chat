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
    static void delInstance();
    static bool hasInstance();

private:
    QString _username;
    int _port;
    QString _color;
    QFile* _savefile;
    void _savePersistent();
    void _loadPersistent();
public:
    QString getUsername() { return _username; };
    void setUsername(QString username) { _username = username; };

    int getPort() { return _port; };
    void setPort(int port) { _port = port; };

    QString getColor() { return _color; };
    void setColor(QString color) { _color = color; };

    void static savePersistent();
    void static loadPersistent();
};

#endif // USER_H

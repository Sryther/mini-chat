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
    QString _getColor() { return _color; }
    int _getPort() { return _port; }
    QString _getUsername() { return _username; }
    void _setUsername(QString username) { _username = username; }
    void _setPort(int port) { _port = port; }
    void _setColor(QString color) { _color = color; }
public:
    void static setColor(QString color);
    void static setPort(int port);
    void static setUsername(QString username);
    QString static getColor();
    int static getPort();
    QString static getUsername();

    void static savePersistent();
    void static loadPersistent();
};

#endif // USER_H

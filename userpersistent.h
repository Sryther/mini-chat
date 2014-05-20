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
    UserPersistent(const UserPersistent &&other);
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

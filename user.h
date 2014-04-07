#ifndef USER_H
#define USER_H

#include <QString>
#include <QHostAddress>

class User
{
private:
    QString _username;
    QHostAddress _ip;

public:
    User(QString username, QHostAddress ip);
    QString getUsername() { return _username; };
    QHostAddress getIp() { return _ip; };
};

#endif // USER_H

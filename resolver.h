#ifndef CONNECTION_H
#define CONNECTION_H

#include <QString>
#include <QMap>
#include <QTcpSocket>
#include "message.h"

using namespace std;

class Resolver
{
    public:
        static bool findOrNewUser(QString username, QString ip);
        static QMap<QString, QString>* _users;
        static QString resolveUsername(QString username);
        static QString resolveIp(QString ip);
};

QMap<QString, QString>* Resolver::_users = nullptr;

#endif // CONNECTION_H

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
        Resolver(QObject *parent = 0);
        bool static findOrNewUser(QString username, QString ip);
        static QMap<QString, QString>* _users;
        static QString resolveUsername(QString username);
        static QString resolveIp(QString ip);
};

#endif // CONNECTION_H

#include "resolver.h"
#include <QMapIterator>

using namespace std;

Resolver::~Resolver() {
    delete _users;
    _users = nullptr;
}

/**
 * @brief Connection::findOrNewUser
 * @param username
 * @param ip
 * @return
 */
bool Resolver::findOrNewUser(QString username, QString ip) {
    auto it = Resolver::_users->find(username);
    if (it != end(*Resolver::_users))
        return ip == it.value();
    else
        Resolver::addUser(username, ip);
        return true;
}

QString Resolver::resolveUsername(QString username) {
    return Resolver::_users->find(username).key();
}

QString Resolver::resolveIp(QString ip) {
    QMap<QString, QString>::iterator i;
    for (i = Resolver::_users->begin(); i != Resolver::_users->end(); ++i)
        if (i.value() == ip)
            return i.value();
}

void Resolver::addUser(QString username, QString ip) {
    Resolver::_users->insert(username, ip);
}

QMap<QString, QString>* Resolver::_users = nullptr;

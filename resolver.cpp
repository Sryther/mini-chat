#include "resolver.h"
#include <map>

using namespace std;

/**
 * @brief Connection::findOrNewUser
 * @param username
 * @param ip
 * @return
 */
bool Resolver::findOrNewUser(QString username, QString ip) {
    auto it = Resolver::_users->find(ip);
    if (it != end(*Resolver::_users)) {
        return username == it.value();
    } else {
        Resolver::_users->insert(ip, username);
        return true;
    }
}

QString resolveUsername(QString username) {

}

QString resolveIp(QString ip) {

}

QMap<QString, QString>* Resolver::_users = nullptr;

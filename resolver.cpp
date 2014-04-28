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
    auto it = Resolver::_users->find(username);
    if (it != end(*Resolver::_users))
        return ip == it.value();
    else
        Resolver::_users->insert(username, ip);
        return true;
}

QString resolveUsername(QString username) {

}

QString resolveIp(QString ip) {

}

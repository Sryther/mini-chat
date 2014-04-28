#include "connection.h"
#include <map>

using namespace std;

/**
 * @brief Connection::findOrNewUser
 * @param username
 * @param ip
 * @return
 */
bool Connection::findOrNewUser(QString username, QString ip) {
    auto it = Connection::_users->find(ip);
    if (it != end(*Connection::_users)) {
        return username == it.value();
    } else {
        Connection::_users->insert(ip, username);
        return true;
    }
}

QMap<QString, QString>* Connection::_users = nullptr;

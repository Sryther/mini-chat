#include "userpersistent.h"
#include <exception>
#include <stdexcept>
#include <QString>
#include <QFile>

UserPersistent::UserPersistent() {
    _username = "";
    _port = 80;
}

UserPersistent* UserPersistent::getInstance() {
    if (UserPersistent::_instance == nullptr) {
        UserPersistent::_instance = new UserPersistent();
    }
    return UserPersistent::_instance;
}

void UserPersistent::savePersistent() {
    throw std::logic_error("not implemented");
}

void UserPersistent::loadPersistent() {
    throw std::logic_error("not implemented");
}

UserPersistent* UserPersistent::_instance = NULL;

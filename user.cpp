#include "user.h"
#include <exception>
#include <QString>

User::User() {
    _username = "";
    _port = 80;
}

User* User::getInstance() {
    if (User::_instance == nullptr) {
        User::_instance = new User();
    }
    return User::_instance;
}

void User::savePersistent() {
    throw std::logic_error("not implemented");
}

void User::loadPersistent() {
    throw std::logic_error("not implemented");
}

User* User::_instance = NULL;

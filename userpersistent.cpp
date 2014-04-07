#include "userpersistent.h"
#include <exception>
#include <stdexcept>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <ios>

UserPersistent::UserPersistent() {
    _username = "";
    _port = 80;
    _savefile = new QFile("settings.cfg");
}

UserPersistent::~UserPersistent() {
    _instance = nullptr;
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
    if (!_savefile->open(QIODevice::ReadOnly | QIODevice::Text))
        throw std::ios_base::failure("Unable to read file");

    QTextStream inputStream(_savefile);
    while ( !inputStream.atEnd() ) {
        QString line = inputStream.readLine();
        if (line.contains("username:")) {
            _username = line.split("username:")[1];
        } else if (line.contains("port:")) {
            _port = line.split("port:")[1].toInt();
        }
    }
    _savefile->close();
}

UserPersistent* UserPersistent::_instance = nullptr;

#include "userpersistent.h"
#include <exception>
#include <stdexcept>
#include <QString>
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <ios>
#include <QDir>
#include <QApplication>

UserPersistent::UserPersistent() {
    _username = "Anonym";
    _port = 80;
    _savefile = new QFile(qApp->applicationDirPath() + "/config.txt");
    if (_savefile->exists()) {
        loadPersistent();
    }
}

UserPersistent::~UserPersistent() {
    _instance = nullptr;
    _savefile = nullptr;
}

UserPersistent* UserPersistent::getInstance() {
    if (UserPersistent::_instance == nullptr) {
        UserPersistent::_instance = new UserPersistent();
    }
    return UserPersistent::_instance;
}

void UserPersistent::savePersistent() {
    if (!_savefile->open(QIODevice::WriteOnly | QIODevice::Text))
        throw std::ios_base::failure("Unable to write to file");

    QTextStream fileStream(_savefile);
    fileStream << ">> Mini-chat settings <<\n";
    fileStream << "username:" + _username + "\n";
    fileStream << "port:";
    fileStream << _port;
    fileStream << "\n";

    _savefile->close();
}

void UserPersistent::loadPersistent() {
    if (!_savefile->open(QIODevice::ReadOnly | QIODevice::Text))
        throw std::ios_base::failure("Unable to read file");

    QTextStream fileStream(_savefile);
    while ( !fileStream.atEnd() ) {
        QString line = fileStream.readLine();
        if (line.contains("username:")) {
            _username = line.split("username:")[1];
        } else if (line.contains("port:")) {
            _port = line.split("port:")[1].toInt();
        }
    }
    _savefile->close();
}

UserPersistent* UserPersistent::_instance = nullptr;

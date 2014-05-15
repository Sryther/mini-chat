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
#include <QDateTime>

UserPersistent::UserPersistent() {
    _username = "nouveau";
    _port = 8000;
    _savefile = new QFile(qApp->applicationDirPath() + "/config.txt");
    if (_savefile->exists()) {
        loadPersistent();
    } else {
        qsrand(QDateTime::currentDateTime().toTime_t());
        QString colors = "0123456789ABCDEF";
        _color = "#";
        for (int i = 0; i < 6; i++) {
            _color += QString(colors.at(qrand() % 16));
        }
        savePersistent();
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

void UserPersistent::delInstance() {
    if (UserPersistent::_instance) delete UserPersistent::_instance;
    UserPersistent::_instance = nullptr;
}

bool UserPersistent::hasInstance() {
    return UserPersistent::_instance != nullptr;
}

void UserPersistent::savePersistent() {
    if (!_savefile->open(QIODevice::WriteOnly | QIODevice::Text))
        throw std::ios_base::failure("Unable to write to file");

    QTextStream fileStream(_savefile);
    fileStream << ">> Mini-chat settings <<\n";
    fileStream << "username:" + _username + "\n";
    fileStream << "port:" + QString::number(_port) + "\n";
    fileStream << "color:" + _color + "\n";

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
        } else if (line.contains("color:")) {
            _color = line.split("color:")[1];
        }
    }
    _savefile->close();
}

UserPersistent* UserPersistent::_instance = nullptr;

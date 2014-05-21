#include "userpersistent.h"
#include <exception>
#include <stdexcept>
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <ios>
#include <QDir>
#include <QApplication>
#include <QDateTime>

/**
 * @brief UserPersistent::UserPersistent
 */
UserPersistent::UserPersistent() :
    _username("nouveau"),
    _port(8000),
    _savefile(new QFile(qApp->applicationDirPath() + "/config.txt"))
{
    if (_savefile->exists()) {
        _loadPersistent();
    } else {
        qsrand(QDateTime::currentDateTime().toTime_t());
        QString colors = "0123456789ABCDEF";
        _color = "#";
        for (int i = 0; i < 6; i++) {
            _color += QString(colors.at(qrand() % 16));
        }
        _savePersistent();
    }
}

/**
 * @brief UserPersistent::UserPersistent
 * @param other
 */
UserPersistent::UserPersistent(const UserPersistent &&other) {
    UserPersistent::_instance = other._instance;
    this->~UserPersistent();
}

/**
 * @brief UserPersistent::~UserPersistent
 */
UserPersistent::~UserPersistent() {
    if (_savefile) delete _savefile;
    _savefile = nullptr;
}

/**
 * @brief UserPersistent::getInstance
 * @return
 */
UserPersistent* UserPersistent::getInstance() {
    if (UserPersistent::_instance == nullptr) {
        UserPersistent::_instance = new UserPersistent();
    }
    return UserPersistent::_instance;
}

/**
 * @brief UserPersistent::delInstance
 */
void UserPersistent::delInstance() {
    if (UserPersistent::_instance) delete UserPersistent::_instance;
    UserPersistent::_instance = nullptr;
}

/**
 * @brief UserPersistent::hasInstance
 * @return
 */
bool UserPersistent::hasInstance() {
    return UserPersistent::_instance != nullptr;
}

/**
 * @brief UserPersistent::savePersistent
 */
void UserPersistent::savePersistent() {
    UserPersistent::getInstance()->_savePersistent();
}

/**
 * @brief UserPersistent::_savePersistent
 */
void UserPersistent::_savePersistent() {
    if (!_savefile->open(QIODevice::WriteOnly | QIODevice::Text))
        throw std::ios_base::failure("Unable to write to file");

    QTextStream fileStream(_savefile);
    fileStream << ">> Mini-chat settings <<\n";
    fileStream << "username:" + _username + "\n";
    fileStream << "port:" + QString::number(_port) + "\n";
    fileStream << "color:" + _color + "\n";
    fileStream << "server:" + _serverIp + "\n";

    _savefile->close();
}

/**
 * @brief UserPersistent::_loadPersistent
 */
void UserPersistent::_loadPersistent() {
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
        } else if (line.contains("server:")) {
            _serverIp = line.split("server:")[1];
        }
    }
    _savefile->close();
}

/**
 * @brief UserPersistent::loadPersistent
 */
void UserPersistent::loadPersistent() {
    UserPersistent::getInstance()->_loadPersistent();
}

/**
 * @brief UserPersistent::getColor
 * @return
 */
QString UserPersistent::getColor() {
    return UserPersistent::getInstance()->_color;
}

/**
 * @brief UserPersistent::getServerIp
 * @return
 */
QString UserPersistent::getServerIp() {
    return UserPersistent::getInstance()->_serverIp;
}

/**
 * @brief UserPersistent::getPort
 * @return
 */
int UserPersistent::getPort() {
    return UserPersistent::getInstance()->_port;
}

/**
 * @brief UserPersistent::getUsername
 * @return
 */
QString UserPersistent::getUsername() {
    return UserPersistent::getInstance()->_username;
}

/**
 * @brief UserPersistent::setColor
 * @param color
 */
void UserPersistent::setColor(QString color) {
    UserPersistent::getInstance()->_color = color;
}

/**
 * @brief UserPersistent::setServerIp
 * @param ip
 */
void UserPersistent::setServerIp(QString ip) {

    UserPersistent::getInstance()->_serverIp = ip;
}

/**
 * @brief UserPersistent::setPort
 * @param port
 */
void UserPersistent::setPort(int port) {
    UserPersistent::getInstance()->_port = port;
}

/**
 * @brief UserPersistent::setUsername
 * @param username
 */
void UserPersistent::setUsername(QString username) {
    UserPersistent::getInstance()->_username = username;
}

UserPersistent* UserPersistent::_instance = nullptr;

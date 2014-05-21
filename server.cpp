#include "server.h"
#include "message.h"
#include "userpersistent.h"
#include <QtNetwork>
#include <exception>

using namespace std;

/**
 * @brief Server::Server
 * @param mainwindow
 */
Server::Server(MainWindow *mainwindow) :
      _mainwindow(mainwindow),
      _udpSocket(new QUdpSocket(this)),
      _udpReceiverSocket(new QUdpSocket(this))
{
    _udpReceiverSocket->bind(UserPersistent::getPort(), QUdpSocket::ShareAddress);
    connect(_udpReceiverSocket, SIGNAL(readyRead()),this, SLOT(processPendingDatagrams()));
}

/**
 * @brief Server::Server
 * @param other
 */
Server::Server(const Server &&other)
{
    Server::_instance = other._instance;
    this->~Server();
}

/**
 * @brief Server::~Server
 */
Server::~Server() {
    _udpSocket->close();
    _udpReceiverSocket->close();
    _mainwindow = nullptr;
    if (_udpSocket) delete _udpSocket;
    _udpSocket = nullptr;
    if (_udpReceiverSocket) delete _udpReceiverSocket;
    _udpReceiverSocket = nullptr;
}

/**
 * @brief Server::getInstance
 * @param mainwindow
 * @return
 */
void Server::create(MainWindow *mainwindow) {
    if (Server::_instance == nullptr) {
        Server::_instance = new Server(mainwindow);
    }
}

Server* Server::getInstance() {
    if (Server::_instance) {
        return Server::_instance;
    } else {
        throw logic_error("Server is not running");
    }
}

/**
 * @brief Server::delInstance
 */
void Server::delInstance() {
    if (Server::_instance) delete Server::_instance;
    Server::_instance = nullptr;
}

/**
 * @brief Server::sendMessage
 * @param message
 * @return
 */
bool Server::sendMessage(Message message, bool system) {
    QString texte = "";
    if (system) {
        message.setUsername("system");
        message.setColor("#DFAF2C");
        message.setContent("*" + message.getContent() + "*");
    }
    for (auto c : message.toQString()) {
        QChar encode = _instance->rot(c, (_instance->_decal % 26));
        texte.append(encode);
    }
    QByteArray data = texte.toUtf8();
    QHostAddress to = QHostAddress(message.getDestination());
    _instance->_udpSocket->writeDatagram(data, to, UserPersistent::getPort());
    return true;
}

/**
 * @brief Server::changePort
 */
void Server::changePort() {
    _instance->_udpReceiverSocket->close();
    _instance->_udpReceiverSocket->bind(UserPersistent::getPort(), QUdpSocket::ShareAddress);
    _instance->_udpReceiverSocket->open(QIODevice::ReadOnly);
}

/**
 * @brief Server::hasInstance
 * @return
 */
bool Server::hasInstance() {
    return Server::_instance != nullptr;
}

/**
 * @brief Server::processPendingDatagrams
 */
void Server::processPendingDatagrams()
{
    while (_udpReceiverSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(_udpReceiverSocket->pendingDatagramSize());
        QHostAddress from;
        _udpReceiverSocket->readDatagram(datagram.data(), datagram.size(), &from);
        QString datas = datagram.data();
        QString texte = "";
        for (auto c : datas) {
            QChar decode = rot(c, 26 - (_decal % 26));
            texte.append(decode);
        }
        Message message = Message(texte);
        message.setContent(message.getContent().replace(Message::getReplaceTag(), from.toString()));
        message.setSender(from.toString());
        _mainwindow->appendMessage(message);
    }
}

/**
 * @brief Server::rot
 * @param letter
 * @param decal
 * @return
 */
QChar Server::rot(QChar letter, int decal) {
    char c = letter.toLatin1();
    if (c >= 'A' && c <= 'Z') {
        return ((c - 'A' + decal) % 26) + 'A';
    } else if (c >= 'a' && c <= 'z') {
        return ((c - 'a' + decal) % 26) + 'a';
    } else {
        return letter;
    }
}

Server* Server::_instance = nullptr;

#include "server.h"
#include "resolver.h"
#include "message.h"
#include "userpersistent.h"
#include <QtNetwork>
#include <QTcpSocket>
#include <QUdpSocket>
#include <exception>

using namespace std;

Server::Server(MainWindow *mainwindow)
      : _mainwindow(mainwindow)
{
    _udpSocket = new QUdpSocket(this);
    _udpReceiverSocket = new QUdpSocket(this);
    _udpReceiverSocket->bind(UserPersistent::getPort(), QUdpSocket::ShareAddress);
    connect(_udpReceiverSocket, SIGNAL(readyRead()),this, SLOT(processPendingDatagrams()));
}

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
 * @return
 */
Server* Server::getInstance(MainWindow *mainwindow) {
    if (Server::_instance == nullptr) {
        Server::_instance = new Server(mainwindow);
    }
    return Server::_instance;
}

void Server::delInstance() {
    if (Server::_instance) delete Server::_instance;
    Server::_instance = nullptr;
}

/**
 * @brief Server::prepareMessage
 * @param messageText
 */
void Server::prepareMessage(QString messageText)
{
    if (messageText.isEmpty())
        return;

    QString username = UserPersistent::getUsername();
    QString color = UserPersistent::getColor();
    QString from = "127.0.0.1"; // TODO: Change for a real wan ip
    QMap<QString, QString>::iterator i;
    for (i = Resolver::_users->begin(); i != Resolver::_users->end(); ++i) {
        Message message = Message(username, color, from, messageText, i.value());
        if (!this->sendMessage(message)) {
            break; // TODO: Exception
        }
    }
}

/**
 * @brief Server::sendMessage
 * @param message
 * @return
 */
bool Server::sendMessage(Message message) {
    QString texte = "";
    for (auto c : message.toQString()) {
        QChar encode = rot(c, (_decal % 26));
        texte.append(encode);
    }
    QByteArray data = texte.toUtf8();
    QHostAddress to = QHostAddress(message.getDestination());
    _udpSocket->writeDatagram(data, to, UserPersistent::getPort());
    return true;
}

void Server::changePort() {
    _udpReceiverSocket->close();
    _udpReceiverSocket->bind(UserPersistent::getPort(), QUdpSocket::ShareAddress);
    _udpReceiverSocket->open(QIODevice::ReadOnly);
}

bool Server::hasInstance() {
    return Server::_instance != nullptr;
}

void Server::processPendingDatagrams()
{
    while (_udpReceiverSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(_udpReceiverSocket->pendingDatagramSize());
        _udpReceiverSocket->readDatagram(datagram.data(), datagram.size());
        QString message = datagram.data();
        QString texte = "";
        for (auto c : message) {
            QChar decode = rot(c, 26 - (_decal % 26));
            texte.append(decode);
        }
        _mainwindow->appendMessage(Message(texte));
    }
}

QChar Server::rot(QChar letter, int decal) {
    char c = letter.toLatin1();
    if (c >= 'A' && c <= 'Z') {
        return ((c - 'A' + decal) % 26) + 'A';
    } else if (c >= 'a' && c <= 'z') {
        return ((c - 'a' + decal) % 26) + 'a';
    } else {
        return c;
    }
}

Server* Server::_instance = nullptr;

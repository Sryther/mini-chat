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
      : _server(0),
        _mainwindow(mainwindow)
{
    _udpSocket = new QUdpSocket(this);
    _udpReceiverSocket = new QUdpSocket(this);
    _udpReceiverSocket->bind(UserPersistent::getInstance()->getPort(), QUdpSocket::ShareAddress);
    connect(_udpReceiverSocket, SIGNAL(readyRead()),this, SLOT(processPendingDatagrams()));
}

Server::~Server() {
    _instance = nullptr;
    _mainwindow = nullptr;
    _udpSocket->close();
    _udpReceiverSocket->close();
    delete _udpSocket;
    delete _udpReceiverSocket;
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

/**
 * @brief Server::prepareMessage
 * @param messageText
 */
void Server::prepareMessage(QString messageText)
{
    if (messageText.isEmpty())
        return;

    QString username = UserPersistent::getInstance()->getUsername();
    QString color = UserPersistent::getInstance()->getColor();
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
    QByteArray data = message.toQString().toUtf8();
    QHostAddress to = QHostAddress(message.getDestination());
    _udpSocket->writeDatagram(data, to, UserPersistent::getInstance()->getPort());
    return true;
}

void Server::changePort(int port) {
    _udpReceiverSocket->close();
    _udpReceiverSocket->bind(UserPersistent::getInstance()->getPort(), QUdpSocket::ShareAddress);
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
        _mainwindow->appendMessage(Message(datagram.data()));
    }
}

Server* Server::_instance = nullptr;

#include "server.h"
#include "message.h"
#include "userpersistent.h"
#include <QtNetwork>
#include <QTcpSocket>
#include <QUdpSocket>
#include <exception>
#include <QMessageBox>

using namespace std;

/**
 * @brief Server::Server
 * @param mainwindow
 */
Server::Server(MainWindow *mainwindow) :
      _mainwindow(mainwindow),
      _udpSocket(new QUdpSocket()),
      _udpReceiverSocket(new QUdpSocket()),
      _udpProbeSocket(new QUdpSocket()),
      _timer(new QTimer),
      _peers(QMap<QString, QString>())
{
    connect(_timer, SIGNAL(timeout()), this, SLOT(probePeers()));
    _timer->start(_cooldown);
    _udpReceiverSocket->bind(UserPersistent::getPort(), QUdpSocket::ShareAddress);
    connect(_udpReceiverSocket, SIGNAL(readyRead()),this, SLOT(processPendingDatagrams()));
    sendProbe();
}

/**
 * @brief Server::~Server
 */
Server::~Server() {
    _udpSocket->close();
    _udpReceiverSocket->close();
    _udpProbeSocket->close();
    _mainwindow = nullptr;
    if (_timer) delete _timer;
    _timer = nullptr;
    if (_udpSocket) delete _udpSocket;
    _udpSocket = nullptr;
    if (_udpReceiverSocket) delete _udpReceiverSocket;
    _udpReceiverSocket = nullptr;
    if (_udpProbeSocket) delete _udpProbeSocket;
    _udpProbeSocket = nullptr;
}

/**
 * @brief Server::create
 * @param mainwindow
 */
void Server::create(MainWindow *mainwindow) {
    if (Server::_instance == nullptr) {
        Server::_instance = new Server(mainwindow);
    }
}

/**
 * @brief Server::getInstance
 * @return _instance
 */
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
 */
void Server::sendMessage(Message message, bool system) {
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
 * @return if Server is instantiated
 */
bool Server::hasInstance() {
    return Server::_instance != nullptr;
}

/**
 * @brief Server::probePeers every 5s
 */
void Server::probePeers() {
    sendProbe();
}

/**
 * @brief Server::sendProbe send a probe message on udp
 */
void Server::sendProbe() {
    QByteArray data = ("probe:" + UserPersistent::getUsername()).toUtf8();
    QHostAddress to = QHostAddress("255.255.255.255");
    _udpProbeSocket->writeDatagram(data, to, UserPersistent::getPort());
}

/**
 * @brief Server::receiveProbe store new peers
 */
void Server::receiveProbe(QString username, QHostAddress ip) {
    if (_peers.contains(ip.toString())) return;
    _peers.insert(ip.toString(), username);
}

/**
 * @brief Server::processPendingDatagrams recover udp messages
 */
void Server::processPendingDatagrams()
{
    while (_udpReceiverSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(_udpReceiverSocket->pendingDatagramSize());
        QHostAddress from;
        _udpReceiverSocket->readDatagram(datagram.data(), datagram.size(), &from);
        QString datas = datagram.data();
        if (datas.split("probe:").length() == 2) {
            QString username = datas.split("probe:")[1];
            receiveProbe(username, from);
            QString deb = "";
            for (auto i : _peers.keys()) {
                deb += i + ":" + _peers[i] + "\n";
            }
            QMessageBox* box = new QMessageBox();
            box->critical(NULL, "Critical error", deb);
            delete box;
            box = nullptr;
        } else {
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
}

/**
 * @brief Server::rot
 * @param letter
 * @param decal
 * @return letter rot decal
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

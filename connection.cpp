#include "connection.h"
#include <QtNetwork>
#include <map>

using namespace std;

static const int TransferTimeout = 30 * 1000;
static const int PongTimeout = 60 * 1000;
static const int PingInterval = 5 * 1000;
static const char SeparatorToken = ' ';

/**
 * @brief Connection::Connection
 */
Connection::Connection(QObject *parent)
    : QTcpSocket(parent)
{
    _helloMessage = "undefined";
    _isHelloSent = false;
    _users = new QMap<QString, QString>();
}

bool Connection::findOrNewUser(QString username, QString ip) {
    auto it = Connection::_users->find(ip);
    if (it != end(*Connection::_users)) {
        return username == it.value();
    } else {
        Connection::_users->insert(ip, username);
        return true;
    }
}

void Connection::setHelloMessage(const QString &message) {
    _helloMessage = message;
}

void Connection::sendPing()
{
    if (_pongTime.elapsed() > PongTimeout) {
        abort();
        return;
    }

    //write("PING 1 p");
}


void Connection::sendHelloMessage()
{
    QByteArray hello = _helloMessage.toUtf8();
    QByteArray data = "HELLO " + QByteArray::number(hello.size()) + ' ' + hello;
    if (write(data) == data.size()) {
        _isHelloSent = true;
    }
}

QMap<QString, QString>* Connection::_users = nullptr;

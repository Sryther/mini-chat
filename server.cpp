#include "server.h"
#include "resolver.h"
#include "message.h"
#include "userpersistent.h"
#include <QtNetwork>

using namespace std;

Server::Server()
    : _server(0)
{
    listen(QHostAddress::Any);
}

Server::~Server() {
    Server::_instance = nullptr;
}

/**
 * @brief Server::getInstance
 * @return
 */
Server* Server::getInstance() {
    if (Server::_instance == nullptr) {
        Server::_instance = new Server();
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
    QString to = message.getDestination();
    return true;
}

Server* Server::_instance = nullptr;

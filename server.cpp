#include "server.h"
#include "connection.h"
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

void Server::incomingConnection(qintptr socketDescriptor)
{
    Connection *connection = new Connection(this);
    connection->setSocketDescriptor(socketDescriptor);
    emit newConnection(connection); // emit a new connection signal
}

Server* Server::_instance = nullptr;

#include "server.h"
#include "resolver.h"
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

Server* Server::_instance = nullptr;

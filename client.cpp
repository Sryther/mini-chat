#include "client.h"
#include "connection.h"
#include "server.h"
#include <QtNetwork>

Client::Client()
{

}

Client::~Client() {
    _instance = nullptr;
}

Client* Client::getInstance() {
    if (Client::_instance == nullptr) {
        Client::_instance = new Client();
    }
    return Client::_instance;
}

void Client::sendMessage(Message message)
{
    if (!message.isValid())
        return;

    /* TODO : recuperer les pairs
    foreach (peers)
        connection->sendMessage(message);
    */
}

void Client::disconnect() {

}

Client* Client::_instance = nullptr;

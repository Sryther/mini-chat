#ifndef CLIENT_H
#define CLIENT_H

#include <QAbstractSocket>
#include <QHash>
#include <QHostAddress>
#include "message.h"

class Client {
private:
    Client();
    ~Client();
    static Client* _instance;
public:
    static Client* getInstance();
    void sendMessage(Message message);
    void disconnect();
private:
    QString _ip;
};

#endif // CLIENT_H

#ifndef SERVER_H
#define SERVER_H
#include <QTcpServer>
#include <QObject>
#include <QString>
#include "message.h"

using namespace std;

class Connection;

class Server : protected QTcpServer
{
    Q_OBJECT
private:
    Server();
    ~Server();
    static Server* _instance;
public:
    static Server* getInstance();
    void prepareMessage(QString messageText);
signals:
    void newConnection(Connection *connection);
private:
    bool sendMessage(Message message);
    QTcpServer _server;
};

#endif // SERVER_H

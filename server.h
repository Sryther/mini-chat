#ifndef SERVER_H
#define SERVER_H
#include <QTcpServer>
#include <QObject>

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
signals:
    void newConnection(Connection *connection);
private:
    void incomingConnection(qintptr socketDescriptor);
    QTcpServer _server;
};

#endif // SERVER_H

#ifndef SERVER_H
#define SERVER_H
#include <QTcpServer>
#include <QObject>

using namespace std;

class Connection;

class Server : public QTcpServer
{
    Q_OBJECT

    public:
        static Server* getInstance();
    signals:
        void newConnection(Connection *connection);
    private:
        void incomingConnection(qintptr socketDescriptor);
        Server(QObject *parent = 0);
        QTcpServer _server;
        static Server* _instance;
        ~Server();
};

#endif // SERVER_H

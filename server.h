#ifndef SERVER_H
#define SERVER_H
#include <QTcpServer>
#include <QTcpSocket>
#include <QUdpSocket>
#include <QObject>
#include <QString>
#include "message.h"
#include "mainwindow.h"

using namespace std;

class Connection;

class Server : protected QTcpServer
{
    Q_OBJECT
private:
    Server(MainWindow *mainwindow);
    ~Server();
    static Server* _instance;
    MainWindow* _mainwindow;
    QUdpSocket* _udpSocket;
    QUdpSocket* _udpReceiverSocket;
public:
    static Server* getInstance(MainWindow *mainwindow);
    void prepareMessage(QString messageText);
    bool sendMessage(Message message);
    void changePort(int port);
    static bool hasInstance();
signals:
    void newConnection(Connection *connection);
private slots:
    void processPendingDatagrams();
private:
    QTcpServer _server;
};

#endif // SERVER_H

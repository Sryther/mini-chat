#ifndef SERVER_H
#define SERVER_H
#include <QTcpServer>
#include <QTcpSocket>
#include <QUdpSocket>
#include <QObject>
#include <QString>
#include <QTimer>
#include <QMap>
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
    QUdpSocket* _udpProbeSocket;
    QTimer* _timer;
    QMap<QString, QString> _peers;
    int _cooldown = 5000;
public:
    static void create(MainWindow *mainwindow);
    static bool hasInstance();
    static Server* getInstance();
    static void delInstance();
    static void sendMessage(Message message, bool system = false);
    void sendProbe();
    void receiveProbe(QString username, QHostAddress ip);
    static void changePort();
private slots:
    void probePeers();
    void processPendingDatagrams();
private:
    int _decal = 42;
    QChar rot(QChar letter, int decal);
};

#endif // SERVER_H

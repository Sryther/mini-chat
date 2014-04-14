#ifndef CONNECTION_H
#define CONNECTION_H

#include <QString>
#include <QMap>
#include <QTcpSocket>
#include <QTimer>
#include <QTime>

using namespace std;

class Connection : public QTcpSocket
{
    Q_OBJECT
    public:
        Connection(QObject *parent = 0);
        bool static findOrNewUser(QString username, QString ip);
    private:
        void setHelloMessage(const QString &message);
        void sendHelloMessage();
        void sendPing();

        static QMap<QString, QString>* _users;
        QString _helloMessage;
        bool _isHelloSent;
        QTimer _pingTimer;
        QTime _pongTime;
};


#endif // CONNECTION_H

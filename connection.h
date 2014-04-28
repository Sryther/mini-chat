#ifndef CONNECTION_H
#define CONNECTION_H

#include <QString>
#include <QMap>
#include <QTcpSocket>
#include <QTimer>
#include <QTime>
#include "message.h"
#include "connection.h"

using namespace std;

class Connection : public QTcpSocket
{
    Q_OBJECT
    public:
        Connection(QObject *parent = 0);
        bool static findOrNewUser(QString username, QString ip);
};


#endif // CONNECTION_H

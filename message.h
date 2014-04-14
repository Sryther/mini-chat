#ifndef MESSAGE_H
#define MESSAGE_H

#include <QStringList>
#include <QAbstractSocket>
#include <map>
#include <QHostAddress>
#include <QString>

using namespace std;

class Message
{
    public:
        uint timestamp;

        Message(QString username, QString from, QString content, QString to);
        QString toQString();
        static QStringList parse(QString formattedString);
        static bool isValid(QStringList params);
        static const QString& getSeparator() { static QString separator("\x0001"); return separator; }
        QString getSender();
        QString getContent();
        QString getUsername();
        QString getDestination();
    private:
        map<QString, QHostAddress> _users;
        QString _from;
        QString _to;
        QString _username;
        QString _content;
};

#endif // MESSAGE_H

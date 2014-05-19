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
        uint _timestamp;

        Message(QString username, QString color, QString from, QString content, QString to);
        Message(QString formattedString);
        QString toQString();
        static QStringList parse(QString formattedString);
        static bool isValid(QStringList params);
        bool isValid();
        static const QString& getSeparator() { static QString separator("\x0001"); return separator; }
        QString getSender() { return _from; }
        void setSender(QString from) { _from = from; }
        QString getContent() { return _content; }
        QString getUsername() { return _username; }
        void setUsername(QString username) { _username = username; }
        QString getColor() { return _color; }
        void setColor(QString color) { _color = color; }
        QString getDestination() { return _to; }
        uint getTimestamp() { return _timestamp; }
    private:
        map<QString, QHostAddress> _users;
        QString _from;
        QString _to;
        QString _username;
        QString _content;
        QString _color;
};

#endif // MESSAGE_H

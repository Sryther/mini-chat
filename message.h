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

        Message(QString username, QString color, QString from, QString content, QString to);
        QString toQString();
        static QStringList parse(QString formattedString);
        static bool isValid(QStringList params);
        bool isValid();
        static const QString& getSeparator() { static QString separator("\x0001"); return separator; }
        QString getSender() { return _from; };
        QString getContent() { return _content; };
        QString getUsername() { return _username; };
        QString getColor() { return _color; };
        QString getDestination() { return _to; };
    private:
        map<QString, QHostAddress> _users;
        QString _from;
        QString _to;
        QString _username;
        QString _content;
        QString _color;
};

#endif // MESSAGE_H

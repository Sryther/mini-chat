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
        static const QString& getReplaceTag() { static QString tag("\x0002"); return tag; }

        QString getSender() { return _from; }
        QString getContent() { return _content; }
        QString getUsername() { return _username; }
        QString getColor() { return _color; }
        QString getDestination() { return _to; }
        uint getTimestamp() { return _timestamp; }

        void setSender(QString from) { _from = from; }
        void setContent(QString content) { _content = content; }
        void setUsername(QString username) { _username = username; }
        void setColor(QString color) { _color = color; }

        static QString paint(QString text, QString color, QString title = "");

    private:
        QString _from;
        QString _to;
        QString _username;
        QString _content;
        QString _color;
};

#endif // MESSAGE_H

#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>
#include <QStringList>
#include <QAbstractSocket>

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
        QString from;
        QString to;
        QString username;
        QString content;
};

#endif // MESSAGE_H

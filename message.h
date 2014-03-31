#ifndef MESSAGE_H
#define MESSAGE_H

#include <QVector>
#include <QString>
#include <QStringList>

using namespace std;

class Message
{
    public:
        int timestamp;
        QString from;
        QString to;
        QString username;
        QString content;

        Message();
        Message(QString username, QString from, QString content);
        QString toString();
        static QStringList parse(QString formattedString);
        static const QString& getSeparator() { static QString separator("\x0001"); return separator; }
    private:
};

#endif // MESSAGE_H

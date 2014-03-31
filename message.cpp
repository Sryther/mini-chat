#include "message.h"
#include <QString>
#include <QVector>
#include <QStringList>

using namespace std;

/**
 * @brief Message::Message
 */
Message::Message() {

}

/**
 * @brief Message::Message
 * @param formatedString
 */
Message::Message(QString username, QString from, QString content) {
    Message::username = username;
    Message::from = from;
    Message::content = content;
}

/**
 * @brief Message::parse
 * @param formatedString
 * @return QStringList
 */
QStringList Message::parse(QString formatedString) {
    QStringList strings;
    strings = formatedString.split(Message::getSeparator());
    return strings;
}

/**
 * @brief Message::toString
 * @return Qstring
 */
QString Message::toString() {
    QString str = username;
    str.append(Message::getSeparator());
    str.append(from);
    str.append(Message::getSeparator());
    str.append(content);
    return str;
}

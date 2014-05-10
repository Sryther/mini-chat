#include "message.h"
#include <QDateTime>
#include <exception>
#include <stdexcept>

using namespace std;

/**
 * @brief Message::Message
 * @param username
 * @param from Sender's IP
 * @param content
 * @param to Destination IP 0.0.0.0 <=> broadcast
 */
Message::Message(QString username, QString color, QString from, QString content, QString to = "0.0.0.0") :
    _username(username),
    _color(color),
    _from(from),
    _content(content),
    _to(to),
    _timestamp(QDateTime::currentDateTime().toTime_t())
{

}

/**
 * @brief Message::Message
 * @param formattedString
 */
Message::Message(QString formattedString) {
    QStringList list = this->parse(formattedString);
    _username = list[0];
    _color = list[1];
    _from = list[2];
    _content = list[3];
    _to = list[4];
    _timestamp = QDateTime::currentDateTime().toTime_t();
}

/**
 * @brief Message::parse
 * @param formatedString
 * @return QStringList
 */
QStringList Message::parse(QString formatedString) {
    QStringList strings;
    strings = formatedString.split(Message::getSeparator()); // Split into three elements
    return strings;
}

bool Message::isValid(QStringList params) {
    try {
        QHostAddress host = QHostAddress(params[1]); // Is a valid IP Address
        if (params[0].isEmpty() || params[2].isEmpty() ) { // Check if a QString is empty
            return false;
        }
        return true;
    } catch(exception &e) {
        e.what();
        return false;
    }
}

bool Message::isValid() {
    try {
        QHostAddress host = QHostAddress(_from); // Is a valid IP Address
        if (_username.isEmpty() || _content.isEmpty() ) { // Check if a QString is empty
            return false;
        }
        return true;
    } catch(exception &e) {
        e.what();
        return false;
    }
}

/**
 * @brief Message::toString
 * @return QString
 */
QString Message::toQString() {
    QString str = _username;
    str.append(getSeparator());
    str.append(_color);
    str.append(getSeparator());
    str.append(_from);
    str.append(getSeparator());
    str.append(_content);

    return str;
}

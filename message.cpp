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
Message::Message(QString username, QString from, QString content, QString to = "0.0.0.0") :
    _username(username),
    _from(from),
    _content(content),
    _to(to)
{
    Message::timestamp = QDateTime::currentDateTime().toTime_t(); // Returns the current timestamp
}

/**
 * @brief Message::getSender
 * @return QString
 */
QString Message::getSender() {
    return _from;
}

/**
 * @brief Message::getContent
 * @return QString
 */
QString Message::getContent() {
    return _content;
}

/**
 * @brief Message::getUsername
 * @return QString
 */
QString Message::getUsername() {
    return _username;
}

/**
 * @brief Message::getReceiver
 * @return QString
 */
QString Message::getDestination() {
    return _to;
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
    str.append(_from);
    str.append(getSeparator());
    str.append(_content);

    return str;
}

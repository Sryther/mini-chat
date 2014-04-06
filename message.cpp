#include "message.h"
#include <QString>
#include <QStringList>
#include <QDateTime>
#include <QHostAddress>
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
Message::Message(QString username, QString from, QString content, QString to = "0.0.0.0") {
    Message::username = username;
    Message::from = from;
    Message::content = content;
    Message::to = to;
    Message::timestamp = QDateTime::currentDateTime().toTime_t(); // Returns the current timestamp
}

/**
 * @brief Message::getSender
 * @return QString
 */
QString Message::getSender() {
    return Message::from;
}

/**
 * @brief Message::getContent
 * @return QString
 */
QString Message::getContent() {
    return Message::content;
}

/**
 * @brief Message::getUsername
 * @return QString
 */
QString Message::getUsername() {
    return Message::username;
}

/**
 * @brief Message::getReceiver
 * @return QString
 */
QString Message::getDestination() {
    return Message::to;
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

/**
 * @brief Message::toString
 * @return QString
 */
QString Message::toQString() {
    QString str = Message::username;
    str.append(Message::getSeparator());
    str.append(Message::from);
    str.append(Message::getSeparator());
    str.append(Message::content);
    return str;
}

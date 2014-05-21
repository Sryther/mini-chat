#include "message.h"
#include <QDateTime>
#include <exception>
#include <stdexcept>

using namespace std;

/**
 * @brief Message::Message
 * @param username
 * @param from
 * @param content
 * @param to
 */
Message::Message(QString username, QString color, QString from, QString content, QString to = "255.255.255.255") :
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
Message::Message(QString formattedString) :
    _timestamp(QDateTime::currentDateTime().toTime_t())
{
    QStringList list = Message::parse(formattedString);
    _username = list[0];
    _color = list[1];
    _from = list[2];
    _content = list[3];
    _to = list[4];
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
 * @brief Message::isValid
 * @param params
 * @return
 */
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
 * @brief Message::isValid
 * @return
 */
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
    str.append(getSeparator());
    str.append(_to);

    return str;
}

QString Message::paint(QString text, QString color, QString title){
    if (title.length() == 0){
        return "<span style='font-weight:bold; color:" + color + "'>" + text + "</span>";
    }
    else {
        return "<span style='font-weight:bold; color:" + color + "' title='" + title + "'>" + text + "</span>";
    }
}

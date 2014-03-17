#include "message.h"

int timestamp;
string from;
string to;
string username;
string content;

Message::Message() {

}

Message::toString() {
    return username + '☺' + host + '☺' + content;
}

Message::~Message() {

}

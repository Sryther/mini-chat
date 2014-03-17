#include "message.h"
#include <string>

using namespace std;

Message::Message() {

}

Message::Message(string formattedString) {
    // TODO split the string.
}

string Message::toString() {
    return username + Message::getSeparator() + from + Message::getSeparator() + content;
}

#include "message.h"
#include <string>
#include <vector>
#include <string>

using namespace std;

Message::Message() {

}

Message::Message(string formattedString) {
    // TODO split the string.

}

vector<string> Message::splitFormattedString(string formattedString) {

}

string Message::toString() {
    return username + Message::getSeparator() + from + Message::getSeparator() + content;
}

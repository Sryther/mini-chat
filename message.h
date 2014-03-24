#ifndef MESSAGE_H
#define MESSAGE_H

#include <vector>
#include <string>

using namespace std;

class Message
{
    public:
        int timestamp;
        string from;
        string to;
        string username;
        string content;

        Message();
        Message(string formatedString);
        string toString();
    private:
        static const string& getSeparator() { static string separator("\x0001"); return separator; }
        vector<string> splitFormatedString(string formattedString);
};

#endif // MESSAGE_H

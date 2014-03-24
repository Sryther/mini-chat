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
        Message(string formattedString);
        string toString();
    private:
        static const string& getSeparator() { static string separator("\x0001"); return separator; }
        vector<string> splitFormattedString(string formattedString);
};

#endif // MESSAGE_H

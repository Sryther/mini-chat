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
<<<<<<< HEAD
        Message(string formatedString);
        string toString();
    private:
        static const string& getSeparator() { static string separator("\x0001"); return separator; }
        vector<string> splitFormatedString(string formattedString);
=======
        Message(string formattedString);
        string toString();
    private:
        static const string& getSeparator() { static string separator("\x0001"); return separator; }
        vector<string> splitFormattedString(string formattedString);
>>>>>>> eadb6912df799fbe505ebc3e74e8197b7c5df513
};

#endif // MESSAGE_H

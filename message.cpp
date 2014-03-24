#include "message.h"
#include <string>
#include <vector>
#include <string>

using namespace std;

<<<<<<< HEAD
/**
 * @brief Message::Message
 */
=======
>>>>>>> eadb6912df799fbe505ebc3e74e8197b7c5df513
Message::Message() {

}

<<<<<<< HEAD
/**
 * @brief Message::Message
 * @param formatedString
 */
Message::Message(string formatedString) {
    vector<string> strings = splitFormatedString(formatedString);

    username = strings[0];
    from = strings[1];
    content = strings[2];
}

/**
 * @brief Message::splitFormatedString
 * @param formatedString
 * @return vector<string>
 */
vector<string> Message::splitFormatedString(string formatedString) {
    vector<string> strings;
    string::size_type posTmp = formatedString.find(getSeparator()); //Recupere la position de la premiere occurence du separateur

    while(posTmp != string::npos) {
        strings.push_back(formatedString.substr(0, posTmp));    // Ajoute au vecteur la chaine avant le separateur
        formatedString = formatedString.substr(posTmp + 1); // Retourne la suite de la chaine (suppression de la partie precedente et du separateur precedent
        posTmp = formatedString.find(getSeparator());   // Recupere la position de l'occurence suivante du separateur, si pas d'occurence renvoie string::npos
    }

    return strings;
}

/**
 * @brief Message::toString
 * @return string
 */
=======
Message::Message(string formattedString) {
    // TODO split the string.

}

vector<string> Message::splitFormattedString(string formattedString) {

}

>>>>>>> eadb6912df799fbe505ebc3e74e8197b7c5df513
string Message::toString() {
    return username + Message::getSeparator() + from + Message::getSeparator() + content;
}

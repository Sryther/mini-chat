#ifndef USER_H
#define USER_H

#include <QString>

class User
{
private:
    User();
    ~User();
    static User* _instance;
public:
    static User* getInstance();

private:
    QString _username;
    int _port;
public:
    QString getUsername() { return _username; };
    void setUsername(QString username) { _username = username; };

    int getPort() { return _port; };
    void setPort(int port) { _port = port; };

    void savePersistent();
    void loadPersistent();
};

#endif // USER_H

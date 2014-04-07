#ifndef USER_H
#define USER_H

#include <QString>

class UserPersistent
{
private:
    UserPersistent();
    ~UserPersistent();
    static UserPersistent* _instance;
public:
    static UserPersistent* getInstance();

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

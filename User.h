#ifndef USER_H
#define USER_H
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
using namespace std;

//======================= CLASS USER ==========================
class User {
protected:
    string userid;
    string fullName;
    string email;
    string password;

public:
    User(string id, string name, string mail, string pass);
    virtual ~User() = default;
    virtual bool login(string mail, string pass);
    virtual void logout();
    virtual void updateProfile(string name, string pass);
    virtual bool isAdmin() const = 0;
    string getEmail() const;
    string getName() const;
    string getUserId() const;
};
#endif

#include "User.h"
#include <iostream>
using namespace std;

User::User(string id, string name, string mail, string pass)
    : userid(id), fullName(name), email(mail), password(pass) {
}

bool User::login(string mail, string pass) {
    return (email == mail && password == pass);
}

void User::logout() {
    cout << fullName << " da dang xuat." << endl;
}

void User::updateProfile(string name, string pass) {
    fullName = name;
    password = pass;
}

string User::getEmail() const { 
    return email; 
}

string User::getName() const { 
    return fullName; 
}

string User::getUserId() const {
    return userid;
}

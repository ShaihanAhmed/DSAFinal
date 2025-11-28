#ifndef AUTH_H
#define AUTH_H
#include "leaderboard.h"
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

class Auth {
private:
    string lastUsername;  // store last signed-up or logged-in username

    string filePath(string path, string filename, string ext);
    bool compare(const string a, const string b);
    bool ifExist(const string fp);
    bool isStrongPassword(const string pass);
    void enc(string &a);
    bool valiEm(const string a);
    bool passVali(const string a, const string b, const string path);

public:
    // bool signup();

    bool signupGUI(const string &fn, const string &email, const string &passInput);
    
    // string login();
    
    string login(const string &fn, const string &passInput);

    // getters for main.cpp
    string getLastSignedUpUsername();
    string getLastLoggedInUsername();
};

#endif

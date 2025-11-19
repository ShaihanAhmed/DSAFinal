#ifndef AUTH_H
#define AUTH_H

#include <iostream>
#include <cstring>
#include <fstream>
#include <ctime>
using namespace std;

class Auth
{
private:
    // string path = "./users/";
    // string ext = ".txt";

    string filePath(string a, string b, string c);
    bool compare(const string a, const string b);
    bool ifExist(string fp);
    bool isStrongPassword(const string b);
    void enc(string &a);
    bool valiEm(const string a);
    bool passVali(const string a, const string b , const string path);

public:
    // void signup();
    bool signup();
    // void login();
    bool login();
};

#endif

//--------------------------------- fallback point -------------------------------

// #ifndef AUTH_H
// #define AUTH_H

// #include <iostream>
// #include <fstream>
// #include <string>

// class Auth {
// private:
//     std::string filePath(const std::string &path, const std::string &fn, const std::string &ext);

// public:
//     bool signup(const std::string &user, const std::string &pass);
//     bool login(const std::string &user, const std::string &pass);

//     void enc(std::string &a);

//     bool signupCLI();
//     bool loginCLI();
// };

// #endif

#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <fstream>
#include <iostream>
using namespace std;

struct FriendNode {
    string name;
    FriendNode *next;
    FriendNode(string n) : name(n), next(nullptr) {}
};

struct RequestNode {
    string name;
    RequestNode *next;
    RequestNode(string n) : name(n), next(nullptr) {}
};

class Player
{
private:
    string username;
    string password;
    string email;

public:
    int total;
    int wins;
    int losses;
    int themeID;

    FriendNode *friendsHead;
    RequestNode *requestsHead;

    Player();
    void clearLists();

    // getters
    string getName() const { return username; }
    string getPass() const { return password; }
    string getEmail() const { return email; }
    int getWins() const { return wins; }
    int getLosses() const { return losses; }
    int getTotal() const { return total; }

    // setters
    void setCreds(const string &n, const string &p, const string &e);

    void loadFromFile(const string &filepath);
    void saveToFile(const string &filepath);

private:
    string* splitPipe(const string &s, int &outCount);
};

#endif

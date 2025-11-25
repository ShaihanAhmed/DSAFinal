// #ifndef PLAYERSYS_H
// #define PLAYERSYS_H

// #include "Player.h"
// #include <filesystem>
// using namespace std;

// class PlayerSys
// {
// public:
//     Player *players;
//     int count;
//     int capacity;

//     PlayerSys();
//     ~PlayerSys();

//     int addPlayer(const Player &p);
//     int findPlayer(const string &name);
//     void resize();
//     void loadAllPlayers();
//     void saveAllPlayers();

//     // ---------------- New getters ----------------
//     int getCount() const { return count; }
//     Player& getPlayer(int idx) { return players[idx]; }
// };

// #endif

// ---------------------------------------------------------------
// ---------------------------------------------------------------
// ---------------------------------------------------------------

#ifndef PLAYERSYS_H
#define PLAYERSYS_H

#include <string>
#include <filesystem>
#include "Player.h"
#include "HashingALGO.h"

using namespace std;

class PlayerSys {
public:
    Player *players;      
    int count;
    int capacity;

    HashingALGO hasher;   // <-- HASH TABLE HERE

    PlayerSys();
    ~PlayerSys();

    void resize();
    int addPlayer(const Player &p);
    int findPlayer(const string &name);

    void loadAllPlayers();
    void saveAllPlayers();
};

#endif

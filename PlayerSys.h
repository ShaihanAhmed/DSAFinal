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

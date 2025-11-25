// #include "PlayerSys.h"

// PlayerSys::PlayerSys() {
//     count = 0;
//     capacity = 10;
//     players = new Player[capacity];
// }

// PlayerSys::~PlayerSys() {
//     delete[] players;
// }

// void PlayerSys::resize() {
//     int newCap = capacity * 2;
//     Player *temp = new Player[newCap];

//     for (int i = 0; i < count; i++)
//         temp[i] = players[i];

//     delete[] players;
//     players = temp;
//     capacity = newCap;
// }

// int PlayerSys::addPlayer(const Player &p) {
//     if (count >= capacity)
//         resize();

//     players[count] = p;
//     return count++;
// }

// int PlayerSys::findPlayer(const string &name) {
//     for (int i = 0; i < count; i++)
//         if (players[i].getName() == name)
//             return i;

//     return -1;
// }

// void PlayerSys::loadAllPlayers() {
//     count = 0;

//     for (auto &entry : filesystem::directory_iterator("./users")) {
//         string file = entry.path().string();
//         if (file.find(".txt") == string::npos) continue;

//         Player p;
//         p.loadFromFile(file);
//         addPlayer(p);
//     }
// }

// void PlayerSys::saveAllPlayers() {
//     for (int i = 0; i < count; i++) {
//         string filepath = "./users/" + players[i].getName() + ".txt";
//         players[i].saveToFile(filepath);
//     }
// }


// ------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------

#include "PlayerSys.h"
#include <iostream>

PlayerSys::PlayerSys() {
    count = 0;
    capacity = 10;
    players = new Player[capacity];
}

PlayerSys::~PlayerSys() {
    delete[] players;
}

void PlayerSys::resize() {
    int newCap = capacity * 2;
    Player *temp = new Player[newCap];

    for (int i = 0; i < count; i++)
        temp[i] = players[i];

    delete[] players;
    players = temp;
    capacity = newCap;
}

int PlayerSys::addPlayer(const Player &p) {
    if (count >= capacity)
        resize();

    players[count] = p;

    // ⭐ LINK ARRAYS + HASH TABLE
    hasher.insert(p.getName(), count);

    return count++;
}

int PlayerSys::findPlayer(const string &name) {
    return hasher.search(name);  // O(1) lookup
}

void PlayerSys::loadAllPlayers() {
    count = 0;

    for (auto &entry : filesystem::directory_iterator("./users")) {
        string file = entry.path().string();
        if (file.find(".txt") == string::npos) continue;

        Player p;
        p.loadFromFile(file);

        addPlayer(p);   // ⭐ also inserts into hash table
    }
}

void PlayerSys::saveAllPlayers() {
    for (int i = 0; i < count; i++) {
        string path = "./users/" + players[i].getName() + ".txt";
        players[i].saveToFile(path);
    }
}



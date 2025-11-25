#ifndef HASHINGALGO_H
#define HASHINGALGO_H

#include <string>
using namespace std;

#define HASH_TABLE_SIZE 251

class hashNode {
public:
    string name;
    int index;
    bool used;

    hashNode() {
        used = false;
        index = -1;
    }
};

class HashingALGO
{
public:
    hashNode table[HASH_TABLE_SIZE];

    int calHash(const string &key) {
        long long h = 0;
        for (char c : key)
            h = (h * 31 + c) % HASH_TABLE_SIZE;
        return (int)h;
    }

    void insert(const string &username, int idx) {
        int pos = calHash(username);
        while (table[pos].used)
            pos = (pos + 1) % HASH_TABLE_SIZE;

        table[pos].used = true;
        table[pos].name = username;
        table[pos].index = idx;
    }

    int search(const string &username) {
        int pos = calHash(username);
        int start = pos;

        while (table[pos].used) {
            if (table[pos].name == username)
                return table[pos].index;

            pos = (pos + 1) % HASH_TABLE_SIZE;
            if (pos == start) break;
        }
        return -1;
    }
};

#endif

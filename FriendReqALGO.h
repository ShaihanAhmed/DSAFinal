#ifndef FRIENDREQALGO_H
#define FRIENDREQALGO_H

#include "PlayerSys.h"
#include "HashingALGO.h"
#include <iostream>

class FriendReqAlgo
{
public:
    PlayerSys *ps;
    HashingALGO *ht;

    FriendReqAlgo(PlayerSys *p, HashingALGO *h);

    void sendReq(const string &from, const string &to);
    void acceptReq(const string &user, const string &from);
    void rejectReq(const string &user, const string &from);
    void viewFriends(const string &user);
    void viewRequests(const string &user);

    string getFriendsStr(const string &user);
    string getRequestsStr(const string &user);
};

#endif

// #include "FriendReqALGO.h"

// FriendReqAlgo::FriendReqAlgo(PlayerSys *p, HashingALGO *h) {
//     ps = p;
//     ht = h;
// }

// void FriendReqAlgo::sendReq(const string &from, const string &to) {
//     int toIdx = ht->search(to);

//     if (toIdx == -1) {
//         cout << "User does not exist!\n";
//         return;
//     }

//     // Add request to receiver
//     RequestNode *node = new RequestNode(from);
//     node->next = ps->players[toIdx].requestsHead;
//     ps->players[toIdx].requestsHead = node;

//     // Save receiver file immediately
//     string filepath = "./users/" + ps->players[toIdx].getName() + ".txt";
//     ps->players[toIdx].saveToFile(filepath);

//     cout << "Request sent from " << from << " to " << to << "\n";
// }

// void FriendReqAlgo::acceptReq(const string &user, const string &from) {
//     int u = ht->search(user);
//     int f = ht->search(from);

//     if (u == -1 || f == -1) return;

//     // Remove from requests list (receiver side)
//     RequestNode *curr = ps->players[u].requestsHead;
//     RequestNode *prev = nullptr;
//     while (curr) {
//         if (curr->name == from) {
//             if (prev) prev->next = curr->next;
//             else ps->players[u].requestsHead = curr->next;
//             delete curr;
//             break;
//         }
//         prev = curr;
//         curr = curr->next;
//     }

//     // Add to friends (both sides)
//     FriendNode *a = new FriendNode(from);
//     a->next = ps->players[u].friendsHead;
//     ps->players[u].friendsHead = a;

//     FriendNode *b = new FriendNode(user);
//     b->next = ps->players[f].friendsHead;
//     ps->players[f].friendsHead = b;

//     // Save both players immediately
//     ps->players[u].saveToFile("./users/" + ps->players[u].getName() + ".txt");
//     ps->players[f].saveToFile("./users/" + ps->players[f].getName() + ".txt");

//     cout << user << " and " << from << " are now friends!\n";
// }

// void FriendReqAlgo::rejectReq(const string &user, const string &from) {
//     int u = ht->search(user);
//     if (u == -1) return;

//     RequestNode *curr = ps->players[u].requestsHead;
//     RequestNode *prev = nullptr;

//     while (curr) {
//         if (curr->name == from) {
//             if (prev) prev->next = curr->next;
//             else ps->players[u].requestsHead = curr->next;
//             delete curr;

//             // Save user file immediately
//             ps->players[u].saveToFile("./users/" + ps->players[u].getName() + ".txt");

//             cout << "Request rejected.\n";
//             return;
//         }
//         prev = curr;
//         curr = curr->next;
//     }
// }



// void FriendReqAlgo::viewFriends(const string &user) {
//     int idx = ht->search(user);

//     if (idx == -1) return;

//     cout << "\nFriends of " << user << ":\n";
//     FriendNode *f = ps->players[idx].friendsHead;

//     while (f) {
//         cout << "  - " << f->name << "\n";
//         f = f->next;
//     }
// }

// void FriendReqAlgo::viewRequests(const string &user) {
//     int idx = ht->search(user);
//     if (idx == -1) return;

//     cout << "\nPending requests for " << user << ":\n";
//     RequestNode *r = ps->players[idx].requestsHead;

//     while (r) {
//         cout << "  - " << r->name << "\n";
//         r = r->next;
//     }
// }


// -----------------------------------------------------------------
// -----------------------------------------------------------------
// ------------------------- GUI BASED IMP ---------------------------
#include "FriendReqALGO.h"

FriendReqAlgo::FriendReqAlgo(PlayerSys *p, HashingALGO *h) {
    ps = p;
    ht = h;
}

void FriendReqAlgo::sendReq(const string &from, const string &to) {
    int toIdx = ht->search(to);
    if (toIdx == -1){
        cout << "sendReq failed: target '" << to << "' not found!\n";
        return;
    };

    // Add request to receiver
    RequestNode *node = new RequestNode(from);
    node->next = ps->players[toIdx].requestsHead;
    ps->players[toIdx].requestsHead = node;

    // Save receiver file immediately
    string filepath = "./users/" + ps->players[toIdx].getName() + ".txt";
    ps->players[toIdx].saveToFile(filepath);
}

void FriendReqAlgo::acceptReq(const string &user, const string &from) {
    int u = ht->search(user);
    int f = ht->search(from);
    if (u == -1 || f == -1) return;

    // Remove from requests list (receiver side)
    RequestNode *curr = ps->players[u].requestsHead;
    RequestNode *prev = nullptr;
    while (curr) {
        if (curr->name == from) {
            if (prev) prev->next = curr->next;
            else ps->players[u].requestsHead = curr->next;
            delete curr;
            break;
        }
        prev = curr;
        curr = curr->next;
    }

    // Add to friends (both sides)
    FriendNode *a = new FriendNode(from);
    a->next = ps->players[u].friendsHead;
    ps->players[u].friendsHead = a;

    FriendNode *b = new FriendNode(user);
    b->next = ps->players[f].friendsHead;
    ps->players[f].friendsHead = b;

    // Save both players immediately
    ps->players[u].saveToFile("./users/" + ps->players[u].getName() + ".txt");
    ps->players[f].saveToFile("./users/" + ps->players[f].getName() + ".txt");
}

void FriendReqAlgo::rejectReq(const string &user, const string &from) {
    int u = ht->search(user);
    if (u == -1) return;

    RequestNode *curr = ps->players[u].requestsHead;
    RequestNode *prev = nullptr;
    while (curr) {
        if (curr->name == from) {
            if (prev) prev->next = curr->next;
            else ps->players[u].requestsHead = curr->next;
            delete curr;

            // Save user file immediately
            ps->players[u].saveToFile("./users/" + ps->players[u].getName() + ".txt");
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

void FriendReqAlgo::viewFriends(const string &user) {
    int idx = ht->search(user);
    if (idx == -1) return;

    // For GUI, you could fetch the string outside
    // Iterating just like before (logic intact)
    FriendNode *f = ps->players[idx].friendsHead;
    while (f) {
        f = f->next;
    }
}

void FriendReqAlgo::viewRequests(const string &user) {
    int idx = ht->search(user);
    if (idx == -1) return;

    RequestNode *r = ps->players[idx].requestsHead;
    while (r) {
        r = r->next;
    }
}

// --- Optional helpers for GUI display ---
string FriendReqAlgo::getFriendsStr(const string &user) {
    int idx = ht->search(user);
    if(idx==-1){
        return "User not found.";
    };
    string res;
    FriendNode *f = ps->players[idx].friendsHead;
    while(f){ res += f->name + "\n"; f=f->next; }
    return res.empty() ? "No friends yet." : res;
}

string FriendReqAlgo::getRequestsStr(const string &user) {
    int idx = ht->search(user);
    if(idx==-1){
        
        return "User not found.";
    } 
        
    string res;
    RequestNode *r = ps->players[idx].requestsHead;
    while(r){ res += r->name + "\n"; r=r->next; }
    return res.empty() ? "No pending requests." : res;
}

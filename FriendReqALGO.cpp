// -----------------------------------------------------------------
// -----------------------------------------------------------------
// ------------------------- GUI BASED IMP ---------------------------

#include "FriendReqALGO.h"

FriendReqAlgo::FriendReqAlgo(PlayerSys *p, HashingALGO *h) {
    ps = p;
    ht = h;
}

// void FriendReqAlgo::sendReq(const string &from, const string &to) {
//     int toIdx = ht->search(to);
//     if (toIdx == -1){
//         cout << "sendReq failed: target '" << to << "' not found!\n";
//         return;
//     };

//     // Add request to receiver
//     RequestNode *node = new RequestNode(from);
//     node->next = ps->players[toIdx].requestsHead;
//     ps->players[toIdx].requestsHead = node;

//     // Save receiver file immediately
//     string filepath = "./users/" + ps->players[toIdx].getName() + ".txt";
//     ps->players[toIdx].saveToFile(filepath);
// }

// ------------------------------ new send req with hadnling edge cases ---------------------------
// Returns message instead of void
string FriendReqAlgo::sendReq(const string &from, const string &to) {
    if (from == to)
        return "Cannot send request to yourself.";

    int toIdx = ht->search(to);
    int fromIdx = ht->search(from);
    if (toIdx == -1)
        return "User '" + to + "' does not exist.";
    if (fromIdx == -1)
        return "Your account not found.";

    // Check if already friends
    FriendNode* f = ps->players[fromIdx].friendsHead;
    while (f) {
        if (f->name == to)
            return "You are already friends with " + to + ".";
        f = f->next;
    }

    // Check if request already sent
    RequestNode* r = ps->players[toIdx].requestsHead;
    while (r) {
        if (r->name == from)
            return "Friend request already sent to " + to + ".";
        r = r->next;
    }

    // Add request
    RequestNode* newReq = new RequestNode(from);
    newReq->next = ps->players[toIdx].requestsHead;
    ps->players[toIdx].requestsHead = newReq;

    ps->players[toIdx].saveToFile("./users/" + ps->players[toIdx].getName() + ".txt");
    return "Friend request sent to " + to + ".";
}


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
// }

// ------------------------------------------------------------------------ hadnling edg cases
void FriendReqAlgo::acceptReq(const string &user, const string &from) {
    int u = ht->search(user);
    int f = ht->search(from);
    if (u == -1 || f == -1) return;

    // Check if already friends
    FriendNode *check = ps->players[u].friendsHead;
    while (check) {
        if (check->name == from) {
            // Already friends, just remove request
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
            return;
        }
        check = check->next;
    }

    // Remove request from receiver side
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

#include "Player.h"

Player::Player() {
    friendsHead = nullptr;
    requestsHead = nullptr;
    total = wins = losses = 0;
    themeID = 0;
}

void Player::clearLists() {
    FriendNode *f = friendsHead;
    while (f) {
        FriendNode *t = f;
        f = f->next;
        delete t;
    }
    friendsHead = nullptr;

    RequestNode *r = requestsHead;
    while (r) {
        RequestNode *t = r;
        r = r->next;
        delete t;
    }
    requestsHead = nullptr;
}

void Player::setCreds(const string &n, const string &p, const string &e) {
    username = n;
    password = p;
    email = e;
}

string* Player::splitPipe(const string &s, int &outCount) {
    if (s.empty()) {
        outCount = 0;
        return nullptr;
    }

    // Count pipes
    outCount = 1;
    for (char c : s)
        if (c == '|') outCount++;

    string *arr = new string[outCount];
    string temp = "";
    int idx = 0;

    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '|') {
            arr[idx++] = temp;
            temp = "";
        } else {
            temp += s[i];
        }
    }
    arr[idx] = temp; // last element
    return arr;
}


void Player::loadFromFile(const string &filepath) {
    clearLists();  // reset friends/requests
    ifstream fin(filepath);
    if (!fin) {
        cout << "WARNING: Cannot read file: " << filepath << ". Using default values.\n";
        username = "";
        password = "";
        email = "";
        total = wins = losses = 0;
        themeID = 1;
        friendsHead = nullptr;
        requestsHead = nullptr;
        return;
    }

    string line;

    // --------- Line 1: Credentials ---------
    if (getline(fin, line)) {
        int c1 = line.find(',');
        int c2 = line.find(',', c1 + 1);

        if (c1 != string::npos && c2 != string::npos) {
            string n = line.substr(0, c1);
            string p = line.substr(c1 + 1, c2 - c1 - 1);
            string e = line.substr(c2 + 1);
            setCreds(n, p, e);
        } else {
            setCreds("", "", "");
        }
    } else {
        setCreds("", "", "");
    }

    // --------- Line 2: Stats ---------
    total = wins = losses = 0;
    if (getline(fin, line) && !line.empty()) {
        size_t a = line.find(',');
        size_t b = line.find(',', a + 1);
        if (a != string::npos && b != string::npos) {
            try {
                total = stoi(line.substr(0, a));
                wins  = stoi(line.substr(a + 1, b - a - 1));
                losses = stoi(line.substr(b + 1));
            } catch (...) {
                total = wins = losses = 0;  // fallback
            }
        }
    }

    // --------- Line 3: Friends ---------
    friendsHead = nullptr;
    if (getline(fin, line) && !line.empty()) {
        int fCount = 0;
        string *fr = splitPipe(line, fCount);
        for (int i = 0; i < fCount; i++) {
            if (!fr[i].empty()) {
                FriendNode *node = new FriendNode(fr[i]);
                node->next = friendsHead;
                friendsHead = node;
            }
        }
        delete[] fr;
    }

    // --------- Line 4: Requests ---------
    requestsHead = nullptr;
    if (getline(fin, line) && !line.empty()) {
        int rCount = 0;
        string *rq = splitPipe(line, rCount);
        for (int i = 0; i < rCount; i++) {
            if (!rq[i].empty()) {
                RequestNode *node = new RequestNode(rq[i]);
                node->next = requestsHead;
                requestsHead = node;
            }
        }
        delete[] rq;
    }

    // --------- Line 5: Theme ---------
    themeID = 1;
    if (getline(fin, line) && !line.empty()) {
        try {
            themeID = stoi(line);
        } catch (...) {
            themeID = 1;  // fallback
        }
    }

    fin.close();
}

//it rewrites file again 
void Player::saveToFile(const string &filepath) {
    ofstream fout(filepath);
    if (!fout) {
        cout << "ERROR: Cannot write file: " << filepath << endl;
        return;
    }

    // --------- Line 1: Credentials ---------
    fout << username << "," << password << "," << email << "\n";

    // --------- Line 2: Stats ---------
    fout << total << "," << wins << "," << losses << "\n";

    // --------- Line 3: Friends ---------
    for (FriendNode *f = friendsHead; f; f = f->next)
        fout << f->name << "|";
    fout << "\n";

    // --------- Line 4: Requests ---------
    for (RequestNode *r = requestsHead; r; r = r->next)
        fout << r->name << "|";
    fout << "\n";

    // --------- Line 5: Theme ---------
    fout << themeID << "\n";

    fout.close();
}


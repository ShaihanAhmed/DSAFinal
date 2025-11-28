#ifndef LEADERBOARD_H
#define LEADERBOARD_H
#include <iostream>
#include <fstream>
#include <string>
#include <limits>

using namespace std;

const int MAX_USERS = 10;

class User {
public:
    int score{};
    string user;
};

class LeaderBoard {
public:
    User topUser[MAX_USERS];
    int heapSize = 0;

    LeaderBoard(int newScore, const string &newUser) {
        readFromFile();

        // If there's room, append and rebuild heap
        if (heapSize < MAX_USERS) {
            topUser[heapSize].score = newScore;
            topUser[heapSize].user = newUser;
            heapSize++;
            buildMinHeap();
            cout << "------------CONGRATULATIONS! YOU MADE IT IN THE LEADERBOARD! -----------------\n";
        } else {
            // Full: replace root if newScore is better than smallest (root)
            if (newScore > topUser[0].score) {
                cout << "--------CONGRATULATIONS! YOU MADE IT TO THE TOP 10 LEADERBOARD!-------------\n";
                topUser[0].score = newScore;
                topUser[0].user = newUser;
                heapifyMin(0); // restore heap property
            }
        }

        printAndWriteToFile();
        display();
    }

private:
    void readFromFile() {
        ifstream in("leaderboard.txt");
        heapSize = 0;
        string line;
        while (heapSize < MAX_USERS && getline(in, line)) {
            if (line.empty()) continue;
            // find first whitespace separating score and name
            size_t pos = line.find_first_of(" \t");
            if (pos == string::npos) continue; // invalid line, skip
            // get score substring and name substring (trim leading spaces for name)
            string scoreStr = line.substr(0, pos);
            size_t nameStart = line.find_first_not_of(" \t", pos);
            if (nameStart == string::npos) nameStart = pos + 1;
            string name = line.substr(nameStart);
            try {
                topUser[heapSize].score = stoi(scoreStr);
            }
            catch (...) {
                continue; // skip malformed lines
            }
            topUser[heapSize].user = name;
            heapSize++;
        }
        in.close();

        // build heap for current entries (so topUser[0] is the smallest)
        if (heapSize > 0) buildMinHeap();
    }

    void printAndWriteToFile() {
        ofstream out("leaderboard.txt");
        for (int i = 0; i < heapSize; ++i) {
            out << topUser[i].score << " " << topUser[i].user << '\n';
        }
        out.close();
    }

    // heap helpers (use heapSize consistently)
    void buildMinHeap() {
        for (int i = heapSize / 2 - 1; i >= 0; --i)
            heapifyMin(i);
    }

    void heapifyMin(int i) {
        int smallest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < heapSize && topUser[left].score < topUser[smallest].score)
            smallest = left;
        if (right < heapSize && topUser[right].score < topUser[smallest].score)
            smallest = right;

        if (smallest != i) {
            swap(topUser[i], topUser[smallest]);
            heapifyMin(smallest);
        }
    }
    void display()
{
    // Copy current leaderboard
    User temp[MAX_USERS];
    for (int i = 0; i < heapSize; i++)
        temp[i] = topUser[i];

    // Sort in descending order (highest score first)
    for (int i = 0; i < heapSize - 1; i++) {
        for (int j = i + 1; j < heapSize; j++) {
            if (temp[j].score > temp[i].score) {
                swap(temp[i], temp[j]);
            }
        }
    }

    // Print leaderboard
    cout << "\n========== LEADERBOARD (TOP " << heapSize << ") ==========\n";
    for (int i = 0; i < heapSize; i++) {
        cout << i + 1 << ". " << temp[i].user << " - " << temp[i].score << "\n";
    }
    cout << "=====================================================\n";
}
};
#endif


// //-----------------------------------------------------------------------

// // #include <iostream>
// // #include "Auth.h"
// // #include <SFML/Graphics.hpp>
// // #include <time.h>
// // using namespace sf;
// // using namespace std;

// // const int M = 25;
// // const int N = 40;
// // int grid[M][N] = {0};
// // int ts = 18; // tile size

// // struct Enemy {
// //     int x, y, dx, dy;
// //     Enemy() {
// //         x = y = 300;
// //         dx = 4 - rand() % 8;
// //         dy = 4 - rand() % 8;
// //     }
// //     void move() {
// //         x += dx;
// //         if (grid[y/ts][x/ts] == 1) { dx = -dx; x += dx; }

// //         y += dy;
// //         if (grid[y/ts][x/ts] == 1) { dy = -dy; y += dy; }
// //     }
// // };

// // void drop(int y, int x)
// // {
// //     if (grid[y][x] == 0) grid[y][x] = -1;
// //     if (grid[y-1][x] == 0) drop(y-1, x);
// //     if (grid[y+1][x] == 0) drop(y+1, x);
// //     if (grid[y][x-1] == 0) drop(y, x-1);
// //     if (grid[y][x+1] == 0) drop(y, x+1);
// // }

// // void startGame()
// // {
// //     srand(time(0));

// //     RenderWindow window(VideoMode(N * ts, M * ts), "Xonix Game!");
// //     window.setFramerateLimit(60);

// //     Texture t1, t2, t3;
// //     t1.loadFromFile("images/tiles.png");
// //     t2.loadFromFile("images/gameover.png");
// //     t3.loadFromFile("images/enemy.png");

// //     Sprite sTile(t1), sGameover(t2), sEnemy(t3);
// //     sGameover.setPosition(100, 100);
// //     sEnemy.setOrigin(20, 20);

// //     int enemyCount = 4;
// //     Enemy a[10];

// //     bool Game = true;
// //     int x = 0, y = 0, dx = 0, dy = 0;
// //     float timer = 0, delay = 0.07;
// //     Clock clock;

// //     for (int i = 0; i < M; i++)
// //         for (int j = 0; j < N; j++)
// //             if (i == 0 || j == 0 || i == M - 1 || j == N - 1)
// //                 grid[i][j] = 1;

// //     while (window.isOpen())
// //     {
// //         float time = clock.getElapsedTime().asSeconds();
// //         clock.restart();
// //         timer += time;

// //         Event e;
// //         while (window.pollEvent(e))
// //         {
// //             if (e.type == Event::Closed)
// //                 window.close();

// //             if (e.type == Event::KeyPressed)
// //                 if (e.key.code == Keyboard::Escape)
// //                 {
// //                     for (int i = 1; i < M - 1; i++)
// //                         for (int j = 1; j < N - 1; j++)
// //                             grid[i][j] = 0;

// //                     x = 10;
// //                     y = 0;
// //                     Game = true;
// //                 }
// //         }

// //         if (Keyboard::isKeyPressed(Keyboard::Left)) { dx = -1; dy = 0; }
// //         if (Keyboard::isKeyPressed(Keyboard::Right)) { dx = 1; dy = 0; }
// //         if (Keyboard::isKeyPressed(Keyboard::Up)) { dx = 0; dy = -1; }
// //         if (Keyboard::isKeyPressed(Keyboard::Down)) { dx = 0; dy = 1; }

// //         if (!Game) continue;

// //         if (timer > delay)
// //         {
// //             x += dx;
// //             y += dy;

// //             if (x < 0) x = 0;
// //             if (x > N - 1) x = N - 1;
// //             if (y < 0) y = 0;
// //             if (y > M - 1) y = M - 1;

// //             if (grid[y][x] == 2) Game = false;
// //             if (grid[y][x] == 0) grid[y][x] = 2;

// //             timer = 0;
// //         }

// //         for (int i = 0; i < enemyCount; i++) a[i].move();

// //         if (grid[y][x] == 1)
// //         {
// //             dx = dy = 0;

// //             for (int i = 0; i < enemyCount; i++)
// //                 drop(a[i].y / ts, a[i].x / ts);

// //             for (int i = 0; i < M; i++)
// //                 for (int j = 0; j < N; j++)
// //                     if (grid[i][j] == -1) grid[i][j] = 0;
// //                     else grid[i][j] = 1;
// //         }

// //         for (int i = 0; i < enemyCount; i++)
// //             if (grid[a[i].y/ts][a[i].x/ts] == 2)
// //                 Game = false;

// //         window.clear();

// //         for (int i = 0; i < M; i++)
// //             for (int j = 0; j < N; j++)
// //             {
// //                 if (grid[i][j] == 0) continue;

// //                 if (grid[i][j] == 1) sTile.setTextureRect(IntRect(0, 0, ts, ts));
// //                 if (grid[i][j] == 2) sTile.setTextureRect(IntRect(54, 0, ts, ts));

// //                 sTile.setPosition(j * ts, i * ts);
// //                 window.draw(sTile);
// //             }

// //         sTile.setTextureRect(IntRect(36, 0, ts, ts));
// //         sTile.setPosition(x * ts, y * ts);
// //         window.draw(sTile);

// //         sEnemy.rotate(10);
// //         for (int i = 0; i < enemyCount; i++)
// //         {
// //             sEnemy.setPosition(a[i].x, a[i].y);
// //             window.draw(sEnemy);
// //         }

// //         if (!Game) window.draw(sGameover);

// //         window.display();
// //     }
// // }


// // int main() {
// //     Auth obj;
// //     bool authenticated = false;

// //     while (!authenticated) {
// //         int choice;
// //         cout << "\033[36m\n----- XONIX GAME LOGIN -----\033[0m\n"; // cyan
// //         cout << "\033[32m1. Sign Up\033[0m\n";                     // green
// //         cout << "\033[34m2. Login\033[0m\n";                       // blue
// //         cout << "\033[31m3. Quit\033[0m\n";                        // red
// //         cout << "\033[37mEnter choice: \033[0m";                   // white
// //         cin >> choice;

// //         if (choice == 1) {
// //             authenticated = obj.signup();
// //         }
// //         else if (choice == 2) {
// //             authenticated = obj.login();
// //         }
// //         else if (choice == 3) {
// //             cout << "\033[31mExiting...\033[0m\n";
// //             return 0;
// //         }
// //         else {
// //             cout << "\033[31mInvalid choice! Try again.\033[0m\n";
// //         }
// //     }

// //     cout << "\033[32m\nAuthentication successful! Starting game...\033[0m\n";

// //     startGame();

// //     return 0;
// // }

// // ---------------------------------------------------------------
// // ---------------------------------------------------------------
// // ---------------------------------------------------------------
// // ---------------------------------------------------------------
// // ---------------------------------------------------------------


// #include <iostream>
// #include "Auth.h"
// #include <SFML/Graphics.hpp>
// #include <time.h>
// #include "Player.h"
// #include "PlayerSys.h"
// #include "FriendReqALGO.h"
// using namespace sf;
// using namespace std;

// const int M = 25;
// const int N = 40;
// int grid[M][N] = {0};
// int ts = 18; // tile size

// struct Enemy {
//     int x, y, dx, dy;
//     Enemy() {
//         x = y = 300;
//         dx = 4 - rand() % 8;
//         dy = 4 - rand() % 8;
//     }
//     void move() {
//         x += dx;
//         if (grid[y/ts][x/ts] == 1) { dx = -dx; x += dx; }

//         y += dy;
//         if (grid[y/ts][x/ts] == 1) { dy = -dy; y += dy; }
//     }
// };

// void drop(int y, int x)
// {
//     if (grid[y][x] == 0) grid[y][x] = -1;
//     if (grid[y-1][x] == 0) drop(y-1, x);
//     if (grid[y+1][x] == 0) drop(y+1, x);
//     if (grid[y][x-1] == 0) drop(y, x-1);
//     if (grid[y][x+1] == 0) drop(y, x+1);
// }

// void startGame()
// {
//     srand(time(0));

//     RenderWindow window(VideoMode(N * ts, M * ts), "Xonix Game!");
//     window.setFramerateLimit(60);

//     Texture t1, t2, t3;
//     t1.loadFromFile("images/tiles.png");
//     t2.loadFromFile("images/gameover.png");
//     t3.loadFromFile("images/enemy.png");

//     Sprite sTile(t1), sGameover(t2), sEnemy(t3);
//     sGameover.setPosition(100, 100);
//     sEnemy.setOrigin(20, 20);

//     int enemyCount = 4;
//     Enemy a[10];

//     bool Game = true;
//     int x = 0, y = 0, dx = 0, dy = 0;
//     float timer = 0, delay = 0.07;
//     Clock clock;

//     for (int i = 0; i < M; i++)
//         for (int j = 0; j < N; j++)
//             if (i == 0 || j == 0 || i == M - 1 || j == N - 1)
//                 grid[i][j] = 1;

//     while (window.isOpen())
//     {
//         float time = clock.getElapsedTime().asSeconds();
//         clock.restart();
//         timer += time;

//         Event e;
//         while (window.pollEvent(e))
//         {
//             if (e.type == Event::Closed)
//                 window.close();

//             if (e.type == Event::KeyPressed)
//                 if (e.key.code == Keyboard::Escape)
//                 {
//                     for (int i = 1; i < M - 1; i++)
//                         for (int j = 1; j < N - 1; j++)
//                             grid[i][j] = 0;

//                     x = 10;
//                     y = 0;
//                     Game = true;
//                 }
//         }

//         if (Keyboard::isKeyPressed(Keyboard::Left)) { dx = -1; dy = 0; }
//         if (Keyboard::isKeyPressed(Keyboard::Right)) { dx = 1; dy = 0; }
//         if (Keyboard::isKeyPressed(Keyboard::Up)) { dx = 0; dy = -1; }
//         if (Keyboard::isKeyPressed(Keyboard::Down)) { dx = 0; dy = 1; }

//         if (!Game) continue;

//         if (timer > delay)
//         {
//             x += dx;
//             y += dy;

//             if (x < 0) x = 0;
//             if (x > N - 1) x = N - 1;
//             if (y < 0) y = 0;
//             if (y > M - 1) y = M - 1;

//             if (grid[y][x] == 2) Game = false;
//             if (grid[y][x] == 0) grid[y][x] = 2;

//             timer = 0;
//         }

//         for (int i = 0; i < enemyCount; i++) a[i].move();

//         if (grid[y][x] == 1)
//         {
//             dx = dy = 0;

//             for (int i = 0; i < enemyCount; i++)
//                 drop(a[i].y / ts, a[i].x / ts);

//             for (int i = 0; i < M; i++)
//                 for (int j = 0; j < N; j++)
//                     if (grid[i][j] == -1) grid[i][j] = 0;
//                     else grid[i][j] = 1;
//         }

//         for (int i = 0; i < enemyCount; i++)
//             if (grid[a[i].y/ts][a[i].x/ts] == 2)
//                 Game = false;

//         window.clear();

//         for (int i = 0; i < M; i++)
//             for (int j = 0; j < N; j++)
//             {
//                 if (grid[i][j] == 0) continue;

//                 if (grid[i][j] == 1) sTile.setTextureRect(IntRect(0, 0, ts, ts));
//                 if (grid[i][j] == 2) sTile.setTextureRect(IntRect(54, 0, ts, ts));

//                 sTile.setPosition(j * ts, i * ts);
//                 window.draw(sTile);
//             }

//         sTile.setTextureRect(IntRect(36, 0, ts, ts));
//         sTile.setPosition(x * ts, y * ts);
//         window.draw(sTile);

//         sEnemy.rotate(10);
//         for (int i = 0; i < enemyCount; i++)
//         {
//             sEnemy.setPosition(a[i].x, a[i].y);
//             window.draw(sEnemy);
//         }

//         if (!Game) window.draw(sGameover);

//         window.display();
//     }
// }


// // ... your other includes and startGame() ...

// // int main() {
// //     Auth obj;
// //     Player currentPlayer;   // create player object
// //     bool authenticated = false;
    
// //     string currentUsername = "";

// // while (currentUsername.empty()) {
// //     int choice;
// //     cout << "\033[36m\n----- XONIX GAME LOGIN -----\033[0m\n";
// //     cout << "\033[32m1. Sign Up\033[0m\n";
// //     cout << "\033[34m2. Login\033[0m\n";
// //     cout << "\033[31m3. Quit\033[0m\n";
// //     cout << "\033[37mEnter choice: \033[0m";
// //     cin >> choice;
// //     cin.ignore();

// //     if (choice == 1) {
// //         bool signupSuccess = obj.signup();
// //         if (signupSuccess) {
// //             currentUsername = obj.getLastSignedUpUsername(); // implement this in Auth
// //         }
// //     }
// //     else if (choice == 2) {
// //         currentUsername = obj.login(); // now login returns username
// //     }
// //     else if (choice == 3) {
// //         cout << "\033[31mExiting...\033[0m\n";
// //         return 0;
// //     }
// //     else {
// //         cout << "\033[31mInvalid choice! Try again.\033[0m\n";
// //     }
// // }


// //     // ------------------- LOAD PLAYER DATA -------------------
// //     string filepath = "./users/" + currentUsername + ".txt";
// //     currentPlayer.loadFromFile(filepath);

// //     // ------------------- DEBUG: PRINT FRIENDS -------------------
// //     cout << "\n--- FRIENDS ---\n";
// //     FriendNode* f = currentPlayer.friendsHead;
// //     if (!f) cout << "No friends yet.\n";
// //     while (f) {
// //         cout << f->name << "\n";
// //         f = f->next;
// //     }

// //     // ------------------- DEBUG: PRINT REQUESTS -------------------
// //     cout << "\n--- REQUESTS ---\n";
// //     RequestNode* r = currentPlayer.requestsHead;
// //     if (!r) cout << "No friend requests yet.\n";
// //     while (r) {
// //         cout << r->name << "\n";
// //         r = r->next;
// //     }

// //     cout << "\033[32m\nStarting game...\033[0m\n";
// //     startGame();

// //     return 0;
// // }

// // --------------------------------------------------------------------
// // --------------------------------------------------------------------
// // ---------------------------- imp loding data into arr -----------------------
// // --------------------------------------------------------------------
// // ---------------------------------------------------------------------

// void displayPlayer(const Player &p) {
//     cout << "Username: " << p.getName() << endl;
//     cout << "Email   : " << p.getEmail() << endl;
//     cout << "Password: " << p.getPass() << endl;
//     cout << "Total   : " << p.total 
//          << " Wins=" << p.wins 
//          << " Losses=" << p.losses << endl;
//     cout << "ThemeID : " << p.themeID << endl;

//     cout << "Friends : ";
//     for (FriendNode *f = p.friendsHead; f; f = f->next)
//         cout << f->name << " ";
//     cout << endl;

//     cout << "Requests: ";
//     for (RequestNode *r = p.requestsHead; r; r = r->next)
//         cout << r->name << " ";
//     cout << endl;
//     cout << "----------------------\n";
// }

// // int main() {
// //     Auth auth;
// //     PlayerSys sys;
// //     Player currentPlayer;

// //     // ---------------- Load all users at startup ----------------
// //     sys.loadAllPlayers();
// //     cout << "\nLoaded " << sys.count << " user(s) from ./users folder.\n";

// //     // ---------------- Debug: Display all loaded users ----------------
// //     cout << "\n--- Loaded users (DEBUG) ---\n";
// //     for (int i = 0; i < sys.count; i++)
// //         displayPlayer(sys.players[i]);

// //     // ---------------- ALSO DEBUG HASH TABLE LOOKUP ----------------
// //     cout << "\n--- Hash Search Test (DEBUG) ---\n";
// //     cout << "Search username: ";
// //     string testname;
// //     cin >> testname;

// //     int testIndex = sys.findPlayer(testname);
// //     if (testIndex == -1)
// //         cout << "User NOT FOUND in hash table.\n";
// //     else {
// //         cout << "Found at index " << testIndex << " in players[].\n";
// //         displayPlayer(sys.players[testIndex]);
// //     }

// //     cin.ignore(); // clean leftover newline

// //     // ---------------- Login / Signup Logic ----------------
// //     string currentUsername = "";

// //     while (currentUsername.empty()) {
// //         int choice;
// //         cout << "\033[36m\n----- XONIX GAME LOGIN -----\033[0m\n";
// //         cout << "\033[32m1. Sign Up\033[0m\n";
// //         cout << "\033[34m2. Login\033[0m\n";
// //         cout << "\033[31m3. Quit\033[0m\n";
// //         cout << "Enter choice: ";
// //         cin >> choice;
// //         cin.ignore();

// //         if (choice == 1) {
// //             bool ok = auth.signup();
// //             if (ok) {
// //                 currentUsername = auth.getLastSignedUpUsername();

// //                 // Load NEW user from file
// //                 Player newP;
// //                 newP.loadFromFile("./users/" + currentUsername + ".txt");

// //                 // Add to the array AND hash table
// //                 sys.addPlayer(newP);

// //                 cout << "\n\033[32m(New user saved + added to array)\033[0m\n";
// //             }
// //         }
// //         else if (choice == 2) {
// //             currentUsername = auth.login();
// //             if (currentUsername.empty())
// //                 cout << "\033[31mLogin failed. Try again.\033[0m\n";
// //         }
// //         else if (choice == 3) {
// //             cout << "Goodbye!\n";
// //             return 0;
// //         }
// //         else {
// //             cout << "Invalid option! Try again.\n";
// //         }
// //     }

// //     // ---------------- Load logged-in player ----------------
// //     currentPlayer.loadFromFile("./users/" + currentUsername + ".txt");

// //     cout << "\n\033[33m--- Current Player Data (DEBUG) ---\033[0m\n";
// //     displayPlayer(currentPlayer);

// //     // ---------------- START THE GAME ----------------
// //     cout << "\033[32m\nStarting game...\033[0m\n";
// //     startGame();     // your actual game function

// //     return 0;
// // }

// // --------------------------------------------------------------------------------
// // int main() {
// //     Auth auth;
// //     PlayerSys sys;
// //     Player currentPlayer;

// //     // ---------------- Load all users at startup ----------------
// //     sys.loadAllPlayers();
// //     cout << "\nLoaded " << sys.count << " user(s) from ./users folder.\n";

// //     // ---------------- Debug: Display all loaded users ----------------
// //     cout << "\n--- Loaded users (DEBUG) ---\n";
// //     for (int i = 0; i < sys.count; i++)
// //         displayPlayer(sys.players[i]);

// //     // ---------------- Login / Signup Logic ----------------
// //     string currentUsername = "";
// //     while (currentUsername.empty()) {
// //         int choice;
// //         cout << "\033[36m\n----- XONIX GAME LOGIN -----\033[0m\n";
// //         cout << "\033[32m1. Sign Up\033[0m\n";
// //         cout << "\033[34m2. Login\033[0m\n";
// //         cout << "\033[31m3. Quit\033[0m\n";
// //         cout << "Enter choice: ";
// //         cin >> choice;
// //         cin.ignore();

// //         if (choice == 1) {
// //             bool ok = auth.signup();
// //             if (ok) {
// //                 currentUsername = auth.getLastSignedUpUsername();

// //                 // Load NEW user from file
// //                 Player newP;
// //                 newP.loadFromFile("./users/" + currentUsername + ".txt");

// //                 // Add to the array
// //                 sys.addPlayer(newP);

// //                 cout << "\n\033[32m(New user saved + added to array)\033[0m\n";
// //             }
// //         }
// //         else if (choice == 2) {
// //             currentUsername = auth.login();
// //             if (currentUsername.empty())
// //                 cout << "\033[31mLogin failed. Try again.\033[0m\n";
// //         }
// //         else if (choice == 3) {
// //             cout << "Goodbye!\n";
// //             return 0;
// //         }
// //         else {
// //             cout << "Invalid option! Try again.\n";
// //         }
// //     }

// //     // ---------------- Load logged-in player ----------------
// //     currentPlayer.loadFromFile("./users/" + currentUsername + ".txt");

// //     cout << "\n\033[33m--- Current Player Data (DEBUG) ---\033[0m\n";
// //     displayPlayer(currentPlayer);

// //     // ---------------- Initialize FriendReqAlgo ----------------
// //     HashingALGO ht;
// //     for (int i = 0; i < sys.count; i++)
// //         ht.insert(sys.players[i].getName(), i);
// //     FriendReqAlgo freqs(&sys, &ht);

// //     // ---------------- Post-login Menu ----------------
// //     int menuChoice = 0;
// //     do {
// //         cout << "\n\033[36m----- FRIEND MENU -----\033[0m\n";
// //         cout << "1. View Friends\n";
// //         cout << "2. View Pending Requests\n";
// //         cout << "3. Send Friend Request\n";
// //         cout << "4. Accept Friend Request\n";
// //         cout << "5. Reject Friend Request\n";
// //         cout << "6. Start Game\n";
// //         cout << "7. Logout / Quit\n";
// //         cout << "Enter choice: ";
// //         cin >> menuChoice;
// //         cin.ignore();

// //         switch (menuChoice) {
// //             case 1:
// //                 freqs.viewFriends(currentUsername);
// //                 break;

// //             case 2:
// //                 freqs.viewRequests(currentUsername);
// //                 break;

// //             case 3: {
// //                 string toUser;
// //                 cout << "Enter username to send request to: ";
// //                 getline(cin, toUser);
// //                 freqs.sendReq(currentUsername, toUser);

// //                 // Save the updated request immediately
// //                 int idx = sys.findPlayer(toUser);
// //                 if (idx != -1)
// //                     sys.players[idx].saveToFile("./users/" + sys.players[idx].getName() + ".txt");
// //                 break;
// //             }

// //             case 4: {
// //                 string fromUser;
// //                 cout << "Enter username of request to accept: ";
// //                 getline(cin, fromUser);
// //                 freqs.acceptReq(currentUsername, fromUser);

// //                 // Save both users immediately
// //                 int uIdx = sys.findPlayer(currentUsername);
// //                 int fIdx = sys.findPlayer(fromUser);
// //                 if (uIdx != -1)
// //                     sys.players[uIdx].saveToFile("./users/" + sys.players[uIdx].getName() + ".txt");
// //                 if (fIdx != -1)
// //                     sys.players[fIdx].saveToFile("./users/" + sys.players[fIdx].getName() + ".txt");
// //                 break;
// //             }

// //             case 5: {
// //                 string fromUser;
// //                 cout << "Enter username of request to reject: ";
// //                 getline(cin, fromUser);
// //                 freqs.rejectReq(currentUsername, fromUser);

// //                 // Save current player immediately
// //                 int uIdx = sys.findPlayer(currentUsername);
// //                 if (uIdx != -1)
// //                     sys.players[uIdx].saveToFile("./users/" + sys.players[uIdx].getName() + ".txt");
// //                 break;
// //             }

// //             case 6:
// //                 cout << "\033[32m\nStarting game...\033[0m\n";
// //                 startGame();
// //                 break;

// //             case 7:
// //                 cout << "Logging out...\n";
// //                 break;

// //             default:
// //                 cout << "Invalid choice! Try again.\n";
// //         }

// //     } while (menuChoice != 7);

// //     return 0;
// // }

// // gui imp --------------------------------
// // gui imp --------------------------------
// // gui imp --------------------------------
// // gui imp --------------------------------
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Auth.h"
#include "PlayerSys.h"
#include "FriendReqALGO.h"

using namespace sf;
using namespace std;


const int M = 25;
const int N = 40;
int grid[M][N] = {0};
int ts = 18; // tile size

struct Enemy {
    int x, y, dx, dy;
    Enemy() {
        x = y = 300;
        dx = 4 - rand() % 8;
        dy = 4 - rand() % 8;
    }
    void move() {
        x += dx;
        if (grid[y/ts][x/ts] == 1) { dx = -dx; x += dx; }

        y += dy;
        if (grid[y/ts][x/ts] == 1) { dy = -dy; y += dy; }
    }
};

void drop(int y, int x)
{
    if (grid[y][x] == 0) grid[y][x] = -1;
    if (grid[y-1][x] == 0) drop(y-1, x);
    if (grid[y+1][x] == 0) drop(y+1, x);
    if (grid[y][x-1] == 0) drop(y, x-1);
    if (grid[y][x+1] == 0) drop(y, x+1);
}

void startGame()
{
    srand(time(0));

    RenderWindow window(VideoMode(N * ts, M * ts), "Xonix Game!");
    window.setFramerateLimit(60);

    Texture t1, t2, t3;
    t1.loadFromFile("images/tiles.png");
    t2.loadFromFile("images/gameover.png");
    t3.loadFromFile("images/enemy.png");

    Sprite sTile(t1), sGameover(t2), sEnemy(t3);
    sGameover.setPosition(100, 100);
    sEnemy.setOrigin(20, 20);

    int enemyCount = 4;
    Enemy a[10];

    bool Game = true;
    int x = 0, y = 0, dx = 0, dy = 0;
    float timer = 0, delay = 0.07;
    Clock clock;

    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            if (i == 0 || j == 0 || i == M - 1 || j == N - 1)
                grid[i][j] = 1;

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();

            if (e.type == Event::KeyPressed)
                if (e.key.code == Keyboard::Escape)
                {
                    for (int i = 1; i < M - 1; i++)
                        for (int j = 1; j < N - 1; j++)
                            grid[i][j] = 0;

                    x = 10;
                    y = 0;
                    Game = true;
                }
        }

        if (Keyboard::isKeyPressed(Keyboard::Left)) { dx = -1; dy = 0; }
        if (Keyboard::isKeyPressed(Keyboard::Right)) { dx = 1; dy = 0; }
        if (Keyboard::isKeyPressed(Keyboard::Up)) { dx = 0; dy = -1; }
        if (Keyboard::isKeyPressed(Keyboard::Down)) { dx = 0; dy = 1; }

        if (!Game) continue;

        if (timer > delay)
        {
            x += dx;
            y += dy;

            if (x < 0) x = 0;
            if (x > N - 1) x = N - 1;
            if (y < 0) y = 0;
            if (y > M - 1) y = M - 1;

            if (grid[y][x] == 2) Game = false;
            if (grid[y][x] == 0) grid[y][x] = 2;

            timer = 0;
        }

        for (int i = 0; i < enemyCount; i++) a[i].move();

        if (grid[y][x] == 1)
        {
            dx = dy = 0;

            for (int i = 0; i < enemyCount; i++)
                drop(a[i].y / ts, a[i].x / ts);

            for (int i = 0; i < M; i++)
                for (int j = 0; j < N; j++)
                    if (grid[i][j] == -1) grid[i][j] = 0;
                    else grid[i][j] = 1;
        }

        for (int i = 0; i < enemyCount; i++)
            if (grid[a[i].y/ts][a[i].x/ts] == 2)
                Game = false;

        window.clear();

        for (int i = 0; i < M; i++)
            for (int j = 0; j < N; j++)
            {
                if (grid[i][j] == 0) continue;

                if (grid[i][j] == 1) sTile.setTextureRect(IntRect(0, 0, ts, ts));
                if (grid[i][j] == 2) sTile.setTextureRect(IntRect(54, 0, ts, ts));

                sTile.setPosition(j * ts, i * ts);
                window.draw(sTile);
            }

        sTile.setTextureRect(IntRect(36, 0, ts, ts));
        sTile.setPosition(x * ts, y * ts);
        window.draw(sTile);

        sEnemy.rotate(10);
        for (int i = 0; i < enemyCount; i++)
        {
            sEnemy.setPosition(a[i].x, a[i].y);
            window.draw(sEnemy);
        }

        if (!Game) window.draw(sGameover);

        window.display();
    }
}


// ---------- GUI DRAW FUNCTION ----------
void drawGUI(RenderWindow &window, Font &font, Text &title,
             RectangleShape &usernameBox, Text &usernameText,
             RectangleShape &emailBox, Text &emailText,
             RectangleShape &passwordBox, Text &passwordText,
             RectangleShape &loginBtn, Text &loginBtnText,
             RectangleShape &signupBtn, Text &signupBtnText,
             RectangleShape &startBtn, Text &startBtnText,
             Text &infoText)
{
    window.clear(Color::Black);
    window.draw(title);

    window.draw(usernameBox);
    window.draw(usernameText);

    window.draw(emailBox);
    window.draw(emailText);

    window.draw(passwordBox);
    window.draw(passwordText);

    window.draw(loginBtn);
    window.draw(loginBtnText);

    window.draw(signupBtn);
    window.draw(signupBtnText);

    window.draw(startBtn);
    window.draw(startBtnText);

    window.draw(infoText);
    window.display();
}

void setPlaceholders(Text &usernameText, Text &emailText, Text &passwordText,
                     const string &typedUsername, const string &typedEmail, const string &typedPassword)
{
    if(typedUsername.empty()) usernameText.setString("Enter username...");
    else usernameText.setString(typedUsername);

    if(typedEmail.empty()) emailText.setString("Enter email...");
    else emailText.setString(typedEmail);

    if(typedPassword.empty()) passwordText.setString("Enter password...");
    else
    {
        string stars(typedPassword.size(), '*');
        passwordText.setString(stars);
    }
}

int main() {
    Auth auth;
    PlayerSys playerSys;
    playerSys.loadAllPlayers();  
    FriendReqAlgo friendSys(&playerSys, &playerSys.hasher);

    RenderWindow window(VideoMode(800, 700), "Mini Social GUI");

    Font font;
    if(!font.loadFromFile("./fonts/arial.ttf")) {
        cout << "Font not found!\n";
        return 1;
    }

    // ---------- GUI ELEMENTS ----------
    Text title("Mini Social GUI", font, 40); title.setFillColor(Color::Cyan); title.setPosition(220,50);

    RectangleShape usernameBox(Vector2f(300,40)); usernameBox.setFillColor(Color(50,50,50)); usernameBox.setPosition(250,180);
    Text usernameText("", font, 20); usernameText.setPosition(255,185); usernameText.setFillColor(Color::White);

    RectangleShape emailBox(Vector2f(300,40)); emailBox.setFillColor(Color(50,50,50)); emailBox.setPosition(250,240);
    Text emailText("", font, 20); emailText.setPosition(255,245); emailText.setFillColor(Color::White);

    RectangleShape passwordBox(Vector2f(300,40)); passwordBox.setFillColor(Color(50,50,50)); passwordBox.setPosition(250,300);
    Text passwordText("", font, 20); passwordText.setPosition(255,305); passwordText.setFillColor(Color::White);

    RectangleShape loginBtn(Vector2f(120,40)); loginBtn.setFillColor(Color::Green); loginBtn.setPosition(250,380);
    Text loginBtnText("Login", font, 20); loginBtnText.setPosition(280,385);

    RectangleShape signupBtn(Vector2f(120,40)); signupBtn.setFillColor(Color::Blue); signupBtn.setPosition(430,380);
    Text signupBtnText("Sign Up", font, 20); signupBtnText.setPosition(445,385);

    RectangleShape startBtn(Vector2f(200,40)); startBtn.setFillColor(Color::Red); startBtn.setPosition(300,450);
    Text startBtnText("Start Game", font, 20); startBtnText.setPosition(330,455);

    // --- FRIEND SYSTEM BUTTONS ---
    RectangleShape viewFriendsBtn(Vector2f(180,40)); viewFriendsBtn.setFillColor(Color(100,200,100)); viewFriendsBtn.setPosition(50,550);
    Text viewFriendsText("View Friends", font, 18); viewFriendsText.setPosition(60,555);

    RectangleShape viewReqBtn(Vector2f(180,40)); viewReqBtn.setFillColor(Color(100,200,200)); viewReqBtn.setPosition(250,550);
    Text viewReqText("View Requests", font, 18); viewReqText.setPosition(260,555);

    RectangleShape sendReqBtn(Vector2f(180,40)); sendReqBtn.setFillColor(Color(200,100,100)); sendReqBtn.setPosition(450,550);
    Text sendReqText("Send Request", font, 18); sendReqText.setPosition(460,555);

    // --- FRIEND DISPLAY BOXES ---
    RectangleShape friendsBox(Vector2f(300,150)); friendsBox.setFillColor(Color(30,30,30)); friendsBox.setPosition(50,400);
    Text friendsText("", font, 16); friendsText.setPosition(60,410); friendsText.setFillColor(Color::White);

    RectangleShape reqBox(Vector2f(300,150)); reqBox.setFillColor(Color(30,30,30)); reqBox.setPosition(400,400);
    Text reqText("", font, 16); reqText.setPosition(410,410); reqText.setFillColor(Color::White);

    RectangleShape friendInputBox(Vector2f(180,30)); friendInputBox.setFillColor(Color(50,50,50)); friendInputBox.setPosition(450,510);
    Text friendInputText("", font, 16); friendInputText.setPosition(455,515); friendInputText.setFillColor(Color::White);

    RectangleShape infoTextBox(Vector2f(700,40)); infoTextBox.setFillColor(Color(50,50,50)); infoTextBox.setPosition(50,610);
    Text infoText("", font, 18); infoText.setFillColor(Color::Yellow); infoText.setPosition(60,615);

    string typedUsername="", typedEmail="", typedPassword="", typedFriendName="";
    bool typingUsername=false, typingEmail=false, typingPassword=false, typingFriend=false;
    string loggedInUser="";

    while(window.isOpen()) {
        Event event;
        while(window.pollEvent(event)) {
            if(event.type == Event::Closed) window.close();

            if(event.type == Event::MouseButtonPressed) {
                Vector2i mousePos = Mouse::getPosition(window);

                typingUsername = usernameBox.getGlobalBounds().contains(mousePos.x, mousePos.y);
                typingEmail    = emailBox.getGlobalBounds().contains(mousePos.x, mousePos.y);
                typingPassword = passwordBox.getGlobalBounds().contains(mousePos.x, mousePos.y);
                typingFriend   = friendInputBox.getGlobalBounds().contains(mousePos.x, mousePos.y);

                if(typingUsername) typingEmail = typingPassword = typingFriend = false;
                if(typingEmail) typingUsername = typingPassword = typingFriend = false;
                if(typingPassword) typingUsername = typingEmail = typingFriend = false;

                // --- LOGIN ---
                if(loginBtn.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    if(!typedUsername.empty() && !typedPassword.empty()) {
                        loggedInUser = auth.login(typedUsername, typedPassword);
                        if(!loggedInUser.empty()) infoText.setString("Logged in as: "+loggedInUser);
                        else infoText.setString("Login failed!");
                    } else infoText.setString("Enter username & password");
                }

                // --- SIGNUP ---
                if(signupBtn.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    if(!typedUsername.empty() && !typedEmail.empty() && !typedPassword.empty()) {
                        if(auth.signupGUI(typedUsername, typedEmail, typedPassword)) {
                            loggedInUser = typedUsername;
                            infoText.setString("Signed up & logged in as: "+loggedInUser);
                            playerSys.loadAllPlayers();
                        } else infoText.setString("Signup failed! Check email/pass rules.");
                    } else infoText.setString("Enter username, email & password");
                }

                // --- START GAME ---
                if(startBtn.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    if(!loggedInUser.empty()) {
                        window.close();
                        startGame();
                    } else infoText.setString("Login first to start game!");
                }

                // --- FRIEND SYSTEM ---
                if(!loggedInUser.empty()) {
                    if(viewFriendsBtn.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        string display="";
                        Player &p = playerSys.players[playerSys.findPlayer(loggedInUser)];
                        FriendNode *curr = p.friendsHead;
                        while(curr) { display += curr->name + "\n"; curr=curr->next; }
                        friendsText.setString(display.empty() ? "No friends yet." : display);
                        infoText.setString("Friends displayed.");
                    }

                    if(viewReqBtn.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        string display="";
                        Player &p = playerSys.players[playerSys.findPlayer(loggedInUser)];
                        RequestNode *curr = p.requestsHead;
                        while(curr) { display += curr->name + "\n"; curr=curr->next; }
                        reqText.setString(display.empty() ? "No pending requests." : display);
                        infoText.setString("Requests displayed.");
                    }

                    if(sendReqBtn.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        if(!typedFriendName.empty()) {
                            friendSys.sendReq(loggedInUser, typedFriendName);
                            infoText.setString("Request sent to " + typedFriendName);
                            typedFriendName="";
                            friendInputText.setString("");
                        } else infoText.setString("Type friend username to send request.");
                    }
                }
            }

            // --- TEXT INPUT ---
            if(event.type == Event::TextEntered) {
                if(event.text.unicode < 128) {
                    char c = static_cast<char>(event.text.unicode);
                    if(typingUsername) { if(c==8 && !typedUsername.empty()) typedUsername.pop_back(); else if(c!=8) typedUsername+=c; }
                    if(typingEmail)    { if(c==8 && !typedEmail.empty()) typedEmail.pop_back();    else if(c!=8) typedEmail+=c; }
                    if(typingPassword) { if(c==8 && !typedPassword.empty()) typedPassword.pop_back(); else if(c!=8) typedPassword+=c; }
                    if(typingFriend)   { if(c==8 && !typedFriendName.empty()) typedFriendName.pop_back(); else if(c!=8) typedFriendName+=c; friendInputText.setString(typedFriendName);}
                }
            }
        }

        // --- PLACEHOLDERS ---
        setPlaceholders(usernameText, emailText, passwordText, typedUsername, typedEmail, typedPassword);
        if(typedFriendName.empty()) friendInputText.setString("Enter friend username...");

        // --- DRAW ---
        window.clear(Color::Black);
        window.draw(title);

        window.draw(usernameBox); window.draw(usernameText);
        window.draw(emailBox); window.draw(emailText);
        window.draw(passwordBox); window.draw(passwordText);

        window.draw(loginBtn); window.draw(loginBtnText);
        window.draw(signupBtn); window.draw(signupBtnText);
        window.draw(startBtn); window.draw(startBtnText);

        window.draw(viewFriendsBtn); window.draw(viewFriendsText);
        window.draw(viewReqBtn); window.draw(viewReqText);
        window.draw(sendReqBtn); window.draw(sendReqText);

        window.draw(friendsBox); window.draw(friendsText);
        window.draw(reqBox); window.draw(reqText);
        window.draw(friendInputBox); window.draw(friendInputText);

        window.draw(infoTextBox); window.draw(infoText);

        window.display();
    }

    return 0;
}
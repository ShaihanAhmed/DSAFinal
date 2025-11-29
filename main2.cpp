#include <SFML/Graphics.hpp>
#include <iostream>
#include "Auth.h"
#include "PlayerSys.h"
#include "FriendReqALGO.h"
#include "leaderboard.h"
using namespace sf;
using namespace std;

int g_lastScore = 0;
bool g_lastWin = false;

// ---------- Helper Functions ----------
void setPlaceholders(Text &usernameText, Text &emailText, Text &passwordText, const string &typedUsername, const string &typedEmail, const string &typedPassword)
{
    usernameText.setString(typedUsername.empty() ? "Enter username..." : typedUsername);
    emailText.setString(typedEmail.empty() ? "Enter email..." : typedEmail);
    passwordText.setString(typedPassword.empty() ? "Enter password..." : string(typedPassword.size(), '*'));
}

// Draw popup box with close button
void drawPopup(RenderWindow &window, RectangleShape &popupBox, Text &popupText, RectangleShape &closeBtn, Text &closeText)
{
    window.draw(popupBox);
    window.draw(popupText);
    window.draw(closeBtn);
    window.draw(closeText);
}

const int M = 25;
const int N = 40;
int grid[M][N] = {0};
int ts = 18; // tile size

struct Enemy
{
    int x, y, dx, dy;
    Enemy()
    {
        x = y = 300;
        dx = 4 - rand() % 8;
        dy = 4 - rand() % 8;
    }
    void move()
    {
        x += dx;
        if (grid[y / ts][x / ts] == 1)
        {
            dx = -dx;
            x += dx;
        }

        y += dy;
        if (grid[y / ts][x / ts] == 1)
        {
            dy = -dy;
            y += dy;
        }
    }
};

void drop(int y, int x)
{
    if (grid[y][x] == 0)
        grid[y][x] = -1;
    if (grid[y - 1][x] == 0)
        drop(y - 1, x);
    if (grid[y + 1][x] == 0)
        drop(y + 1, x);
    if (grid[y][x - 1] == 0)
        drop(y, x - 1);
    if (grid[y][x + 1] == 0)
        drop(y, x + 1);
}

// imp for storing total points ------------------------------------------------
// imp for storing total points ------------------------------------------------
// imp for storing total points ------------------------------------------------

void resetGameState(int &x, int &y, int &dx, int &dy, int grid[M][N], Enemy a[], int enemyCount)
{
    // Reset player position
    x = 0;
    y = 0;
    dx = dy = 0;

    // Reset grid
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            grid[i][j] = (i == 0 || j == 0 || i == M - 1 || j == N - 1) ? 1 : 0;

    // Reset enemies
    for (int i = 0; i < enemyCount; i++)
        a[i] = Enemy(); // reinitialize enemy positions
}

int startGame(string user)
{
    int tilesCaptured = 0;
    int score = 0;
    int bonusCount = 0;
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

    resetGameState(x, y, dx, dy, grid, a, enemyCount);

    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            if (i == 0 || j == 0 || i == M - 1 || j == N - 1)
                grid[i][j] = 1;

    Font font;
    if (!font.loadFromFile("fonts/arial.ttf"))
    {
        cout << "Font not found!\n";
        return 0;
    }

    Text scoreText("", font, 24);
    scoreText.setFillColor(Color::Yellow);
    scoreText.setPosition(10, 10);

    Text bonusText("", font, 20);
    bonusText.setFillColor(Color::Cyan);
    bonusText.setPosition(10, 40);

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

            if (e.type == Event::KeyPressed && e.key.code == Keyboard::Escape)
            {
                for (int i = 1; i < M - 1; i++)
                    for (int j = 1; j < N - 1; j++)
                        grid[i][j] = 0;

                x = 10;
                y = 0;
                Game = true;
                score = 0;
                bonusCount = 0;
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Left))
        {
            dx = -1;
            dy = 0;
        }
        if (Keyboard::isKeyPressed(Keyboard::Right))
        {
            dx = 1;
            dy = 0;
        }
        if (Keyboard::isKeyPressed(Keyboard::Up))
        {
            dx = 0;
            dy = -1;
        }
        if (Keyboard::isKeyPressed(Keyboard::Down))
        {
            dx = 0;
            dy = 1;
        }

        if (!Game)
        {
            while (window.isOpen())
            {
                Event e;
                while (window.pollEvent(e))
                {
                    if (e.type == Event::Closed)
                        return score;

                    if (e.type == Event::KeyPressed)
                    {
                        if (e.key.code == Keyboard::R)
                        {
                            LeaderBoard(score, user);
                            return startGame(user);
                        }

                        if (e.key.code == Keyboard::M)
                        {
                            LeaderBoard(score, user);
                            return score;
                        }

                        if (e.key.code == Keyboard::Escape)
                        {
                            LeaderBoard(score, user);
                            exit(0);
                        }
                    }
                }

                window.clear();
                window.draw(sGameover);

                // Show instructions
                Text opt;
                opt.setFont(font);
                opt.setCharacterSize(24);
                opt.setFillColor(Color::White);
                opt.setString("Press R to Restart\nPress M for Main Menu\nPress ESC to Exit");
                opt.setPosition(120, 350);

                window.draw(opt);
                window.display();
            }
        }

        if (timer > delay)
        {
            x += dx;
            y += dy;

            if (x < 0)
                x = 0;
            if (x > N - 1)
                x = N - 1;
            if (y < 0)
                y = 0;
            if (y > M - 1)
                y = M - 1;

            if (grid[y][x] == 2)
                Game = false;
            if (grid[y][x] == 0)
                grid[y][x] = 2;

            timer = 0;
        }

        for (int i = 0; i < enemyCount; i++)
            a[i].move();

        if (grid[y][x] == 1)
        {
            tilesCaptured = 0;
            dx = dy = 0;

            for (int i = 0; i < enemyCount; i++)
                drop(a[i].y / ts, a[i].x / ts);

            for (int i = 0; i < M; i++)
                for (int j = 0; j < N; j++)
                {
                    if (grid[i][j] == -1)
                        grid[i][j] = 0;
                    else if (grid[i][j] == 0 || grid[i][j] == 2)
                    {
                        grid[i][j] = 1;
                        tilesCaptured++;
                    }
                }

            int threshold = (bonusCount <= 2) ? 10 : 5;
            int multiplier = (bonusCount > 5) ? 4 : 2;

            if (tilesCaptured > threshold)
            {
                score += tilesCaptured * multiplier;
                bonusCount++;
            }
            else if (tilesCaptured > 0)
            {
                score += tilesCaptured;
            }
        }

        for (int i = 0; i < enemyCount; i++)
            if (grid[a[i].y / ts][a[i].x / ts] == 2)
                Game = false;

        scoreText.setString("Score: " + to_string(score));
        bonusText.setString("Bonus: " + to_string(bonusCount));

        window.clear();
        for (int i = 0; i < M; i++)
            for (int j = 0; j < N; j++)
            {
                if (grid[i][j] == 0)
                    continue;
                sTile.setTextureRect(IntRect((grid[i][j] == 1) ? 0 : 54, 0, ts, ts));
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

        window.draw(scoreText);
        window.draw(bonusText);

        window.display();
    }

    return score; // final score returned
}

void updateInfoText(const std::string &username, PlayerSys &playerSys, sf::Text &infoText)
{
    int idx = playerSys.findPlayer(username);
    if (idx != -1)
    {
        Player &pl = playerSys.players[idx];
        infoText.setString("Player: " + pl.getName() +
                           "\nTotal Points: " + std::to_string(pl.total) +
                           "\nWins: " + std::to_string(pl.wins) +
                           "\nLosses: " + std::to_string(pl.losses));
    }
    else
    {
        infoText.setString("Player not found.");
    }
}

// for achieveing new high score
bool showHighScorePopup = false;
int lastScore = 0;

// Helper to update info text
int main()
{
    Auth auth;
    PlayerSys playerSys;
    playerSys.loadAllPlayers();
    FriendReqAlgo friendSys(&playerSys, &playerSys.hasher);

    RenderWindow window(VideoMode(800, 700), "XONIX");
    Font font;
    if (!font.loadFromFile("./fonts/arial.ttf"))
    {
        cout << "Font not found!\n";
        return 1;
    }

    // ---------- GUI ELEMENTS ----------
    Text title("XONIX", font, 40);
    title.setFillColor(Color::Cyan);
    title.setPosition(220, 50);

    // Login fields
    RectangleShape usernameBox(Vector2f(300, 40));
    usernameBox.setFillColor(Color(50, 50, 50));
    usernameBox.setPosition(250, 180);
    Text usernameText("", font, 20);
    usernameText.setPosition(255, 185);
    usernameText.setFillColor(Color::White);

    RectangleShape emailBox(Vector2f(300, 40));
    emailBox.setFillColor(Color(50, 50, 50));
    emailBox.setPosition(250, 240);
    Text emailText("", font, 20);
    emailText.setPosition(255, 245);
    emailText.setFillColor(Color::White);

    RectangleShape passwordBox(Vector2f(300, 40));
    passwordBox.setFillColor(Color(50, 50, 50));
    passwordBox.setPosition(250, 300);
    Text passwordText("", font, 20);
    passwordText.setPosition(255, 305);
    passwordText.setFillColor(Color::White);

    // Buttons
    RectangleShape loginBtn(Vector2f(120, 40));
    loginBtn.setFillColor(Color::Green);
    loginBtn.setPosition(250, 380);
    Text loginBtnText("Login", font, 20);
    loginBtnText.setPosition(280, 385);

    RectangleShape signupBtn(Vector2f(120, 40));
    signupBtn.setFillColor(Color::Blue);
    signupBtn.setPosition(430, 380);
    Text signupBtnText("Sign Up", font, 20);
    signupBtnText.setPosition(445, 385);

    // Post-login menu
    RectangleShape startBtn(Vector2f(200, 50));
    startBtn.setFillColor(Color::Red);
    startBtn.setPosition(50, 150);
    Text startBtnText("Start Game", font, 20);
    startBtnText.setPosition(80, 165);

    RectangleShape viewFriendsBtn(Vector2f(200, 50));
    viewFriendsBtn.setFillColor(Color(100, 200, 100));
    viewFriendsBtn.setPosition(50, 220);
    Text viewFriendsText("View Friends", font, 20);
    viewFriendsText.setPosition(80, 235);

    RectangleShape sendReqBtn(Vector2f(200, 50));
    sendReqBtn.setFillColor(Color(200, 100, 100));
    sendReqBtn.setPosition(50, 290);
    Text sendReqText("Send Request", font, 20);
    sendReqText.setPosition(80, 305);

    RectangleShape viewReqBtn(Vector2f(200, 50));
    viewReqBtn.setFillColor(Color(100, 200, 200));
    viewReqBtn.setPosition(50, 360);
    Text viewReqText("Pending Requests", font, 20);
    viewReqText.setPosition(60, 375);

    Text infoText("", font, 18);
    infoText.setFillColor(Color::Yellow);
    infoText.setPosition(50, 620);

    // Popup
    RectangleShape popupBox(Vector2f(500, 300));
    popupBox.setFillColor(Color(30, 30, 30));
    popupBox.setPosition(150, 200);
    Text popupText("", font, 18);
    popupText.setFillColor(Color::White);
    popupText.setPosition(160, 220);

    RectangleShape closeBtn(Vector2f(100, 40));
    closeBtn.setFillColor(Color::Red);
    closeBtn.setPosition(330, 430);
    Text closeText("Close", font, 20);
    closeText.setPosition(355, 435);

    // Accept/Reject buttons
    RectangleShape acceptBtn(Vector2f(120, 40));
    acceptBtn.setFillColor(Color::Green);
    acceptBtn.setPosition(200, 400);
    Text acceptText("Accept", font, 20);
    acceptText.setPosition(225, 405);

    RectangleShape rejectBtn(Vector2f(120, 40));
    rejectBtn.setFillColor(Color::Red);
    rejectBtn.setPosition(400, 400);
    Text rejectText("Reject", font, 20);
    rejectText.setPosition(425, 405);

    // --- State variables ---
    string typedUsername = "", typedEmail = "", typedPassword = "", typedFriendName = "";
    bool typingUsername = false, typingEmail = false, typingPassword = false, typingFriend = false;
    string loggedInUser = "";
    bool showPopup = false;
    bool handlingRequest = false;
    Player *pl = nullptr; // ✅ make it global in loop

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::MouseButtonPressed)
            {
                Vector2i mousePos = Mouse::getPosition(window);

                // Activate typing boxes
                typingUsername = usernameBox.getGlobalBounds().contains(mousePos.x, mousePos.y);
                typingEmail = emailBox.getGlobalBounds().contains(mousePos.x, mousePos.y);
                typingPassword = passwordBox.getGlobalBounds().contains(mousePos.x, mousePos.y);

                // LOGIN / SIGNUP
                if (loggedInUser.empty())
                {
                    if (loginBtn.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {
                        if (!typedUsername.empty() && !typedPassword.empty())
                        {
                            loggedInUser = auth.login(typedUsername, typedPassword);
                            if (!loggedInUser.empty())
                                updateInfoText(loggedInUser, playerSys, infoText);
                            else
                                infoText.setString("Login failed!");
                        }
                        else
                            infoText.setString("Enter username & password");
                    }

                    if (signupBtn.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {
                        if (!typedUsername.empty() && !typedEmail.empty() && !typedPassword.empty())
                        {
                            if (auth.signupGUI(typedUsername, typedEmail, typedPassword))
                            {
                                Player newP;
                                newP.setCreds(typedUsername, typedPassword, typedEmail);
                                playerSys.addPlayer(newP);

                                loggedInUser = typedUsername;
                                updateInfoText(loggedInUser, playerSys, infoText);
                            }
                            else
                                infoText.setString("Signup failed!");
                        }
                        else
                            infoText.setString("Enter username, email & password");
                    }
                }
                else // POST-LOGIN MENU
                {
                    int idx = playerSys.findPlayer(loggedInUser);
                    pl = (idx != -1) ? &playerSys.players[idx] : nullptr;
                    if (!pl)
                        continue;

                    if (startBtn.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {
                        string user = auth.getLastLoggedInUsername();
                        int score = startGame(user);
                        // if (score > pl->total)
                        //     pl->total = score;
                        //     // showHighScorePopup = true;

                        if (score > pl->total)
                        {
                            pl->total = score;
                            showHighScorePopup = true; // ⭐ TRIGGER POPUP HERE
                        }

                        pl->saveToFile("./users/" + pl->getName() + ".txt");
                        updateInfoText(loggedInUser, playerSys, infoText);
                    }

                    if (viewFriendsBtn.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {
                        popupText.setString(friendSys.getFriendsStr(loggedInUser));
                        showPopup = true;
                        handlingRequest = false;
                    }

                    if (viewReqBtn.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {
                        RequestNode *firstReq = pl->requestsHead;
                        if (firstReq)
                        {
                            popupText.setString("Pending request from: " + firstReq->name);
                            handlingRequest = true;
                        }
                        else
                        {
                            popupText.setString("No pending requests.");
                            handlingRequest = false;
                        }
                        showPopup = true;
                    }

                    if (sendReqBtn.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {
                        popupText.setString("Enter friend's username:\n");
                        typedFriendName = "";
                        typingFriend = true;
                        showPopup = true;
                    }
                }

                // CLOSE POPUP
                if (showPopup && closeBtn.getGlobalBounds().contains(mousePos.x, mousePos.y))
                {
                    showPopup = false;
                    typingFriend = false;
                    handlingRequest = false;
                }

                // ACCEPT / REJECT
                if (showPopup && handlingRequest && pl)
                {
                    RequestNode *firstReq = pl->requestsHead;
                    if (firstReq)
                    {
                        string reqName = firstReq->name;

                        if (acceptBtn.getGlobalBounds().contains(mousePos.x, mousePos.y))
                        {
                            friendSys.acceptReq(loggedInUser, reqName);
                            firstReq = pl->requestsHead;
                        }

                        if (rejectBtn.getGlobalBounds().contains(mousePos.x, mousePos.y))
                        {
                            friendSys.rejectReq(loggedInUser, reqName);
                            firstReq = pl->requestsHead;
                        }

                        if (firstReq)
                            popupText.setString("Pending request from: " + firstReq->name);
                        else
                            handlingRequest = false;
                    }
                }
            }

            // TEXT INPUT
            if (event.type == Event::TextEntered)
            {
                if (event.text.unicode < 128)
                {
                    char c = static_cast<char>(event.text.unicode);
                    if (typingUsername)
                    {
                        if (c == 8 && !typedUsername.empty())
                            typedUsername.pop_back();
                        else if (c != 8)
                            typedUsername += c;
                    }
                    if (typingEmail)
                    {
                        if (c == 8 && !typedEmail.empty())
                            typedEmail.pop_back();
                        else if (c != 8)
                            typedEmail += c;
                    }
                    if (typingPassword)
                    {
                        if (c == 8 && !typedPassword.empty())
                            typedPassword.pop_back();
                        else if (c != 8)
                            typedPassword += c;
                    }
                    if (typingFriend)
                    {
                        if (c == 8 && !typedFriendName.empty())
                            typedFriendName.pop_back();
                        else if (c != 8 && c != '\r')
                            typedFriendName += c;
                        popupText.setString("Enter friend's username:\n" + typedFriendName);
                    }
                }
            }

            // ENTER KEY FRIEND REQUEST
            if (event.type == Event::KeyPressed && typingFriend && event.key.code == Keyboard::Enter)
            {
                if (!typedFriendName.empty() && !loggedInUser.empty())
                {
                    // friendSys.sendReq(loggedInUser, typedFriendName);
                    // popupText.setString("Request sent to: " + typedFriendName);
                    // typedFriendName = "";

                    string msg = friendSys.sendReq(loggedInUser, typedFriendName);
                    popupText.setString(msg); // shows success or error message
                    typedFriendName = "";
                }
                typingFriend = false;
            }
        }

        // placeholders
        setPlaceholders(usernameText, emailText, passwordText, typedUsername, typedEmail, typedPassword);

        // DRAW
        window.clear(Color::Black);
        window.draw(title);

        if (loggedInUser.empty())
        {
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
        }
        else
        {
            window.draw(startBtn);
            window.draw(startBtnText);
            window.draw(viewFriendsBtn);
            window.draw(viewFriendsText);
            window.draw(sendReqBtn);
            window.draw(sendReqText);
            window.draw(viewReqBtn);
            window.draw(viewReqText);
        }

        window.draw(infoText);

        if (showPopup)
        {
            drawPopup(window, popupBox, popupText, closeBtn, closeText);
            if (handlingRequest)
            {
                window.draw(acceptBtn);
                window.draw(acceptText);
                window.draw(rejectBtn);
                window.draw(rejectText);
            }
        }

        window.display();
    }

    return 0;
}
// #include <SFML/Graphics.hpp>
// #include <time.h>
// using namespace sf;

// const int M = 25;
// const int N = 40;

// int grid[M][N] = {0};
// int ts = 18; //tile size

// struct Enemy
// {int x,y,dx,dy;

//   Enemy()
//    {
//     x=y=300;
//     dx=4-rand()%8;
//     dy=4-rand()%8;
//    }

//   void move()
//    { 
//     x+=dx; if (grid[y/ts][x/ts]==1) {dx=-dx; x+=dx;}
//     y+=dy; if (grid[y/ts][x/ts]==1) {dy=-dy; y+=dy;}
//    }
// };

// void drop(int y,int x)
// {
//   if (grid[y][x]==0) grid[y][x]=-1;
//   if (grid[y-1][x]==0) drop(y-1,x);
//   if (grid[y+1][x]==0) drop(y+1,x);
//   if (grid[y][x-1]==0) drop(y,x-1);
//   if (grid[y][x+1]==0) drop(y,x+1);
// }
// int main()
// {
//     srand(time(0));

//     RenderWindow window(VideoMode(N*ts, M*ts), "Xonix Game!");
//     window.setFramerateLimit(60);

//     Texture t1,t2,t3;
//     t1.loadFromFile("images/tiles.png");
//     t2.loadFromFile("images/gameover.png");
//     t3.loadFromFile("images/enemy.png");

//     Sprite sTile(t1), sGameover(t2), sEnemy(t3);
//     sGameover.setPosition(100,100);
//     sEnemy.setOrigin(20,20);

//     int enemyCount = 4;
//     Enemy a[10];

//     bool Game=true;
//     int x=0, y=0, dx=0, dy=0;
//     float timer=0, delay=0.07; 
//     Clock clock;

//     for (int i=0;i<M;i++)
//      for (int j=0;j<N;j++)
//       if (i==0 || j==0 || i==M-1 || j==N-1)  grid[i][j]=1;

//     while (window.isOpen())
//     {
//         float time = clock.getElapsedTime().asSeconds();
//         clock.restart();
//         timer+=time;

//         Event e;
//         while (window.pollEvent(e))
//         {
//             if (e.type == Event::Closed)
//                 window.close();
               
//             if (e.type == Event::KeyPressed)
//              if (e.key.code==Keyboard::Escape)
//                {
//                 for (int i=1;i<M-1;i++)
//                  for (int j=1;j<N-1;j++)
//                    grid[i][j]=0;

//                 x=10;y=0;
//                 Game=true;
//                }
//         }

//         if (Keyboard::isKeyPressed(Keyboard::Left)) {dx=-1;dy=0;};
//         if (Keyboard::isKeyPressed(Keyboard::Right))  {dx=1;dy=0;};
//         if (Keyboard::isKeyPressed(Keyboard::Up)) {dx=0;dy=-1;};
//         if (Keyboard::isKeyPressed(Keyboard::Down)) {dx=0;dy=1;};
        
//         if (!Game) continue;

//         if (timer>delay)
//         {
//          x+=dx;
//          y+=dy;

//          if (x<0) x=0; if (x>N-1) x=N-1;
//          if (y<0) y=0; if (y>M-1) y=M-1;

//          if (grid[y][x]==2) Game=false;
//          if (grid[y][x]==0) grid[y][x]=2;
//          timer=0;
//         }

//         for (int i=0;i<enemyCount;i++) a[i].move();

//         if (grid[y][x]==1)
//           {
//            dx=dy=0;

//            for (int i=0;i<enemyCount;i++)
//                 drop(a[i].y/ts, a[i].x/ts);

//            for (int i=0;i<M;i++)
//              for (int j=0;j<N;j++)
//               if (grid[i][j]==-1) grid[i][j]=0;
//               else grid[i][j]=1;
//           }

//         for (int i=0;i<enemyCount;i++)
//            if  (grid[a[i].y/ts][a[i].x/ts]==2) Game=false;

//       /////////draw//////////
//       window.clear();

//       for (int i=0;i<M;i++)
//         for (int j=0;j<N;j++)
//          {
//             if (grid[i][j]==0) continue;
//             if (grid[i][j]==1) sTile.setTextureRect(IntRect( 0,0,ts,ts));
//             if (grid[i][j]==2) sTile.setTextureRect(IntRect(54,0,ts,ts));
//             sTile.setPosition(j*ts,i*ts);
//             window.draw(sTile);
//          }

//       sTile.setTextureRect(IntRect(36,0,ts,ts));
//       sTile.setPosition(x*ts,y*ts);
//       window.draw(sTile);

//       sEnemy.rotate(10);
//       for (int i=0;i<enemyCount;i++)
//        {
//         sEnemy.setPosition(a[i].x,a[i].y);
//         window.draw(sEnemy);
//        }

//       if (!Game) window.draw(sGameover);

//        window.display();
//     }

//     return 0;
// }


// ------------------------ fall back point ----------------------------
#include <iostream>
#include "Auth.h"
#include <SFML/Graphics.hpp>
#include <time.h>
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

// int main() {
//     Auth obj;
//     bool authenticated = false;

//     while (!authenticated) {
//         int choice;
//         cout << "\n----- XONIX GAME LOGIN -----\n";
//         cout << "1. Sign Up\n";
//         cout << "2. Login\n";
//         cout << "3. Quit\n";
//         cout << "Enter choice: ";
//         cin >> choice;

//         if (choice == 1)
//             authenticated = obj.signupCLI();  // returns true if signup successful
//         else if (choice == 2)
//             authenticated = obj.loginCLI();   // returns true if login successful
//         else if (choice == 3) {
//             cout << "Exiting...\n";
//             return 0;
//         } else {
//             cout << "Invalid choice! Try again.\n";
//             continue;
//         }

//         if (!authenticated)
//             cout << "Try again or choose a different option.\n";
//     }

//     cout << "\nStarting game...\n";
//     startGame();

//     return 0;
// }

//--------------------------- my auth main imp ----------------------
int main() {
    Auth obj;
    bool authenticated = false;

    while (!authenticated) {
        int choice;
        cout << "\033[36m\n----- XONIX GAME LOGIN -----\033[0m\n"; // cyan
        cout << "\033[32m1. Sign Up\033[0m\n";                     // green
        cout << "\033[34m2. Login\033[0m\n";                       // blue
        cout << "\033[31m3. Quit\033[0m\n";                        // red
        cout << "\033[37mEnter choice: \033[0m";                   // white
        cin >> choice;

        if (choice == 1) {
            authenticated = obj.signup();
        }
        else if (choice == 2) {
            authenticated = obj.login();
        }
        else if (choice == 3) {
            cout << "\033[31mExiting...\033[0m\n";
            return 0;
        }
        else {
            cout << "\033[31mInvalid choice! Try again.\033[0m\n";
        }
    }

    cout << "\033[32m\nAuthentication successful! Starting game...\033[0m\n";

    startGame();

    return 0;
}


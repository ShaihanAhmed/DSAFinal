#include "Auth.h"
//-----------------------------------------------------------------------------
#define DEFAULT "\033[37m"
#define BLUE "\033[34m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#include <SFML/Graphics.hpp>

// ----------------------- Private -----------------------
string Auth::filePath(string a, string b, string c) {
    a += b;
    a += c;
    return a;
}

bool Auth::compare(const string a, const string b) {
    return (a == b);
}

bool Auth::ifExist(string fp) {
    fstream userFile(fp, ios::in);
    if (userFile) {
        userFile.close();
        return true;
    }
    return false;
}

bool Auth::isStrongPassword(const string b) {
    bool hasUpperCase = false, hasLowerCase = false, hasDigit = false;
    int count = 0;
    for (int i = 0; b[i] != '\0'; i++) {
        if (b[i] >= 'A' && b[i] <= 'Z') hasUpperCase = true;
        else if (b[i] >= 'a' && b[i] <= 'z') hasLowerCase = true;
        else if (b[i] >= '0' && b[i] <= '9') hasDigit = true;
        count++;
    }
    return ((count > 7) && hasUpperCase && hasLowerCase && hasDigit);
}

void Auth::enc(string &a) {
    for (int i = 0; a[i] != '\0'; i++) {
        if (a[i] >= 'a' && a[i] <= 'z') a[i] = (a[i] - 97 + 13) % 26 + 97;
        else if (a[i] >= 'A' && a[i] <= 'Z') a[i] = (a[i] - 65 + 13) % 26 + 65;
        else if (a[i] >= '0' && a[i] <= '9') a[i] = (a[i] - 48 + 8) % 10 + 48;
    }
}

bool Auth::valiEm(const string a) {
    bool flag1 = false, flag2 = false;
    for (int i = 0; a[i] != '\0'; i++) {
        if (a[i] == '@') flag1 = true;
        if (a[i] == '.') flag2 = true;
    }
    return flag1 && flag2;
}

bool Auth::passVali(const string a, const string b, const string path) {
    fstream userFile(path, ios::in);
    if (userFile) {
        char name[20], p[25];
        userFile.getline(name, 20, ',');
        userFile.getline(p, 25, ',');
        userFile.close();
        return (compare(a, name) && compare(b, p));
    }
    return false;
}

// ----------------------- Public -----------------------
// bool Auth::signup() {
//     string fn = "", email = "", pass = "";
//     string pathFull = "./users/";
//     string extFull = ".txt";

//     cin.ignore();
//     cout << GREEN << "\nEnter your username: ";
//     getline(cin, fn, '\n');

//     const string fp = filePath(pathFull, fn, extFull);

//     if (ifExist(fp)) {
//         cout << RED << "\nUser already exists! Please log in.\n";
//         return false;
//     }

//     // Validate email
//     bool vali;
//     do {
//         cout << CYAN << "\nEnter your email: ";
//         getline(cin, email, '\n');
//         vali = valiEm(email);
//         if (!vali) cout << RED << "Invalid email!\n";
//     } while (!vali);

//     // Validate password
//     do {
//         cout << CYAN << "\nEnter your password: ";
//         getline(cin, pass, '\n');
//         vali = isStrongPassword(pass);
//         if (!vali) cout << RED << "Weak password!\n";
//     } while (!vali);

//     enc(pass);

//     ofstream o1(fp);
//     if (!o1) { cout << RED << "Failed to create file!\n"; return false; }

//     // Write full 5-line default file
//     o1 << fn << "," << pass << "," << email << "\n";  // creds
//     o1 << "0,0,0\n";                                  // stats: total,wins,losses
//     o1 << "\n";                                       // friends
//     o1 << "\n";                                       // requests
//     o1 << "1\n";                                      // themeID
//     o1.close();

//     lastUsername = fn;  // store signed-up username
//     cout << BLUE << "\nWelcome " << fn << "!\n";

//     return true;
// }

// ------------------------------- gui based sign up -----------------------------
// GUI-compatible signup

bool Auth::signupGUI(const string &fn, const string &email, const string &passInput) {
    const string pathFull = "./users/";
    const string extFull = ".txt";
    const string fp = filePath(pathFull, fn, extFull);

    if (ifExist(fp)) {
        return false; // user already exists
    }

    if (!valiEm(email)) {
        return false; // invalid email
    }

    if (!isStrongPassword(passInput)) {
        return false; // weak password
    }

    string pass = passInput;
    enc(pass);

    ofstream o1(fp);
    if (!o1) return false;

    // Write full 5-line default file
    o1 << fn << "," << pass << "," << email << "\n"; // creds
    o1 << "0,0,0\n";                                 // stats: total,wins,losses
    o1 << "\n";                                      // friends
    o1 << "\n";                                      // requests
    o1 << "1\n";                                     // themeID
    o1.close();

    lastUsername = fn; // store signed-up username
    return true;
}

// --------------------------------------------------------------------------

// Auth.cpp
//changing log in

// string Auth::login() {
//     string fn, pass;
//     cout << "\nEnter your username: ";
//     cin >> fn;
//     cout << "Enter your password: ";
//     cin >> pass;

//     const string fp = filePath("./users/", fn, ".txt");
//     if (!ifExist(fp)) {
//         cout << "User not found!\n";
//         return ""; // login failed
//     }

//     // Load file and check password
//     ifstream fin(fp);
//     string line;
//     getline(fin, line);
//     int c1 = line.find(',');
//     int c2 = line.find(',', c1 + 1);
//     string savedPass = line.substr(c1 + 1, c2 - c1 - 1);

//     enc(pass); // encrypt input to compare
//     if (pass != savedPass) {
//         cout << "Incorrect password!\n";
//         return "";
//     }

//     cout << "Welcome back, " << fn << "!\n";
//     return fn; // return the username
// }

//-------------------------------------- gui based login ---------------------------------------

string Auth::login(const string &fn, const string &passInput) {
    const string fp = filePath("./users/", fn, ".txt");
    if (!ifExist(fp)) {
        return ""; // user not found
    }

    ifstream fin(fp);
    string line;
    getline(fin, line);
    int c1 = line.find(',');
    int c2 = line.find(',', c1 + 1);
    string savedPass = line.substr(c1 + 1, c2 - c1 - 1);

    string pass = passInput;
    enc(pass); // encrypt input
    if (pass != savedPass) {
        return ""; // incorrect password
    }

    lastUsername = fn;
    return fn; // login success
}

// ----------------------- Getters -----------------------
string Auth::getLastSignedUpUsername() {
    return lastUsername;
}

string Auth::getLastLoggedInUsername() {
    return lastUsername;
}

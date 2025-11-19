#include "Auth.h"

#define DEFAULT "\033[37m"
#define BLUE "\033[34m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define MAGENTA "\033[35m"
#define cyan "\033[36m"

//-----------------------Private functions-----------------------
string Auth::filePath(string a, string b, string c)
{ //  a = path , b = fn , c ext - fn - ext ko const rakha takai no one changes it!
    a += b;
    a += c;

    cout << "path demo test : " << a << endl;

    return a;
}

bool Auth::compare(const string a, const string b)
{
    return (a == b);
}

bool Auth::ifExist(string fp)
{
    fstream userFile(fp, ios::in);
    if (userFile)
    {
        // cout << "\n\nYou already have an account! LOG IN PLEASE\n"
        //      << endl;
        userFile.close();
        return 1;
    }
    userFile.close();
    return 0;
}

bool Auth::isStrongPassword(const string b)
{
    bool hasUpperCase = false, hasLowerCase = false, hasDigit = false;
    int count = 0;
    for (int i = 0; b[i] != '\0'; i++)
    {
        if (b[i] >= 'A' && b[i] <= 'Z')
            hasUpperCase = true;
        else if (b[i] >= 'a' && b[i] <= 'z')
            hasLowerCase = true;
        else if (b[i] >= '0' && b[i] <= '9')
            hasDigit = true;
        count++;
    }
    return ((count > 7) && (hasUpperCase) && (hasLowerCase) && (hasDigit));
}

void Auth::enc(string &a)
{
    for (int i = 0; a[i] != '\0'; i++)
    {
        if (a[i] >= 'a' && a[i] <= 'z')
            a[i] = (a[i] - 97 + 13) % 26 + 97;
        else if (a[i] >= 'A' && a[i] <= 'Z')
            a[i] = (a[i] - 65 + 13) % 26 + 65;
        else if (a[i] >= '0' && a[i] <= '9')
            a[i] = (a[i] - 48 + 8) % 10 + 48;
    }
}

bool Auth::valiEm(const string a)
{
    bool flag1 = false, flag2 = false;
    for (int i = 0; a[i] != '\0'; i++)
    {
        if (a[i] == '@')
            flag1 = true;
        if (a[i] == '.')
            flag2 = true;
    }
    return flag1 && flag2;
}

bool Auth::passVali(const string a, const string b, const string path)
{
    fstream userFile(path, ios::in);

    if (userFile)
    {
        char name[20], p[25];
        userFile.getline(name, 20, ',');
        userFile.getline(p, 25, ',');
        if (compare(b, p) && compare(a, name))
        {
            userFile.close();
            return true;
        }
        userFile.close();
    }
    return false;
}

//-----------------------Public functions-----------------------
bool Auth::signup()
{
    string fn = "", email = "", pass = "";
    string pathFull = "./users/";
    string extFull = ".txt";

    cin.ignore();
    cout << GREEN << "\nEnter your username : ";
    getline(cin, fn, '\n');

    const string fp = filePath(pathFull, fn, extFull);
    cout << "demo var check : " << fp << endl;

    bool checkName = ifExist(fp);

    if (checkName)
    {
        cout << RED << "\n\n-----------------Please LOG IN!-----------------" << endl;
        return false;
    }

    bool vali;
    do
    {
        cout << cyan << "\nEnter your email (must be a valid email , include @ , include '.' ) : ";
        getline(cin, email, '\n');

        vali = valiEm(email);

        if (!vali)
            cout << RED << "\nenter valid email must contain @ character!\n";
    } while (vali == false);

    do
    {
        cout << cyan << "\nEnter your password (must be atleast 8 characters long , 1 Uc , 1 lc , 1 dig ) : ";
        getline(cin, pass, '\n');

        vali = isStrongPassword(pass);

        if (!vali)
            cout << RED << "\nWeak password ! Please create a strong one add at least 1 UC , 1 LC AND 1 DIG!\n";
    } while (vali == 0);

    fstream o1(fp, ios::out);

    enc(pass);

    if (o1)
    {
        o1 << fn << ',' << pass << ',' << email << endl;
        o1.close();
        cout << BLUE << "\n----------------------Welcome " << fn << " ----------------------" << endl;
    } // helloUser(fn);
    else
    {
        cout << RED << "something went wrong upon creation!" << endl;
        return false;
    }

    return true;
}

bool Auth::login()
{
    string fn = "", passCheck = "", rol = "", pathFull = "./users/", extFull = ".txt";
    cin.ignore();

    cout << cyan << "\n\nEnter your username : ";

    getline(cin, fn, '\n');

    const string fp = filePath(pathFull, fn, extFull);

    bool checkName = ifExist(fp);

    if (!checkName)
    {
        cout << RED << "\n------------------Please MAKE an ACCOUNT FIRST!------------------" << endl;
        return false;
    }

    int count = 0, check = 0;
    do
    {
        cout << cyan << "\nEnter your password : ";
        getline(cin, passCheck, '\n');

        enc(passCheck);

        check = passVali(fn, passCheck, fp);
        if (!check)
        {
            cout << RED << "\n---------------INVALID PASSWORD---------------" << endl;
            cout << RED << "-------------YOU HAVE " << (3 - count - 1) << " ATTEMPTS LEFT---------" << endl;
        }
        count++;
    } while (check == 0 && count < 3);

    if (count >= 3)
    {
        fstream act("./activityLog.txt", ios::app);
        std::time_t now = std::time(nullptr);
        if (act)
            act << "attempt > 3" << "," << fn << ',' << std::ctime(&now);
        else
            cout << RED << "something went wrong!" << endl;
    }

    if (check)
    {
        cout << "\n---------------WELCOME " << fn << " ---------------\n";
    }
    else
    {
        cout << RED << "\nLogin failed! Too many attempts.\n";
        return false;
    }
    return true;
}


//---------------- fall back point ------------------------
// #include "Auth.h"
// using namespace std;

// string Auth::filePath(const string &path, const string &fn, const string &ext) {
//     return path + fn + ext;
// }

// void Auth::enc(string &a)
// {
//     for (int i = 0; a[i] != '\0'; i++) {
//         if (a[i] >= 'a' && a[i] <= 'z')
//             a[i] = (a[i] - 97 + 13) % 26 + 97;
//         else if (a[i] >= 'A' && a[i] <= 'Z')
//             a[i] = (a[i] - 65 + 13) % 26 + 65;
//         else if (a[i] >= '0' && a[i] <= '9')
//             a[i] = (a[i] - 48 + 8) % 10 + 48;
//     }
// }

// bool Auth::signup(const string &user, const string &pass) {
//     string fp = filePath("./users/", user, ".txt");

//     fstream chk(fp, ios::in);
//     if (chk) return false; // already exists

//     string encrypted = pass;
//     enc(encrypted);

//     fstream o(fp, ios::out);
//     if (!o) return false;

//     o << user << "," << encrypted;
//     o.close();
//     return true;
// }

// bool Auth::login(const string &user, const string &pass) {
//     string fp = filePath("./users/", user, ".txt");

//     fstream in(fp, ios::in);
//     if (!in) return false;

//     char uname[50], storedPass[50];
//     in.getline(uname, 50, ',');
//     in.getline(storedPass, 50, ',');

//     string encPass = pass;
//     enc(encPass);

//     return (user == uname && encPass == storedPass);
// }

// //for cli imp
// bool Auth::signupCLI() {
//     string user, pass;
//     cout << "Enter username: ";
//     cin >> user;

//     cout << "Enter password: ";
//     cin >> pass;

//     if (!signup(user, pass)) {   // already exists
//         cout << "User already exists! Please login.\n";
//         return false;
//     }

//     cout << "Signup successful!\n";
//     return true;
// }

// bool Auth::loginCLI() {
//     string user, pass;
//     cout << "Enter username: ";
//     cin >> user;

//     cout << "Enter password: ";
//     cin >> pass;

//     if (!login(user, pass)) {
//         cout << "Login failed!\n";
//         return false;
//     }

//     cout << "Login successful!\n";
//     return true;
// }

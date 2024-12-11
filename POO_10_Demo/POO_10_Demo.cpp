#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>

using namespace std;

enum Server {
    Default = 100, EMEA, APAC, NA, LATAM, None = 999
};

class Character {
    
    const int id = 0;
    char* name = nullptr;
    Server server = (Server)999;
    float gold = 0;
    static float MAX_GOLD;
public:
    static int noCharacters;
    static const char forbiddenCharacters[10];

    Character() : id(Character::noCharacters) {
        cout << "Character - Default Constructor\n";
        this->name = new char[strlen("Default Character") + 1];
        strncpy(this->name, "Default Character", strlen("Default Character") + 1);
        this->gold = 0.99f;
        this->server = Server::Default;
        // this->server = Default; // si aceasta varianta este valida
        Character:noCharacters++;
    }

    //Character(char* name, Server server, float _gold) : id(Character::noCharacters) { // var1
    //    cout << "Character - Arguments Constructor\n";
    //    this->name = new char[strlen(name) + 1];
    //    strncpy(this->name, name, strlen(name) + 1);
    //    this->server = server;
    //    this->gold = _gold;
    //    Character:noCharacters++;
    //}

    Character(char* name, Server server, float _gold) : id(Character::noCharacters) { // var2
        cout << "Character - Arguments Constructor\n";
        this->name = new char[strlen(name) + 1];
        strncpy(this->name, name, strlen(name) + 1);
        this->server = server;
        this->gold = _gold;
    Character:noCharacters++;
    }

    static bool containsForbiddenSymbols(const Character& c, const char forbiddenSymbols[]) {
        for (int i = 0; i < strlen(forbiddenSymbols); i++) {
            if (strchr(c.name, forbiddenSymbols[i])) {
                return true;
            }
        }

        return false;
    }

    char* getName() const {
        return name;
    }

    void setName(const char* _name) {
        if (strlen(_name) >= 3 && containsForbiddenSymbols(*this, Character::forbiddenCharacters) == false) {
            if (this->name != nullptr) {
                delete[] this->name;
                this->name = nullptr;
            }

            this->name = new char[strlen(_name + 1)];
            strcpy_s(this->name, strlen(_name + 1), _name);
        }
        else {
            throw exception("The name is invalid. ( length < 3 or name contains " + string(Character::forbiddenCharacters);
        }
    }

    Server getServer() const { // punem const pentru a garanta ca "this" nu va fi modificat
        return this->server;
    }

    void setServer(const Server server) {
        this->server = server;
    }

    float getGold() const {
        return this->gold;
    }

    void setGold(const float gold) {
        if (gold >= 0 || gold <= Character::MAX_GOLD) {
            this->gold = gold;
        }
    }

    friend ostream& operator<<(ostream& out, const Character& c); //var 1
    
};

ostream& operator<<(ostream& out, const Character& c) { // var 1
    out << "\n\n****** Character " << c.id << " ******\n";

    out << "Character name: " << c.name << endl;
    out << "Character server: ";

    //out << c.server << endl; // e ok

    switch (c.server) { // e elegant
    case Server::Default: out << "Default" << endl; break;
    case Server::EMEA: out << "EMEA" << endl; break;
    case Server::APAC: out << "APAC" << endl; break;
    case Server::NA: out << "NA" << endl; break;
    case Server::LATAM: out << "LATAM" << endl; break;
    case Server::None: out << "None" << endl; break;
    default: out << "Unrecognized server" << endl;
    }

    out << "Character gold: " << c.gold << endl;

    out << "****** Character " << c.id << " ******\n\n";
    return out;
}

int Character::noCharacters = 1;
const char Character::forbiddenCharacters[10] = " &<>%{}/\\";
float Character::MAX_GOLD = 999999999;

int main()
{
    Character c1 = Character(); // default constructor
    cout << c1;

    Character c2; // default constructor
    cout << c2;

    const int noCharacters = 10;

    Character staticCharacters[noCharacters]; // static vector of characters // default constructor
    for (int i = 0; i < noCharacters; i++) {
        cout << staticCharacters[i];
    }

    Character* dynamicCharacters = new Character[noCharacters]; // dynamic vector of characters // default constructor
    for (int i = 0; i < noCharacters; i++) {
        cout << dynamicCharacters[i];
    }


    return 0;
}

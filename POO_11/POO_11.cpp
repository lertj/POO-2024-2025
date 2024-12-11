//#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>

using namespace std;

class Animal {
public:
    string nume = "";
    float masa = 0;

    Animal() {
        cout << "Ctor default animal\n";
    }

    Animal(string _nume, float _masa) {
        cout << "Ctor arg animal\n";
        this->nume = _nume;

        if (_masa < 0) {
            throw invalid_argument("Masa nu poate fi negativa");
        }
        else {
            this->masa = _masa;
        }
    }

    friend ostream& operator<<(ostream& out, const Animal& animal) {
        out << animal.nume << " ";
        out << animal.masa << endl;

        return out;
    }
};

class Mamifer : Animal {
    int nrPui = 0;

public:
    Mamifer() : Animal() {
        cout << "Ctor default Mamifer\n";
    }

    /*Mamifer(int _nrPui, string _nume, float _masa) { // nerecomandat
        this->nrPui = _nrPui;
        this->nume = _nume;
        this->masa = _masa;
    }*/

    Mamifer(int _nrPui, string _nume, float _masa) : Animal(_nume, _masa) {
        this->nrPui = _nrPui;
    }
};

class Zoo {
    char* denumire;
    int nrAnimale;
    Animal* animal;

    int nrGrajduri;
    int nrAnimalePerGrajd;
    Animal** animaleGrajd;


public:

    Zoo() {
        cout << "Ctor default Zoo\n";
    }

    Zoo(char* _denumire, int _nrAnimale, string* numeAnimale, float* masaAnimale){
        this->denumire = new char[strlen(_denumire)+1];

        strcpy(this->denumire, _denumire);

        this->nrAnimale = _nrAnimale;

        this->animal = new Animal[_nrAnimale];

        for (int i = 0; i < _nrAnimale; i++) {
            this->animal[i] = Animal(numeAnimale[i], masaAnimale[i]);
        }

    }

    Zoo(char* _denumire, int _nrGrajduri, int nrAnimalePerGrajd,  string** numeAnimale, float** masaAnimale) {
        this->denumire = new char[strlen(_denumire) + 1];

        strcpy(this->denumire, _denumire);

        this->nrGrajduri = _nrGrajduri;
        this->nrAnimalePerGrajd = nrAnimalePerGrajd;

        this->animaleGrajd = new Animal*[nrGrajduri];
        for (int i = 0; i < this->nrGrajduri; i++) {
            this->animaleGrajd[i] = new Animal[this->nrAnimalePerGrajd];
        }

        for (int i = 0; i < this->nrGrajduri; i++) {
            for (int j = 0; j < this->nrAnimalePerGrajd; j++)
                this->animaleGrajd[i][j] = Animal(numeAnimale[i][j], masaAnimale[i][j]);
        }

    }

    void afisare() {
        cout << this->denumire << endl;
        cout << this->nrAnimale << endl;
        for (int i = 0; i < this->nrAnimale; i++) {
            cout << this->animal[i];
        }
    }

};

int main()
{
    char* denumireZoo = new char[20];
    strcpy(denumireZoo, "Zoo1");
    int nrAnimale = 2;
    string* denumireAnimale = new string[nrAnimale];
    float* masaAnmiale = new float[nrAnimale] {100, 20.5f};
    denumireAnimale[0] = "Leu";
    denumireAnimale[1] = "Pinguin";

    Zoo z1 = Zoo(denumireZoo, nrAnimale, denumireAnimale, masaAnmiale);
    z1.afisare();

    cout << "\n\n\n";

    try {
        Mamifer m(3, "Tigru", -10);
    }
    catch (invalid_argument abcd) {
        Mamifer m(3, "Tigru", 10);
        cout << "Mesaj de eroare: " << abcd.what();
    }


    ifstream inFileTxt("input.txt", ios::in);
    ifstream inFileBin("input.bin", ios::in | ios::binary);

    ofstream outFileTxt("output.txt", ios::out);
    ofstream outFileBin("output.bin", ios::out | ios::binary);
    
    
    return 0;
}


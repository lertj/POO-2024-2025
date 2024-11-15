#include <iostream>

using namespace std;

class Business {

    string denumire;
    char* departament;
    int* salarii;
    int nrAngajati;
    char** numeAngajati;

public:

    static int SALARIU_MINIM;
    static int LUNGIME_NUME_MAX;

    Business(string _denumire, int* _salarii, int _nrAngajati, char* _departament, char** _numeAngajati) : denumire(_denumire) {
        /*this->denumire = _denumire;*/
        if (_salarii != nullptr || _nrAngajati > 0) {
            this->salarii = new int[_nrAngajati];
            for (int i = 0; i < _nrAngajati; i++) {
                if (_salarii[i] >= SALARIU_MINIM) {
                    this->salarii[i] = _salarii[i];
                }
                else {
                    cout << "Salariul de " << _salarii[i] << " lei este prea mic. Acesta va fi modificat la suma minima.\n";
                    this->salarii[i] = SALARIU_MINIM;
                }
            }
            this->nrAngajati = _nrAngajati;
        }
        // neelegant (validare dupa atribuire)
        //if (this->denumire.size() < 3) { 
        //    this->denumire = "invalid"; 
        //}

        if (_departament != nullptr || strlen(_departament) > 3) {
            this->departament = new char[strlen(_departament) + 1];
            strcpy_s(this->departament, strlen(_departament) + 1, _departament);
        }

        if (_numeAngajati != nullptr) {
            this->numeAngajati = new char* [_nrAngajati];
            for (int i = 0; i < _nrAngajati; i++) {
                this->numeAngajati[i] = new char[strlen(_numeAngajati[i]) + 1];
                strcpy_s(this->numeAngajati[i], strlen(_numeAngajati[i]) + 1, _numeAngajati[i]);
            }
        }
    }

    Business(const Business& b) : denumire(b.denumire) {
        /*this->denumire = _denumire;*/
        if (b.salarii != nullptr || b.nrAngajati > 0) {
            this->salarii = new int[b.nrAngajati];
            for (int i = 0; i < b.nrAngajati; i++) {
                if (b.salarii[i] >= SALARIU_MINIM) {
                    this->salarii[i] = b.salarii[i];
                }
                else {
                    cout << "Salariul de " << b.salarii[i] << " lei este prea mic. Acesta va fi modificat la suma minima.\n";
                    this->salarii[i] = SALARIU_MINIM;
                }
            }
            this->nrAngajati = b.nrAngajati;
        }
        // neelegant (validare dupa atribuire)
        //if (this->denumire.size() < 3) { 
        //    this->denumire = "invalid"; 
        //}

        if (b.departament != nullptr || strlen(b.departament) > 3) {
            this->departament = new char[strlen(b.departament) + 1];
            strcpy_s(this->departament, strlen(b.departament) + 1, b.departament);
        }

        if (b.numeAngajati != nullptr) {
            this->numeAngajati = new char* [b.nrAngajati];
            for (int i = 0; i < b.nrAngajati; i++) {
                this->numeAngajati[i] = new char[strlen(b.numeAngajati[i]) + 1];
                strcpy_s(this->numeAngajati[i], strlen(b.numeAngajati[i]) + 1, b.numeAngajati[i]);
            }
        }
    }

    ~Business() {
        cout << "\nApelare destructor\n";
        if(this->departament != nullptr)
            delete[] this->departament;

        if (this->departament != nullptr)
            delete[] this->salarii;

        if (this->numeAngajati != nullptr){

            for (int i = 0; i < this->nrAngajati; i++) {
                delete[] this->numeAngajati[i];
            }
            
            delete[] this->numeAngajati;
        }
    }

    void afisare() {
        cout << "Denumire: " << this->denumire << "\n";
        cout << "Nr angajati: " << this->nrAngajati << endl;
        cout << "Departament: " << this->departament << endl;

        for (int i = 0; i < this->nrAngajati; i++) {
            cout << "Nume: " << this->numeAngajati[i] << " Salariu: " << this->salarii[i] << endl;
        }
    }

    //static void afiseazaSalariulSiNume(const Business& b, int idAngajat); //este posibil

    static void afiseazaSalariulSiNume(const Business& b, int idAngajat) {
        // this nu exista in contextul unei metode statice
        // this->salarii[idAngajat]; // EROARE DE COMPILARE
        if (idAngajat >= 0 && idAngajat < b.nrAngajati) {
            cout << "Nume: " << b.numeAngajati[idAngajat] << endl;
            cout << "Salariu: " << b.salarii[idAngajat] << endl;
        }
    }

    Business& operator=(Business& b) {
        // TO BE IMPLEMENTED
    }

    Business& operator++() { // pre++ // Business* this;
        for (int i = 0; i < this->nrAngajati; i++) {
            this->salarii[i] += 500;
        }

        return *this;
    }

    Business& operator++(int) { // post++ // Business* this;
        Business copie = Business(*this); // creezi copie // copy constructor
        for (int i = 0; i < this->nrAngajati; i++) {
            this->salarii[i] += 500;
        }

        return copie;
    }

    bool operator>(int buget) { // verificam daca suma salariilor este mai mare decat bugetul primit
        int suma = 0;
        for (int i = 0; i < this->nrAngajati; i++) {
            suma += this->salarii[i];
        }

        return suma > buget;
    }

    friend ostream& operator<<(ostream& out, const Business& b);
    friend istream& operator>>(istream& in, Business& b);
};

ostream& operator<<(ostream& out, const Business& b) { // cu inlantuire de operatori istream& // fara inalantuire void
    out << "Denumire: " << b.denumire << "\n";
    out << "Nr angajati: " << b.nrAngajati << endl;
    out << "Departament: " << b.departament << endl;

    for (int i = 0; i < b.nrAngajati; i++) {
        out << "Nume: " << b.numeAngajati[i] << " Salariu: " << b.salarii[i] << endl;
    }

    return out;
}

istream& operator>>(istream& in, Business& b) { // cu inlantuire de operatori istream& // fara inalantuire void
    char buffer[100];
    in >> buffer;

    if (b.departament != nullptr) {
        delete[] b.departament;
    }

    b.departament = new char[strlen(buffer) + 1];
    strcpy_s(b.departament, strlen(buffer) + 1, buffer);

    // + alte variabile

    return in;
}

//void Business::afiseazaSalariulSiNume(const Business& b, int idAngajat) { // este posibil
//    // this nu exista in contextul unei metode statice
//    // this->salarii[idAngajat]; // EROARE DE COMPILARE
//    if (idAngajat >= 0 && idAngajat < b.nrAngajati) {
//        cout << "Nume: " << b.numeAngajati[idAngajat] << endl;
//        cout << "Salariu: " << b.salarii[idAngajat] << endl;
//    }
//}


int Business::LUNGIME_NUME_MAX = 30;
int Business::SALARIU_MINIM = 1000;

int main()
{
    string denumire = "Ceva SRL";
    int nrAngajati = 3;
    int* salarii = new int[3];
    char* departament = new char[10];
    char** numeAngajati = new char* [3];
    for (int i = 0; i < nrAngajati; i++) {
        salarii[i] = i * 1000;
        numeAngajati[i] = new char[Business::LUNGIME_NUME_MAX];
    }

    strcpy_s(departament, strlen("IT") + 1, "IT");
    strcpy_s(numeAngajati[0], strlen("Andrei1") + 1, "Andrei1");
    strcpy_s(numeAngajati[1], strlen("Andrei2") + 1, "Andrei2");
    strcpy_s(numeAngajati[2], strlen("Andrei3") + 1, "Andrei3");

    Business b1(denumire, salarii, nrAngajati, departament, numeAngajati);
    //Business x = b1; // Copy Constructor
    //Business y;
    //y = b1; // operator =
    b1.afisare();
    numeAngajati[0][0] = 'C'; // din primul sir de caractere schimbam primul caracter
    cout << "\n\n";
    b1.afisare();

    ++b1;
    b1++;

    cout << "\n\n";
    b1.afisare();

    cout << "\n\n";
    int buget = 6000;
    cout << "Este bugetul de " << buget << " lei suficient pentru a plati toate salariile angajatilor ? " << ((b1 > buget) ? "NU" : "DA") << endl;
    // linia de deasupra este echivalenta cu ce e dedesubt
    /*if (b1 > buget) {
        cout << "Este bugetul de " << buget << " lei suficient pentru a plati toate salariile angajatilor ? NU\n";
    }
    else {
        cout << "Este bugetul de " << buget << " lei suficient pentru a plati toate salariile angajatilor ? DA\n";
    }*/

    Business::afiseazaSalariulSiNume(b1,0); // varianta corecta si recomandata
    b1.afiseazaSalariulSiNume(b1,0); // varianta permisa, dar nerecomandata

    cout << "\nOperatori:\n" << endl;

    cout << b1 << b1;

    cout << "\n\nCitire:\n";

    cin >> b1;

    cout << b1;
    return 0;
}
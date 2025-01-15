#include <iostream>

using namespace std;

class Printable { // clasa abstracta / interfata - nu poate fi instantiata (linia 107)
public:
    virtual void printInfo() = 0; // pure virtual - specific c++
};

class Persoana : public Printable {
protected:
    string nume;

public:

    Persoana(string _nume) {
        this->nume = _nume;
    }

    Persoana() {
       
    }

    virtual void printInfo() {
        cout << "nume persoana: " << this->nume << endl;
    }

};

class Angajat : public Persoana {
    string companie;

public:

    Angajat(string _companie, string _nume) : Persoana(_nume) {
        this->companie = _companie;
    }

    void printInfo() {
        //cout << "Nume persoana: " << this->nume << endl;
        this->Persoana::printInfo();
        cout << "Companie Angajat: " << this->companie<<endl;
    }
};

class Intern : public Angajat {
public:
    int nrMinOre;

    Intern(int _nrOre, string _companie, string _nume) : Angajat(_companie, _nume) {
        this->nrMinOre = _nrOre;
    }

    void printInfo() { // fara a implementa aceasta metoda avem eroare de compilare din cauza
        //cout << "Nume persoana: " << this->nume << endl;
        this->Angajat::printInfo();
        cout << "Nr min ore Intern: " << this->nrMinOre << endl;
    }

};

class Actor {

};

class Fotbalist : public Persoana, public Actor { // este posibila mostenirea multipla ( dar cu mare atentie )
public:
    Fotbalist(string nume) {
        this->nume = nume;
    }
};
int main()
{
    Persoana p1("Andrei");
    Persoana p2("Andreea");
    Angajat a1("Microsoft", "Bogdan");
    Angajat a2("Amazon", "Laurentiu");
    Intern i1(80, "IBM", "Biciclentiu");

    cout << "p1\n";
    p1.printInfo(); 
    cout << "a1\n";
    a1.printInfo(); // depend on concrete - nu putem inlocui a1 decat cu un alt obiect de acelasi tip - suntem limitati de clasa Angajat

   //  a1 = p1; downcast // NU merge by default
    p1 = a1; // upcast // Merge by default
    cout << "p1 din nou\n";
    p1.printInfo();

    Persoana* persoane[10]; // var1
    //Printable *persoane[10]; // var2
    persoane[0] = &p1;
    persoane[1] = &p2;
    persoane[2] = &a1;
    persoane[3] = &a2;
    persoane[4] = &i1;

    Fotbalist f("Gica"); 
    persoane[5] = &f; // este Persoana -> este Printable -> putem face upcast && poate fi afisata in for-ul de mai jos


    for (int i = 0; i < 6; i++) {
        persoane[i]->printInfo(); // depend on abstract  - la adresa p[i] putem avea ORICE obiect care mosteneste Clasa Persoana/Clasa Abstracta(Interfata) Printable
        // ne bazam pe faptul ca orice clasa care este Persoana / "Printable" poate afisa informatii (concept abstract)
    }

    // Printable printable; // EROARE de compilare

    return 0;
}

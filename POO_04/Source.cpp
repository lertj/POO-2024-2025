#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

struct Card { // exemplu struct
    char* nume;
    string nrTelefon;
    int pFidelitate;
};

union CardSimplu { // exemplu union (grija!!)
    int x;
    long long y;
};

class CardFidelitate { // clasa cu char*
public:
    int noPuncte;
    int* achizitii;
    char* nume;
    string nrTelefon;

    CardFidelitate() {
        // default constructor
        // daca nu avem niciun alt constructor in clasa, compilatorul ne va adauga el un constructor default
        // dar daca ne declaram ORICE alt constructor, cel adaugat de compilator dispare
        cout << "Default constructor" << endl;
    }
    // mare grija la denumirea parametrilor formali din constructor!!!
    CardFidelitate(string _nrTelefon, char* _nume) {
        cout << "Alt constructor" << endl;
        // this este un pointer catre CardFidelitate
        // acest pointer reprezinta obiectul pe care il manipulam/construim
        this->nrTelefon = _nrTelefon;
        this->nume = new char[strlen(_nume) + 1];
        strcpy(this->nume, _nume);
    }

    CardFidelitate(string _nrTelefon, char* _nume, int nrPuncte) :nrTelefon(_nrTelefon), noPuncte(nrPuncte) {
        // :nrTelefon(_nrTelefon) < = > this->nrTelefon = _nrTelefon; // echivalente
        // putem folosi initializarea cu :atribut(valoare) doar daca initializarea directa / atribuirea este ceea ce ne dorim
        cout << "Alt constructor" << endl;
        this->nume = new char[strlen(_nume) + 1];
        strcpy(this->nume, _nume);
    }
};

class CardFideliteSimplu { // echivalentul clasei CardFidelitate, dar cu string
public:
    int noPuncte;
    int* achizitii;
    string nume;
    string nrTelefon;

    // deoarece am declarat un constructor in aceasta clasa, constructorul default creat de compilator nu mai exista

    CardFideliteSimplu(string _nrTelefon, string _nume) :nrTelefon(_nrTelefon), nume(_nume) {
        // :nrTelefon(_nrTelefon) < = > this->nrTelefon = _nrTelefon;
        // :nume(_nume) < = > this->nume = _nume;
        cout << "Alt constructor 2" << endl;
    }
};

Card initCard(int noPuncte, char* nume, string telefon) { // un mod de a initializa o structura folosind o functie
    Card c;
    c.pFidelitate = noPuncte;
    c.nume = new char[strlen(nume) + 1];
    strcpy(c.nume, nume);
    c.nrTelefon = telefon;

    return c;
}

int main()
{
    Card c1;
    c1.pFidelitate = 50;
    //c1.nume = "Robert"; //NU
    c1.nume = new char[100];
    strcpy(c1.nume, "TestNume");
    cout << c1.nume;

    delete[] c1.nume; // in lipsa acestuia avem memory leak

    //string numeTest = "Test"; 
    //Card c2 = initCard(5, numeTest.c_str(), "0722"); // NU ( metoda c_str() returneaza tot un const char => eroare de compilare

    char* numeTest = new char[100]; // buffer / zona de tampon
    // (in cazul de fata nu este necesar, dar este necesar pentru citirea de la tastatura unde nu cunoastem nr de caractere introduse sau alte cazuri similare)
    string telefonTest = "0722222222";
    strcpy(numeTest, "Test");
    Card c2 = initCard(5, numeTest, telefonTest);
    cout <<  endl << c2.nume << " " << c2.nrTelefon;

    cout << endl << endl;


    CardFidelitate cf1; // Constructorul defafult a fost apelat
    cout << endl;

    //cout <<"Nume card: " << cf1.nume << endl << "Nr. puncte: " << cf1.noPuncte; // cf1.nume nu a fost alocat => eroare

    CardFidelitate cf2(telefonTest, numeTest); // Constructorul cu un string

    cout << endl;

    cout << "Nume card: " << cf2.nume << endl << "Nr. telefon : " << cf2.nrTelefon;

    cout << endl << endl;

    // CardFideliteSimplu cfs; // eroare, vezi CardFideliteSimplu linia 56
    CardFideliteSimplu cfs(telefonTest,numeTest); 

    cout << endl;

    cout <<"Nume card: " << cfs.nume << endl << "Nr. telefon: " << cfs.nrTelefon;

    return 0;
}
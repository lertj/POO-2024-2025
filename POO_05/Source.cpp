#include <iostream>

using namespace std;

class Student {
private:

    int* note;
    int nrNote;
    string nume;

public:
    
    string getNume() {
        return this->nume;
    }

    void setNume(string nume) {
        if (nume.size() > 3) {
            this->nume = nume;
        }
    }

    const int* getNote() {
        //return this->note; // NU!!!
        int* copieNote = new int[this->nrNote]; // PASUL 1. ALOCARE


        for (int i = 0; i < this->nrNote; i++) {// PASUL 2. COPIERE
            copieNote[i] = this->note[i]; // deep copy
        }

        return copieNote;

    }

    void setNote(int _nrNote, const int* note) {
        this->nrNote = _nrNote;

        this->note = new int[_nrNote]; // PASUL 1. ALOCARE

        for (int i = 0; i < _nrNote; i++) { // PASUL 2. COPIERE
            this->note[i] = note[i]; // deep copy 
        }
    }

    Student(string _nume, int _nrNote, int* _note) :nume(_nume), nrNote(_nrNote) {

        //this->note = new int[_nrNote];

        //for (int i = 0; i < _nrNote; i++) {
        //  this->note[i] = _note[i]; // deep copy
        //}

        this->setNote(_nrNote, _note); // deoarece avem implementata corect metoda de setNote o putem utiliza in constructor
        // pentru a economisi timp si cod
    }

    Student() {
        cout << endl << "Default constructor" << endl;
    }

    Student(const Student& s) {
        cout << endl << "Copy constructor" << endl;
        this->nume = s.nume;
        this->nrNote = s.nrNote;

        this->setNote(s.nrNote, s.note);
    }

    ~Student() {
        cout << endl << "Destructor!!" << endl;
        delete[] note;
    }

    void afisareStud() {
        cout << endl << "____________ STUDENT ____________" << endl;
        cout << "Nume: " + nume << endl; // + este operator de concatenare intre const char* si string
        //cout << nrNote + nume << endl; // nu exista operator de concatenare direct pentru string si int //NU!!!
        //cout << "Nr note: " + nrNote << endl; // nu este eroare de compilare, dar avem pointer arithmetic => ne va afisa stringul incepand cu pozitia 'nrNote'
        // e.g. nrNote = 3 -> va afisa "note:" ; nrNote = 1 -> va afisa "r note:"
        cout << "Nr note: " << nrNote << endl;

        cout << "Note: " ;
        for (int i = 0; i < nrNote; i++) {
            cout << this->note[i] << ' ';
        }

        cout << endl << "____________ END STUDENT ____________" << endl;


    }
};

int funTest(Student s) { // pentru s se apeleaza copy constructor

    return 0;
}

int main() {
    int nrNote = 3;
    int* note = new int[3] {8, 8, 9};
    Student stud1("Andrei", nrNote, note);
    stud1.afisareStud();

    Student stud2("Marian", nrNote, note);

    note[0] = 1; // nu se va schimba not si in stud1/stud2 deoarece nu avem shallow copy (avem deep copy)

    stud2.afisareStud();

    int* noteFurate = (int*)stud1.getNote(); // castul este demonstrativ pentru const int*
    noteFurate[2] = 0;

    stud1.afisareStud();

    stud1.setNote(nrNote, new int[3] {1, 1, 1});
    stud1.afisareStud();

    { int x = 0; } // un scope
    // x = 1; // NU merge, x e in afara scope ului

    cout << endl;
    Student copieS1(stud1);
    copieS1.setNume("AndreiCopie");
    copieS1.afisareStud();
    cout << endl;
    stud1.afisareStud();

    funTest(stud1); // apel copy Constructor (transmitere prin valoare) + primul destructror

    delete[] note;

    Student* s = new Student(); // apel copy constructor
    delete s; // delete obiect => apel destructor




    return 0; // celelalte 3 apeluri de destructor
}
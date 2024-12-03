#include <iostream>

using namespace std;

//"has a" / composition
//"is a" / inheritance

class Job {
public:
    float salariu;
    string denumire;
    char* descriere = nullptr;
public:
    Job() {
        cout << "Ctor default Job\n";
    }
    Job(float _salariu, string _denumire) :salariu(_salariu), denumire(_denumire) {
        cout << "Ctor arg Job\n";
    }

    Job(float _salariu, string _denumire, char* _descriere) :salariu(_salariu), denumire(_denumire) {
        cout << "Ctor arg descriere Job\n";
        this->descriere = new char[strlen(_descriere) + 1];
        strcpy_s(this->descriere, strlen(_descriere) + 1, _descriere);
    }

    Job(const Job& _job) :salariu(_job.salariu), denumire(_job.denumire) {

        this->descriere = new char[strlen(_job.descriere) + 1];
        strcpy_s(this->descriere, strlen(_job.descriere) + 1, _job.descriere);
        cout << "Copy ctr Job\n";
    }

    void setDenumire(string _denumire) {
        this->denumire = _denumire;
    }

    string getDenumire() {
        return this->denumire;
    }
};

class Angajat {
protected:
    std::string nume; // poate apartine unei clase Persoana, pe care Angajat sa o mosteneasca
    int varsta; // poate apartine unei clase Persoana, pe care Angajat sa o mosteneasca
    string departament;
public:
    Job job;

public:

    Angajat(string _nume, int _varsta, string _departament, string _denumire, float _salariu) : job(_salariu, _denumire), nume(_nume) {
        cout << "Ctor arg Angajat\n";
        this->nume = nume;
        this->varsta = _varsta;
        this->departament = _departament;
    }

    Angajat(const Angajat& angj) : job(angj.job.salariu, angj.job.denumire), nume(angj.nume), varsta(angj.varsta), departament(angj.departament) {
        cout << "Cpy Ctor Angajat\n";
    }

    /*Angajat(string _nume, int _varsta, Job _job): nume(_nume) { // primim job in loc de parametrii pe care i-am fi pus in job
        cout << "Ctor arg Angajat\n";
        this->nume = nume;
        this->varsta = _varsta;
        this->job.setDenumire(_job.getDenumire());
    }*/

    /*Angajat(string _nume, int _varsta, Job job) : job(job.salariu, job.denumire), nume(_nume) { // primim job in loc de parametrii pe care i-am fi pus in job
        cout << "Ctor arg Angajat\n";
        this->nume = nume;
        this->varsta = _varsta;
    }*/

    Angajat(string _nume, int _varsta) {
        // pt job este nevoie de Copy Constructor (al jobului)
        cout << "Ctor arg Angajat fara job\n";
        if (this->nume.size() > 3) {
            this->nume = _nume;
        }
        this->varsta = _varsta;
    }

    Angajat(string _nume, int _varsta, Job _job) : job(_job), nume(_nume) { // copy ctor job
        // pt job este nevoie de Copy Constructor (al jobului)
        cout << "Ctor arg Job Angajat\n";
        this->nume = nume;
        this->varsta = _varsta;
    }

    Angajat() {
        cout << "Ctor default Angajat\n";
    }

};

class Manager : Angajat {
    int persoaneInSubordine;
public:
    Manager() {
        cout << "Ctor default Manager\n";
    }

    Manager(int _persoaneInSubordine, string _nume, int _varsta, float _salariu, string _denumire) : Angajat(_nume, _varsta) {
        this->persoaneInSubordine = _persoaneInSubordine;
        cout << "Ctor arg Manager\n";
    }

    //Manager(string _departament,Angajat angj) : Angajat(angj) { // copy ctor pt angj // var 1
    //    cout << "Manager Ctor cu angj\n";
    //    this->departament = _departament;
    //}

    Manager(int _persoaneInSubordine, const Angajat& angj) : Angajat(angj) { // evitam copy ctor pt angj // var 2
        cout << "Manager Ctor cu angajat\n";
        this->persoaneInSubordine = _persoaneInSubordine;
    }
};


int main()
{
    cout << "*** Angajat a1 ***" << "\n";
    Angajat a1;
    cout << "*** Angajat a1 ***" << "\n\n";


    cout << "*** Angajat a2 ***" << "\n";
    Angajat a2("ion", 33, "IT", "Programator", 3000);
    cout << "*** Angajat a2 ***" << "\n\n";


    char desc[100] = "dezvolta software";
    cout << "*** Job prog ***" << "\n";
    Job prog(3000, "Programator", desc);
    cout << "*** Job prog ***" << "\n\n";

    cout << "*** Angajat a3 ***" << "\n";
    Angajat a3("vasile", 33, prog);
    cout << "*** Angajat a3 ***" << "\n\n";

    cout << "Salariul jobului angajatului3: " << a3.job.salariu << endl << endl;

    cout << "*** Manager m1 ***" << "\n";
    Manager m1;
    cout << "*** Manager m1 ***" << "\n\n";


    cout << "*** Manager m2 ***" << "\n";
    Manager m2(5, "Gigel", 33, 3000, "tester");
    cout << "*** Manager m2 ***" << "\n\n";


    cout << "*** Manager m3 ***" << "\n";
    Manager m3(10, a2);
    cout << "*** Manager m3 ***" << "\n\n";
}
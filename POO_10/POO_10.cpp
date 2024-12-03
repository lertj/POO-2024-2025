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

class Persoana {
protected:
    std::string nume;
    int varsta;

public:
    Job job;
    Persoana(string _nume, int _varsta, string _denumire, float _salariu) : job(_salariu, _denumire), nume(_nume) {
        cout << "Ctor arg Persoana\n";
        this->nume = nume;
        this->varsta = _varsta;
    }

    Persoana(const Persoana& pers) : job(pers.job.salariu, pers.job.denumire), nume(pers.nume) {
        cout << "Cpy Ctor Persoana\n";
    }

    /*Persoana(string _nume, int _varsta, Job _job): nume(_nume) {
        cout << "Ctor arg Persoana\n";
        this->nume = nume;
        this->varsta = _varsta;
        this->job.setDenumire(_job.getDenumire());
    }*/

    /*Persoana(string _nume, int _varsta, Job job) : job(job.salariu, job.denumire), nume(_nume) {
        cout << "Ctor arg Persoana\n";
        this->nume = nume;
        this->varsta = _varsta;
    }*/

    Persoana(string _nume, int _varsta) {
        // pt job este nevoie de Copy Constructor (al jobului)
        cout << "Ctor arg Persoana fara job\n";
        if (this->nume.size() > 3) {
            this->nume = _nume;
        }
        this->varsta = _varsta;
    }

    Persoana(string _nume, int _varsta, Job _job) : job(_job), nume(_nume) {
        // pt job este nevoie de Copy Constructor (al jobului)
        cout << "Ctor arg Job Persoana\n";
        this->nume = nume;
        this->varsta = _varsta;
    }

    Persoana() {
        cout << "Ctor default Persoana\n";
    }

};

class Angajat : Persoana {
    string departament;
public:
    Angajat() {
        cout << "Ctor default Angajat\n";
    }

    Angajat(string _departament, string _nume, int _varsta, float _salariu, string _denumire) : Persoana(_nume, _varsta) {
        this->departament = _departament;
        cout << "Ctor arg Angajat\n";
    }

    //Angajat(string _departament,Persoana pers) : Persoana(pers) { // copy ctor pt pers // var 1
    //    cout << "Anagajat Ctor cu pers\n";
    //    this->departament = _departament;
    //}

    Angajat(string _departament, const Persoana& pers) : Persoana(pers) { // evitam copy ctor pt pers // var 2
        cout << "Anagajat Ctor cu pers\n";
        this->departament = _departament;
    }
};


int main()
{
    cout << "*** Persoana p1 ***" << "\n";
    Persoana p1;
    cout <<"*** Persoana p1 ***" << "\n";


    cout << "*** Persoana p2 ***" << "\n";
    Persoana p2("ion", 33, "Programator", 3000);
    cout << "*** Persoana p2 ***" << "\n\n";


    char desc[100] = "dezvolta software";
    cout << "*** Job prog ***" << "\n";
    Job prog(3000, "Programator", desc);
    cout << "*** Job prog ***" << "\n\n";

    cout << "*** Persoana p3 ***" << "\n";
    Persoana p3("vasile", 33, prog);
    cout << "*** Persoana p3 ***" << "\n\n";

    cout << "Salariul jobului persoanei3: " << p3.job.salariu << endl << endl;

    cout << "*** Angajat a1 ***" << "\n";
    Angajat a1;
    cout << "*** Angajat a1 ***" << "\n\n";


    cout << "*** Angajat a2 ***" << "\n";
    Angajat a2("IT", "Gigel", 33, 3000, "tester");
    cout << "*** Angajat a2 ***" << "\n\n";


    cout << "*** Angajat a3 ***" << "\n";
    Angajat a3("QA", p2);
    cout << "*** Angajat a3 ***" << "\n\n";
}
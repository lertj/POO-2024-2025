#include <iostream>

using namespace std;

class Sejur {
    const int id;
    string destinatie;
    float pretBaza;
    int nrExcursii;
    float* preturiExcursii;
    bool esteValabila;

public:

    Sejur(int _id, string _destinatie, float _pretBaza, int _nrExcursii, float* preturiExcursii, bool _esteValabila) : id(_id), destinatie(_destinatie), pretBaza(_pretBaza), nrExcursii(_nrExcursii), esteValabila(_esteValabila) {

        this->preturiExcursii = new float[nrExcursii];
        for (int i = 0; i < this->nrExcursii; i++) {
            this->preturiExcursii[i] = preturiExcursii[i];
        }
    }
    void afisare()
    {
        cout << this->destinatie << "\n";
        cout << this->pretBaza << "\n";
        cout << this->nrExcursii << "\n";
        for (int i = 0; i < this->nrExcursii; i++)
            cout << this->preturiExcursii[i] << " ";
        cout << "\n";
    }

    Sejur operator+(float x) const { //returnam o COPIE // thhis ramane NEMODIFICAT
        Sejur copie = *this;
        copie.pretBaza += x;

        return copie;
    }

    Sejur& operator--(int) { // post-decrementare
        float* copie = new float[nrExcursii - 1];
        for (int i = 0; i < nrExcursii - 1; i++) {
            copie[i] = this->preturiExcursii[i];
        }
        delete[] preturiExcursii;
        preturiExcursii = copie;
        nrExcursii--;
        return *this;
    }

    bool operator<=(float buget) { // verificam daca bugetul 'buget' este suficient pentru a plati toate excursiile + pretul de baza
        float total = this->pretBaza;
        for (int i = 0; i < nrExcursii; i++) {
            total += this->preturiExcursii[i];
        }

        if (total <= buget) {
            return true; // ne ajunge bugetul
        }
        else {
            return false; // nu ne ajunge bugetul
        }
    }

    Sejur(const Sejur& sej): id(sej.id) {// Prin returnarea unei referinte (Sejur&) evitam (auto)apelarea copy constructorului

        this->destinatie = sej.destinatie;
        this->nrExcursii = sej.nrExcursii;
        this->pretBaza = sej.pretBaza;
        this->esteValabila = sej.esteValabila;


        this->preturiExcursii = new float[sej.nrExcursii];
        for (int i = 0; i < sej.nrExcursii; i++) {
            this->preturiExcursii[i] = sej.preturiExcursii[i];
        }

    }

    Sejur& operator=(const Sejur& sej) {

        this->destinatie = sej.destinatie;
        this->nrExcursii = sej.nrExcursii;
        this->pretBaza = sej.pretBaza;
        this->esteValabila = sej.esteValabila;


        this->preturiExcursii = new float[sej.nrExcursii];
        for (int i = 0; i < sej.nrExcursii; i++) {
            this->preturiExcursii[i] = sej.preturiExcursii[i];
        }

        return *this;
    }

    ~Sejur() {
        if (preturiExcursii != nullptr) {
            delete[] preturiExcursii;
            preturiExcursii = nullptr;
        }
    }

    string getDestinatie() {
        return this->destinatie;
    }

    


    friend ostream& operator<<(ostream& out, const Sejur& s);
};
ostream& operator<<(ostream& out, const Sejur& s)
{
    out << s.destinatie << "\n";
    out << s.pretBaza << "\n";
    out << s.nrExcursii << "\n";
    for (int i = 0; i < s.nrExcursii; i++)
        out << s.preturiExcursii[i] << " ";
    out << "\n";
    return out;
}

Sejur& operator+(float x, Sejur& s) {
    return s + x;
}

int main()
{
    float* excursii = new float[3];

    excursii[0] = 100.5;
    excursii[1] = 200.4;
    excursii[2] = 400.7;

    Sejur s1(1, "Roma", 100, 3, excursii, true);
    //s1.afisare();
    cout << s1;
    cout << s1--;

    float buget = 215.77;
    if (s1 <= buget) {
        cout << endl << "Pentru destinatia " << s1.getDestinatie() << " bugetul este suficient.\n";
    }
    else {
        cout << endl << "Pentru destinatia " << s1.getDestinatie() << " bugetul NU este suficient.\n";
    }

    buget = 915.77;
    if (s1 <= buget) {
        cout << endl << "Pentru destinatia " << s1.getDestinatie() << " bugetul este suficient.\n";
    }
    else {
        cout << endl << "Pentru destinatia " << s1.getDestinatie() << " bugetul NU este suficient.\n";
    }
    
    cout << "s1: " << s1 << endl;
    s1 + 12.5f;
    cout << "s1 nemodificat in continuare: " << s1 << endl;

    s1 = s1 + 110.5f;
    cout << "s1 modificat : " << s1 << endl;

    return 0;
}
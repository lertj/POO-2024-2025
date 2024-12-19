#include <iostream>

using namespace std;

class Jucator;

enum SimbolCarte {
    INIMA_NEAGRA, INIMA_ROSIE, TREFLA, ROMB
};

class Carte {
public:
    int nr;
    SimbolCarte simbol;

    Carte() {

    }
};

Carte* getCarteRandom() {
    Carte* carte = new Carte();

    carte->nr = rand() % 13 + 1;
    carte->simbol = SimbolCarte(rand() % 4);

    return carte;
}

class Playable {
public:
    virtual void adaugaJucator(Jucator* jucator) = 0;
    virtual bool eliminaJucator(string nume) = 0;
    virtual bool joaca1Tura() = 0;
};

class Participant {
public:
    virtual Carte* joaca1Carte(int index) = 0;
    virtual void trage1Carte(Carte* c) = 0;
    virtual int poateJuca1Carte(const Carte* const ultimaCarte) = 0;
};

class Jucator : public Participant  {
    int nrCarti=0;

public:
    string nume;
    Carte* carti;

    Jucator() {

    }

};

class JucatorExpert : public Jucator {
public:
    int nrCampionateCastigate;
    string porecla;
};

class Joc : public Playable {
    int nrJucatori = 0;

public:
    Carte* ultimaCarte = nullptr; // 1 singura carte (NU un vector de carti)
    Participant** jucatori = nullptr; // vector de pointeri catre jucatori (NU matrice de jucatori)
    
    Joc() {

    }
};

int main()
{
    srand(time(0));

    return 0;
}

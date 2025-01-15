#include <iostream>

using namespace std;

class Jucator {
    string name;
public:
    Jucator(string name) {
        this->name = name;
    }

    void virtual printInfo() {
        cout << "Numele Jucatorului: " << this->name << endl;
    }

    operator int() { // operator dummy de cast catre int
        cout << "conversie catre int!" << endl;

        return 0;
    }

    operator void* () {
        cout << "conversie catre void*!"<<endl;

        return this;
    }

    //operator JucatorExpert() { // NU EXISTA // C++ nu permite cast din clasa de Baza catre clasa Derivata (exceptia de la regula va fi discutata in cursul 14)
    //    cout << "conversie!";

    //    return JucatorExpert("","");
    //}

};

class JucatorExpert : public Jucator {
    string nickname;
public:
    JucatorExpert(string nickname, string name) : Jucator(name) {
        this->nickname = nickname;
    }
    void printInfo() {
        cout << "Porecla JucatoruluiExpert este: " << this->nickname << endl;
    }

};

int main() {

    cout << "\ncaz1\n\n";

    Jucator j("jucator1");
    JucatorExpert je("briliantul", "expert1");


    j.printInfo(); // nume
    je.printInfo(); // afiseaza

    // ----------------- 
    cout << "\ncaz2\n\n";
    int noJucatori = 2;
    Jucator* p[2] = { new Jucator("j2"), new JucatorExpert("aproapebriliantul","j2'") }; // static

    Jucator** pDinamic = new Jucator * [noJucatori];
    pDinamic[0] = new Jucator("j2");
    pDinamic[1] = new JucatorExpert("aproapebriliantul", "j2'");
    //dinamic

    p[0]->printInfo();
    p[1]->printInfo();



    // ----------------- 
    cout << "\ncaz3\n\n";
    Jucator* jp = new Jucator("jucator3");
    JucatorExpert* jep = new JucatorExpert("briliantul3", "expert3");

    jp->printInfo();
    jep->printInfo();

    //je = (JucatorExpert)j; // NU este posibil
    //jep = jp; // nu merge
    jep = (JucatorExpert*)jp; // putem face conversie catre un alt tip de pointer // DOWNCAST
    cout << "downcast: ";
    jep->printInfo();
    void* pVoid = (void*)jp; // alt exemplu de conversie a unui pointer catre Jucator la pointer catre void
    void* pVoid2 = (void*)j; // exemplu de conversie a unui Jucator la pointer catre void (cu scop pur demonstrativ)
    int x = j; // cast catre int

    return 0;
}
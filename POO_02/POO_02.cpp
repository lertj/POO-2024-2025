#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using namespace std;

// Transmiterea prin valoare va face "o clona" a parametrilor transmisi
//  => Modificarile asupra paramterilor transmisi prin adresa nu se vor reflecta si in afara functiei
// Pentru a putea incrementa valoarea unei variabile cu aceasta functie vom avea nevoie sa returnam valoarea la finalul functiei
// => nu putem folosi void
int incrementarePrinValoare(int x) {
    x = x + 1;
    return x;
}

// Transmiterea prin adresa a unei variabile duce la modificarea valorii ei si in afara functiei 
// => returnarea valorii este optionala => putem avea o functie void
void incrementarePrinAdresa(int* x) {
    *x = *x + 1;
}

int main()
{
    int x;
    int* ptr = &x;

    cin >> x; //scanf("%d", &x);
    cout << "Valoarea lui x dupa citire este: " << x << endl; //printf("%d", x);

    // x sa devina 0;
    x = 0;
    cout << "Valoarea lui x este: " << x << endl; // x = 0;

    *ptr = 1;
    cout << "Valoarea lui x este: " << x << endl; // x = 1

    incrementarePrinValoare(x);
    cout << "Valoarea lui x dupa apelarea incrementarii prin valoare este: " << x << endl; // x ramane 1

    x = incrementarePrinValoare(x); // pentru a schimba valoarea suntem nevoiti sa asignam valoarea returnata de functie
    cout << "Valoarea lui x dupa asignarea valorii returnate de incrementare prin valoare este: " << x << endl; // x devine 2

    incrementarePrinAdresa(&x);
    cout << "Valoarea lui x dupa incrementare prin adresa este: " << x << endl; // x devine 3


    return 0;
}
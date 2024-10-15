
#define _CRT_SECURE_NO_WARNINGS
// POO3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

/*
Scrieti o functie in C, care sa primeasca urmatorii parametri:
c - un caracter

Functia trebuie sa modifice variabila c primita astfel incat:
daca este o litera din alfabetul roman, sa fie transformata in litera mare
dar daca este o cifra, sa fie incrementata cu o pozitie (dar sa ramana cifra, ex: 1 -> 2, 5->6, 9->0)

La final, functia trebuie sa afiseze caracterul modificat.
Tipul de date returnat de functie este irelevant.

*/

/*
Scrieti o functie in C, care sa primeasca urmatorii parametri:

v - *vector de elemente de tip int
nr - numarul de elemente al vectorului

Functia trebuie sa modifice elementele vectorului astfel:
daca elementul se afla pe o pozitie impara, decrementeaza elementul cu 1
daca elementul se afla pe o pozitie para, incrementeaza elementul cu 3.
La final, functia trebuie sa afiseze vectorul modificat.
Tipul de date returnat de functie este irelevant.*/

// Functie pentru un sir de caractere unde toate caracterele care sunt litere mici sa devina mari


#include <stdio.h>
#include <ctype.h>
#include <iostream>

using namespace std;

void ModiSir(char*& c) { // Task 1.1 folosind functii pentru prelucrare de stringuri)

    int nr = strlen(c);
    for (int i = 0; i < nr; i++) {
        if (isalpha(c[i])) // echivalentul unui if((c[i] >= 'a' && c[i]<='z') || (c[i] >= 'A' && c[i]<='Z'))
            c[i] = toupper(c[i]); // echivbalentul unui c[i] = c[i] + ('a' - 'A') // 'a' - 97 in ASCII 'A' - 65 => minuscula + 32 == majuscula
    }

    cout << c;
}

void modifica(char* c) // Task 1.2
{
    if (isalpha(*c))
        *c = toupper(*c);
    else
        if (isdigit(*c))
        {
            if (*c == '9')*c = '0';
            else *c = *c + 1;
        }
    printf("%c", *c);
}
void modificaVector(int* v, int nr)
{
    for (int i = 0; i < nr; i++)
    {
        if (i % 2 == 0)
            v[i] = v[i] + 3;
        else v[i] = v[i] - 1;
    }
    for (int i = 0; i < nr; i++)
        printf("%d", v[i]);
}

void add1(int x, int y) { //transmitere prin valoare
    x = x + y;
}

void add2(int* x, int y) { //transmitere prin adresa
    *x = *x + y;
}

void add3(int& x, int y) { //transmitere prin referinta
    x = x + y;
}


int main() {

    int x = 2, y = 1;

    cout << "x= " << x << ' ' << "y= " << y << endl;

    add1(x, y);

    cout << "x= " << x << ' ' << "y= " << y << endl;

    add2(&x, y);

    cout << "x= " << x << ' ' << "y= " << y << endl;

    add3(x, y);

    cout << "x= " << x << ' ' << "y= " << y << endl;

    int* v = NULL;
    int nr = 5;

    //v = (int*)malloc(nr * sizeof(int);
    v = new int[nr]; // alocam memorie (dinamic) pentru un vector cu nr elemente 


    //v = new int; // alocam memorie (dinamic) pentru un vector cu 1 element (atentie!!!)
    //v = new int(nr); // * spoiler * alocam memorie (dinamic) pentru un vector cu 1 element, initializat cu valoarea nr
    //v = new int[nr]{1,2,3,4,5} // * spoiler * alocam memorie (dinamic) pentru un vector cu nr elemente, initializat cu valorile 1,2,3,4,5 (nerecomandat)

    //vb[10000] = 0; // NU putem accesa memorie care nu ne este alocata

    cout << "______________" << endl;

    for (int i = 0; i < nr; i++) {
        v[i] = i;
    }

    for (int i = 0; i < nr; i++) {
        cout << v[i] << ' ';
    }

    
    delete[] v; // free(v); // v devine dangling pointer

    cout << endl << "______________" << endl;

    /*for (int i = 0; i < nr; i++) {
        cout << v[i] << ' '; // DANGLING POINTER!! => eroare
    }*/

    cout << endl << "______________" << endl;
    char* c = new char[10];
    strcpy(c, "abcd");
    ModiSir(c);
    return 0;

}



//int main() //pentru task
//{
//    char c;
//   /* scanf_s("%c", &c);
//    modifica(&c);*/
//
//    int nr;
//    scanf("%d", &nr);
//    int v[100];
//    for (int i = 0; i < nr; i++)
//        scanf("%d", &v[i]); // NU combinati citirea cu scanf_s si scanf; folositi doar una dintre cele doua functii
//    modificaVector(v, nr);
//    return 0;
//}
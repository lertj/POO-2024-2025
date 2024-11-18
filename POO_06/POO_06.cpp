#include <iostream>

using namespace std;

class Magazin {

	const int idMagazin;
	string oras;
	char* tara = nullptr; // constructor, getter/setter

public:

	static float procentTVA; // membrul a fost "descris", insa nu are memorie alocata momentan, el trebuie declarat in afara clasei pentru a exista
	string numeMagazin = "";
	int* inventar = NULL;
	int noProduse = 0;

	Magazin() :idMagazin(0) {
		this->procentTVA = 0;
	}

	Magazin(int _idMagazin) :idMagazin(_idMagazin) { // initializarea unui atribut constant se face doar cu initializator
		// this->idMagazin = _idMagazin; // NU
	}

	Magazin(int* _inventar, int _noProduse, char* _tara) :idMagazin(0) {

		if (_tara != nullptr) { // VALIDARE
			this->tara = new char[strlen(_tara) + 1]; // +1 deoarece alocam spatiu si pentru \0  // ALOCARE
			strcpy_s(this->tara, strlen(_tara) + 1, _tara); // +1 deoarece copie si \0  // COPIERE
		} // varianta 1

		// this->setTara(_tara); //  varianta 2

		this->inventar = new int[_noProduse];

		for (int i = 0; i < _noProduse; i++) {
			this->inventar[i] = _inventar[i];
		}

		this->noProduse = _noProduse;
	}

	void setTara(char* _tara) {

		if (this->tara != nullptr) {
			delete this->tara;
		}

		if (_tara != nullptr) {
			this->tara = new char[strlen(_tara) + 1]; // +1 deoarece alocam spatiu si pentru \0
			strcpy_s(this->tara, strlen(_tara) + 1, _tara); // +1 deoarece copie si \0
		}
	}

	char* getTara() {
		char* copie = new char[strlen(this->tara) + 1]; // alocare e
		strcpy_s(copie, strlen(this->tara) + 1, this->tara); // copiere
		return copie; // returnare
	}

	Magazin(const Magazin& m) :idMagazin(m.idMagazin) {
		cout << endl << "***** Apel Copy Constructor *****" << endl;
	}

	// ignorati complet keyword-ul volatile momentan, este folosit in scop pur demonstrativ pentru Copy Constructor
	Magazin(volatile const Magazin& m) :idMagazin(m.idMagazin) {
		cout << endl << "***** Apel Copy Constructor volatile *****" << endl;
	}

	void afisare() {
		cout << "__________________________________\n";
		cout << "Procent TVA: " << Magazin::procentTVA << endl;
		if (this->noProduse > 0) {
			cout << "Nr produse: " << this->noProduse << endl;
			for (int i = 0; i < this->noProduse; i++) {
				cout << this->inventar[i] << ' ';
			}
			cout << endl;
		}
		if (this->tara != nullptr) {
			cout << "Tara: " << this->tara << endl;
		}
		cout << "__________________________________\n";

	}

	static void cresteTVA(float crestere) {
		Magazin::procentTVA += crestere;
		//this->numeMagazin; // NU merge
	}

	// supraincarcare/overloading operator =
	Magazin& operator=(const Magazin& m2) { // obiect1 = obiect2 ; obiect1 - destinatie/this; obiect2 - sursa/m2
		cout << endl << "***** Apel Operator= *****" << endl;
		if (this != &m2) {

			if (m2.inventar != NULL) { // sau if(m2.inventar != nullptr && m2.noProduse != 0)
				if (this->inventar != NULL) {
					delete[] this->inventar;
					this->inventar = nullptr;
				}

				this->inventar = new int[m2.noProduse];
				for (int i = 0; i < m2.noProduse; i++) {
					this->inventar[i] = m2.inventar[i];
				}

				this->noProduse = m2.noProduse;

			}

		}

		return *this;
	}

	~Magazin() {
		cout << "\nApelare Destructor\n";
		if (this->tara != nullptr) {
			delete[] this->tara;
			this->tara = nullptr;
		}
		
	}

	friend Magazin test(Magazin m);
	friend class Mall;
};

class Mall {
	Magazin m; // mai multe detalii despre relatia has a/compunere in seminarul 7

	Mall() { // default constructorul pentru Magazin trebuie sa fie definit in cazul de fata, altfel vom avea erori de compilare in acest constructor din cauza relatiei de has a
		this->m.oras = "Bucuresti"; //desi oras este private, keywordul friend ne permite sa accesam atributele private IN CLASA MALL
	}

};

float Magazin::procentTVA = 0; // necesar pentru ca procentTVA sa existe (trebuie declarat in afara clasei)

// functie dummy folosita pentru demonstrarea apelurilor implicite ale Copy Constructorului
Magazin test(Magazin m) { // apel 1 copy constructor - transmitere prin valoare a lui m
	cout << "Start functie...\n";
	cout << "Pre-initializare...\n";
	// ignorati complet keyword-ul volatile momentan, este folosit in scop pur demonstrativ pentru Copy Constructor
	volatile Magazin nou = m; // apel 2 copy constructor - initializare obiect
	cout << "Post-initializare...\n";

	m.oras = "Bucuresti"; //desi oras este private, keywordul friend ne permite sa accesam atributele private IN FUNCTIA test cu parametrul Magazin m

	return nou; // apel 3 copy constructor - returnare prin valoare
}

Magazin test(int x) { // supraincarcare/overloading functie
	return Magazin(x);
}

//int test(int x) { // nu putem avea supraincarcare/overloading doar prin schimbarea tipului de return
//	return x;
//}

int test(int x, Magazin m) { // supraincarcare/overloading functie
	return x;
}

int main() {


	Magazin m1(1);
	m1.afisare();
	Magazin::procentTVA = 3;
	Magazin m2(2);
	m1.afisare();
	m2.afisare();

	m1.cresteTVA(0.12f);
	m1.afisare();

	cout << "\nPre-apelare functie test...\n";
	test(m1);
	cout << "\nPost-executare functie test...\n";
	Magazin m3;
	m3 = m1; // operator=
	cout << "\nPost-executare operator =...\n";


	// _______________________
	int noProduse = 5;
	int* inventar = new int[noProduse] {1, 2, 3, 4, 5};


	Magazin m4(inventar, noProduse, nullptr);
	m4.afisare();
	m3 = m4;// operator=
	m3.afisare();
	m4.inventar[0] = 0;


	m3.afisare();
	m4.afisare();
	m3 = m2 = m1; // inlantuire de = deoarece returnam obiectul la final // operator= x2


	cout << "\n\n\n_____________________________________________________________________\n\n\n";

	char* tara = new char[15];
	strcpy_s(tara, strlen("Bulgaria")+1, "Bulgaria");
	Magazin nou(inventar, noProduse, tara);
	nou.afisare();
	char* copieTara = (char*)nou.getTara();
	copieTara[0] = 'H';
	cout << endl << copieTara;
	nou.afisare();


	
	{
		Magazin nou(inventar, noProduse, tara);
	}
	cout << "\nAici se termina main\n";


	delete[] inventar;
	delete[] tara;
	delete[] copieTara;
	return 0;
}

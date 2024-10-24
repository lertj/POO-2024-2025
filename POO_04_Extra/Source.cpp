#include <iostream>

using namespace std;

class CardFidelitate {
	public:
		string numeClient;
		char* numeMagazin;
		
		int nrCafelePlict() { // Obtinerea numarului total de "cafele plictisitoare" cumparate in ultimele 10 achizitii
			// 0 2 4 10 0 5 3
			int totalCafelePlict = 0;
			for (int i = this->noAchizitii - 1; i >= this->noAchizitii - 10; i--) {
				totalCafelePlict += this->cafelePlict[i];
			}

			return totalCafelePlict;

		}

		CardFidelitate(string _numeClient, int* _cafelePlict, int _nrAchizitii, string _nrTelefon):numeClient(_numeClient),noAchizitii(_nrAchizitii),nrTelefon(_nrTelefon) {
			/*:NUME_ATRIBUT_DIN_CLASA(VALOARE)
			:numeClient(_numeClient)*/
			//this->cafelePlict = _cafelePlict; // NU // shallow copy NU NU

			this->cafelePlict = new int[_nrAchizitii];
			for (int i = 0; i < _nrAchizitii; i++)
				this->cafelePlict[i] = _cafelePlict[i]; // deep copy // DA
		}

		string getNrTelefon() {
			return this->nrTelefon;
		}

		void setNrTelefon(string _nrTelefon) {
			if (_nrTelefon.size() > 5) {
				this->nrTelefon = _nrTelefon;
			}

		}

		string getNume() {
			return this->numeClient;
		}

		void setNume(string _numeClient) {
			if (_numeClient[0] >= 'A' && _numeClient[0] <= 'Z') {
				this->numeClient = _numeClient;
			}
		}

	private:
		int* cafelePlict;
		int noAchizitii;
		int ID;
		string nrTelefon;

};



int main() {
	int* vectAchizitii = new int[20] {0,3,6,2,5,2,5,1,1,2,5,1,1,1,2,1,5,2,1,0};
	int nrAchizitii = 20;
	

	string numeClient = "Andrei";
	string nrTelefon = "0722";
	string nrTelefonCorect = "072222";
	string nrTelefonGresit = "07";


	CardFidelitate card(numeClient, vectAchizitii, nrAchizitii, nrTelefon);

	cout << "Inainte de modificare: " << card.nrCafelePlict() << endl; // 19

	/*vectAchizitii[19] = 100;


	cout << "Dupa modificare: " <<  card.nrCafelePlict() << endl;*/ // exemplu shallow copy

	cout << "Nr. telefon initial: " << card.getNrTelefon() << endl;

	card.setNrTelefon(nrTelefonGresit);

	cout << "Nr. telefon dupa schimbare eronata: " << card.getNrTelefon() << endl;

	card.setNrTelefon(nrTelefonCorect);

	cout << "Nr. telefon dupa schimbare corecta: " << card.getNrTelefon() << endl;

	string numeGresit = "orlando";
	string numeCorect = "NuOrlando";

	card.setNume(numeGresit);

	cout << "Numele nu s-a schimbat: " << card.getNume() << endl;

	card.setNume(numeCorect);

	cout << "Numele s-a schimbat: " << card.getNume() << endl;

	return 0;
}
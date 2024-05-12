#include <stdio.h>

#include <string.h>

//Dumitru Stefan
//D --- S
struct trupaDansuri{
	int idTrupa;
	int nrDansatori;
	char* denumireTrupa;
};


void citireTrupa(trupaDansuri& trupa) {
	cout << "Introduceti ID-ul trupei: ";
	cin >> trupa.idTrupa;

	cout << "Introduceti numarul de dansatori: ";
	cin >> trupa.nrDansatori;

	// Alocare spațiu pentru denumireTrupa și citirea acesteia de la tastatura
	cout << "Introduceti denumirea trupei: ";
	char buffer[100];
	cin.ignore(); // Ignoră newline-ul lăsat în buffer după citirea numărului de dansatori
	cin.getline(buffer, 100);
	trupa.denumireTrupa = new char[strlen(buffer) + 1];
	strcpy(trupa.denumireTrupa, buffer);
}

void afisareTrupa(struct trupaDansuri trupa) {
	printf("ID Trupa: %d\n", trupa.idTrupa);
	printf("Numar Dansatori: %d\n", trupa.nrDansatori);
	if (trupa.denumireTrupa != NULL)
};

//Realizati o functie care calculeaza ceva pentru un obiect de tipul implementat de voi. 
//(o medie sau o suma, un maxim, un minim...sau orice altceva)

int SumaDansatori(struct trupaDansuri trupe[], int numarTrupe) {
	int suma = 0;
	for (int i = 0; i < numarTrupe; ++i) {
		suma += trupe[i].nrDansatori;
	}
	return suma;
}


//Realizati o functie care modifica pentru un obiect primit ca parametru, un anumit camp.
//noua valoare este primita ca parametru.
void adaugareDansatori(struct trupaDansuri* trupa, int nouNrDansatori) {
	trupa->nrDansatori = nouNrDansatori;
}




void main() {
	trupaDansuri trupa;
	trupa.denumireTrupa = new char[50];
	strcpy(trupa.denumireTrupa, "Trupa de dans CSIE");

	trupa.idTrupa = 1;
	trupa.nrDansatori = 15;

	printf("ID Trupa: ", trupa.idTrupa);
	printf("Numar Dansatori: ", trupa.nrDansatori);
	printf("Denumire Trupa: ", trupa.denumireTrupa);

	struct trupaDansuri trupe[] = {
	   {1, 10, "Trupa A"},
	   {2, 15, "Trupa B"},
	   {3, 8, "Trupa C"}
	};
	int numarTrupe = sizeof(trupe) / sizeof(trupe[0]);

	int sumaDansatori = SumaDansatori(trupe, numarTrupe);
	printf("Suma numarului de dansatori pentru toate trupele: %d\n", sumaDansatori);

	printf("Informatiile initiale despre trupa:\n");
	afisareTrupa(trupa);

	modificareNrDansatori(&trupa, 15);
}
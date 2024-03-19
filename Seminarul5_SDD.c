#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

typedef struct Biblioteca Biblioteca;
typedef struct Nod Nod;

//avem nevoie de o adresa de legatura
//nodul retine un pointer cu adresa noului nod 
//ultimul nod retine null
struct Biblioteca {
	char* nume;
	int nrCarti;
	int nrCititori;
};

//typedef
//ne cream un alias sau o eticjeta pentru 
struct Nod {
	Biblioteca info;
	Nod* next;
};

Biblioteca initializare(const char* nume, int nrCarti, int nrCititori) {
	Biblioteca b;
	b.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy(b.nume, nume);
	b.nrCarti = nrCarti;
	b.nrCititori = nrCititori;
	return b;
}

Nod* inserareInceput(Nod* cap, Biblioteca b) {
	//initializam nodul si alocam spatiu
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	//setam informatia - cand facem cu b. se face deep copy, cu = initializare e deepcopy
	nou->info = initializare(b.nume, b.nrCarti, b.nrCititori);
	nou->next = cap;
	//returnam capul listei
	return nou;

}

void afisareLista(Nod* cap) {
	while (cap != NULL) {
		//procesare
		printf("Biblioteca %s are %d si %d cititori. \n", cap->info.nume, cap->info.nrCarti, cap->info.nrCititori);
		cap = cap->next;
	}
}

char* getBibliotecaNrCartiPerCititor(Nod* cap) {
	float max = 0;
	char* nume_aux = NULL;

	while (cap) {
		if (cap->info.nrCarti / cap->info.nrCititori > max) {
			max = cap->info.nrCarti / cap->info.nrCititori;
			nume_aux = cap->info.nume;
		}
		cap = cap->next;
	}
	char* nume = (char*)malloc(sizeof(char) * (strlen(nume_aux) + 1));
	strcpy(nume, nume_aux);
	return nume;
}

void inserareFinal(Nod** cap, Biblioteca b) {
	Nod* sfarsit = (Nod*)malloc(sizeof(Nod));
	
	sfarsit->info = initializare(b.nume,b.nrCarti,b.nrCititori);
	if ((*cap) != NULL) {
		Nod* capA = (*cap);
		//parcurgearea se face secvential
		while (capA->next !=NULL) {
			capA = capA->next;
			
		}
		capA = capA->next;
	}
	else {
		//derefentiere
		*cap = sfarsit;
	}
	//aplicam divide et impera, ne deplasam pe ultimul nod, cream obiectul nou, nod, si trebuie sa facem legatura intre noul nod
	
}

void stergereLista(Nod** cap) {
	while (*cap != NULL) {
		Nod* temp = *cap;
		*cap = (*cap)->next;
		free(temp->info.nume);
		free(temp);
	}
}

void main() {
	//declaram prima data primul nod
	Nod* cap = NULL;
	Biblioteca b1 = initializare("Mihai Eminescu", 150, 20);
	Biblioteca b2 = initializare("Ioan Slavici", 200, 30);
	Biblioteca b3 = initializare("Tudor Arghezi", 100, 15);
	cap = inserareInceput(cap, b1);
	cap = inserareInceput(cap, b2);
	cap = inserareInceput(cap, b3);

	afisareLista(cap);

	getBibliotecaNrCartiPerCititor(cap);
	Biblioteca b4 = initializare("\nCarturesti", 150, 15);

	inserareFinal(&cap, b4);
	afisareLista(cap);

	stergereLista(&cap);
	afisareLista(cap);

	//

}

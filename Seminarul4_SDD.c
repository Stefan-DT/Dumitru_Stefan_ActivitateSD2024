#define _CRT_SECURE_NO_WARNINGS
#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Aeroport {
	int id;
	char* nume;
	int nrTerminale;
};

struct Aeroport* adaugaAeroport(struct Aeroport* vector, struct Aeroport aeroport, int* dim) {//dim e pointer pt ca o vom modifica 
	struct Aeroport* copie = (struct Aeroport*)malloc(sizeof(struct Aeroport) * ((*dim) + 1));
	copie[(*dim)] = aeroport;
	for (int i = 0; i < (*dim); i++)
	{
		copie[i] = vector[i];
	}

	if (vector != NULL) {
		free(vector);
	}

	(*dim)++;
	return copie;
}

struct Aeroport* citireFisier(const char* numeFisier, int* nrAeroporturi) {
	struct Aeroport* vectorAeroporturi = NULL;
	FILE* f = fopen(numeFisier, "r");
	if (f != NULL) {
		(*nrAeroporturi) = 0;
		char buffer[100];//aloc static pt ca compilatorul dezaloca memoria automat; pot aloca dinamic doar dupa ce citesc, dar am nev de buffer ca sa citesc
		while (fgets(buffer, 99, f) != NULL) {
			struct Aeroport aeroport;
			char delimitator[] = ",\n";//cauta virgula; daca nu o gaseste cauta new line
			char* token = strtok(buffer, delimitator);
			aeroport.id = atoi(token);
			token = strtok(NULL, delimitator);
			aeroport.nume = (char*)malloc(sizeof(char) * (strlen(token) + 1));
			strcpy(aeroport.nume, token);
			token = strtok(NULL, delimitator);
			aeroport.nrTerminale = atoi(token);

			vectorAeroporturi = adaugaAeroport(vectorAeroporturi, aeroport, nrAeroporturi);//la nrAeroporturi nu punem nimic pt ca sunt ambele de tip pointer la int

		}
		fclose(f);
	}
	return vectorAeroporturi;
}

void afisareAeroport(struct Aeroport* aeroport) {
	if (aeroport != NULL) {
		printf("%d. %s are %d terminale\t", aeroport->id, aeroport->nume, aeroport->nrTerminale);
	}
	else {
		printf("NU exista acest aeroport");
	}
}

void afisareVectorAeroporturi(struct Aeroport* aeroporturi, int dim) {
	for (int i = 0; i < dim; i++) {
		afisareAeroport(&aeroporturi[i]);
	}
}

struct Aeroport idCautat(struct Aeroport* aeroporturi, int dim, int idCautat) {
	for (int i = 0; i < dim; i++) {
		if (aeroporturi[i].id == idCautat) {
			return aeroporturi[i];
		}
	}
	struct Aeroport aeroport;
	aeroport.id = -1;
	aeroport.nrTerminale = -1;
	aeroport.nume = NULL;
	return aeroport;
}

void dezalocareVector(struct Aeroport** aeroporturi, int* dim) {
	for (int i = 0; i < (*dim); i++) {
		free((*aeroporturi)[i].nume);
	}

	free(*aeroporturi);
	(*aeroporturi) = NULL;
	(*dim) = NULL;
}


struct Aeroport** citireMatrice(const char* numeFisier, int* nrAeroporturiLinie, int nrClustere, struct Aerport** aeroporturi) {
	FILE* f = fopen(numeFisier, "r");
	if (f != NULL) {
		char buffer[100];//aloc static pt ca compilatorul dezaloca memoria automat; pot aloca dinamic doar dupa ce citesc, dar am nev de buffer ca sa citesc
		while (fgets(buffer, 99, f) != NULL) {
			struct Aeroport aeroport;
			char delimitator[] = ",\n";//cauta virgula; daca nu o gaseste cauta new line
			char* token = strtok(buffer, delimitator);
			aeroport.id = atoi(token);
			token = strtok(NULL, delimitator);
			aeroport.nume = (char*)malloc(sizeof(char) * (strlen(token) + 1));
			strcpy(aeroport.nume, token);
			token = strtok(NULL, delimitator);
			aeroport.nrTerminale = atoi(token);
			int poz = aeroport.nrTerminale % 2;


			aeroporturi[poz] = adaugaAeroport(aeroporturi[poz], aeroport, &(nrAeroporturiLinie[poz]));//la nrAeroporturi nu punem nimic pt ca sunt ambele de tip pointer la int

		}
		fclose(f);
	}
}

void afisareMatrice(struct Aeroport** matrice, int nrClustere, int* nrColoane) {
	for (int i = 0; i < nrClustere; i++)
	{
		for (int j = 0; j < nrColoane[i]; j++)
		{
			afisareAeroport(&matrice[i][j]);
		}
		printf("\n");
	}
}

float mediaTerminale(struct Aeroport** matrice, int* nrAeroporturiLinie, int paritate) {
	paritate = paritate % 2;
	int suma = 0;
	//%2 daca este par, daca restul impartirii este 0
	for (int i = 0; i < nrAeroporturiLinie[paritate]; i++) {

		suma += matrice[paritate][i].nrTerminale;
	}
	if (nrAeroporturiLinie[paritate]) {
		return suma / nrAeroporturiLinie[paritate];
	}


}

void dezalocareMatrice(struct Aeroport*** matrice, int** nrColoane, int* nrClustere) {
	for (int i = 0; i < (*nrClustere); i++) {
		dezalocareVector(&((*matrice)[i]), &((*nrColoane)[i]));
	}
	free(*matrice);
	(*matrice) = NULL;
	free(*nrColoane);
	(*nrColoane) = NULL;
	(*nrClustere) = 0;
}

struct Aeroport* cautareDupaID(struct Aeroport** matrice, int* nrColoane, int nrLinii, int Id) {
	for (int i = 0; i < nrLinii; i++) {
		for (int j = 0; j < nrColoane[i]; j++) {
			if (matrice[i][j].id == Id) {
				return &matrice[i][j];
			}
		}
	}
	return NULL;
}


void main() {
	/*int dimensiune = 3;
	struct Aeroport* aeroporturi = NULL;
	aeroporturi = citireFisier("aeroporturi.txt", &dimensiune);
	afisareVectorAeroporturi(aeroporturi, dimensiune);
	printf("\n");
	dezalocareVector(&aeroporturi, &dimensiune);*/
	//vom salva aeroporturi 


		//MATRICE = VECTOR DE VECTORI - [entru fiecare element am nevoie de un pointer
	struct Aeroport** aeroporturi;
	int nrLinii = 2;//nr clustere in fuctie de numarul de terminale
	int* nrColoane = (int*)malloc((sizeof(int) * nrLinii));

	aeroporturi = (struct Aeroport**)malloc(sizeof(struct Aeroport) * nrLinii);
	//initializare 2 vectori prin for
	//lungimea unui  vector este reprezentata de nrLinii
	for (int i = 0; i < nrLinii; i++) {
		nrColoane[i] = 0;
		aeroporturi[i] = NULL;
	}

	citireMatrice("aeroporturi.txt", nrColoane, nrLinii, aeroporturi);

	afisareMatrice(aeroporturi, nrLinii, nrColoane);

	float medie = mediaTerminale(aeroporturi, nrColoane, 12);
	printf("Media paritate: %.2f", medie);
	printf("\n\n");
	afisareAeroport(cautareDupaID(aeroporturi, nrColoane, nrLinii, 9));

	dezalocareMatrice(&aeroporturi, &nrColoane, &nrLinii);
}

//nrcoloane reprezinta numarul elemente de tip cluster
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

struct Nod {
	int data;
	struct Nod* next;
};

// Functie pentru alocarea unui nou nod
struct Nod* creareNod(int data) {
	struct Nod* nou = (struct Nod*)malloc(sizeof(struct Nod));
	if (nou == NULL) {
		printf("Eroare la alocarea memoriei pentru nod!");
		exit(EXIT_FAILURE);
	}
	nou->data = data;
	nou->next = NULL;
	return nou;
}

// Functie pentru a sterge un nod de pe o pozitie data ca parametru
void stergeNod(struct Nod** cap, int index) {
	if (*cap == NULL)
		return;

	struct Nod* temp = *cap;

	// Daca trebuie sters primul nod
	if (index == 0) {
		*cap = temp->next;
		free(temp);
		return;
	}

	// Gasim nodul anterior celui pe care vrem sa-l stergem
	for (int i = 0; temp != NULL && i < index - 1; i++)
		temp = temp->next;

	// Daca indexul este mai mare decat numarul de noduri in lista, nu se face nimic
	if (temp == NULL || temp->next == NULL)
		return;

	// Stergem nodul de pe pozitia data
	struct Nod* next = temp->next->next;
	free(temp->next);
	temp->next = next;
}

// Functie pentru a insera un nod intr-o lista sortata crescator
void inserareSortata(struct Nod** cap, int data) {
	struct Nod* nou = creareNod(data);
	struct Nod* temp;

	// Daca lista este goala sau primul nod are o valoare mai mare decat data
	if (*cap == NULL || (*cap)->data > data) {
		nou->next = *cap;
		*cap = nou;
	}
	else {
		// Gasim locul corect de inserare
		temp = *cap;
		while (temp->next != NULL && temp->next->data < data)
			temp = temp->next;

		nou->next = temp->next;
		temp->next = nou;
	}
}

// Functie pentru a salva intr-un vector toate obiectele care indeplinesc o anumita conditie
struct Nod** filtrareLista(struct Nod* cap, int conditie, int* dimensiune) {
	*dimensiune = 0;
	struct Nod** rezultat = NULL;
	struct Nod* temp = cap;

	// Calculam numarul de noduri care indeplinesc conditia
	while (temp != NULL) {
		if (temp->data == conditie)
			(*dimensiune)++;
		temp = temp->next;
	}

	// Alocam spatiu pentru vectorul rezultat
	rezultat = (struct Nod**)malloc(sizeof(struct Nod*) * (*dimensiune));
	if (rezultat == NULL) {
		printf("Eroare la alocarea memoriei pentru vectorul rezultat!");
		exit(EXIT_FAILURE);
	}

	// Salvam nodurile care indeplinesc conditia intr-un vector
	temp = cap;
	int index = 0;
	while (temp != NULL) {
		if (temp->data == conditie)
			rezultat[index++] = creareNod(temp->data);
		temp = temp->next;
	}

	return rezultat;
}

// Functie pentru interschimbarea a doua noduri dintr-o lista
void interschimbarePozitii(struct Nod** cap, int pozitie1, int pozitie2) {
	if (pozitie1 == pozitie2)
		return;

	struct Nod* preNod1 = NULL, * preNod2 = NULL;
	struct Nod* nod1 = *cap, * nod2 = *cap;

	// Cautam nodurile de pe pozitiile date
	for (int i = 0; nod1 != NULL && i < pozitie1; i++) {
		preNod1 = nod1;
		nod1 = nod1->next;
	}
	for (int i = 0; nod2 != NULL && i < pozitie2; i++) {
		preNod2 = nod2;
		nod2 = nod2->next;
	}

	// Daca nu gasim nodurile, nu se face nimic
	if (nod1 == NULL || nod2 == NULL)
		return;

	// Daca unul dintre noduri este primul nod
	if (preNod1 != NULL)
		preNod1->next = nod2;
	else
		*cap = nod2;

	if (preNod2 != NULL)
		preNod2->next = nod1;
	else
		*cap = nod1;

	// Schimbam legaturile dintre nodurile vecine
	struct Nod* temp = nod2->next;
	nod2->next = nod1->next;
	nod1->next = temp;
}

// Functie pentru afisarea listei
void afisareLista(struct Nod* cap) {
	struct Nod* temp = cap;
	while (temp != NULL) {
		printf("%d -> ", temp->data);
		temp = temp->next;
	}
	printf("NULL\n");
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


	struct Nod* lista = NULL;

	// 1. Testam functia pentru stergerea unui nod de pe o pozitie data
	inserareSortata(&lista, 10);
	inserareSortata(&lista, 20);
	inserareSortata(&lista, 30);
	inserareSortata(&lista, 40);
	printf("Lista initiala: ");
	afisareLista(lista);
	stergeNod(&lista, 2); // Stergem nodul de pe pozitia 2 (index 1)
	printf("Lista dupa stergerea nodului de pe pozitia 2: ");
	afisareLista(lista);
	printf("\n");

	// 2. Testam functia pentru inserarea unui nod intr-o lista sortata
	inserareSortata(&lista, 25);
	printf("Lista dupa inserarea valorii 25: ");
	afisareLista(lista);
	printf("\n");

	// 3. Testam functia pentru filtrarea listei si salvarea in vector
	int dimensiuneVector;
	struct Nod** rezultat = filtrareLista(lista, 30, &dimensiuneVector); // Filtram nodurile cu valoarea 30
	printf("Nodurile din lista care au valoarea 30 si au fost salvate in vector: ");
	for (int i = 0; i < dimensiuneVector; i++) {
		printf("%d -> ", rezultat[i]->data);
	}
	printf("NULL\n\n");

	// 4. Testam functia pentru interschimbarea a doua noduri din lista
	printf("Lista initiala: ");
	afisareLista(lista);
	interschimbarePozitii(&lista, 1, 3); // Interschimbam nodurile de pe pozitiile 1 si 3 (index 0 si 2)
	printf("Lista dupa interschimbarea nodurilor de pe pozitiile 1 si 3: ");
	afisareLista(lista);
}

//nrcoloane reprezinta numarul elemente de tip cluster
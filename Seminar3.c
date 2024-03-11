#include <stdio.h>
#define _CRT_SECURE_NO_WARNIGNS
#include <malloc.h>

struct Aeroport {
	int id;
	char* nume;
	int nrTerminale;
};

struct Aeroprot* adaugareAeroport(struct Aeroport* vector, struct Aeroport aeroport,int* dimensiune) {
	struct Aeroport* copie = (struct Aeropot*)malloc(sizeof(struct Aeroport) * ((*dimensiune) + 1));
	copie[(*dimensiune)] = aeroport;
	for (int i = 0; i < (*dimensiune); i++) {
		copie[i] = vector[i];	
	}
	
	if (vector) {
		free(vector);
	}
	(*dimensiune)++;
	return copie;


}

struct aeroport* citireFisier(const char* numeFisier, int *nrAeroporturi) {
	struct Aeroport* vectorAeroport;
	vectorAeroport = NULL;
	FILE* f = fopen(numeFisier, "r");




	if (f != NULL){
		(*nrAeroporturi) = 0;
		char buffer[100];
		while (fgets(buffer, 99, f)!=NULL) {
			//trebuie sa o parsam
			//separam elemnetele de pe linie
			struct Aeroport aeroport;
			char delimitator[] = ",\n";
			//o sa caute , sau \n si la \n se opreste 
			//de repetat aici mult 
			char* token = strtok(buffer, delimitator);
			aeroport.id = atoi(token);
			//ce e atoi
			token = strtok(NULL, delimitator);
			aeroport.nume = malloc(sizeof(char) * strlen(token) + 1);
			strcpy(aeroport.nume, token);
			token = strtok(NULL, delimitator);
			aeroport.nrTerminale = atoi(token);


			vectorAeroport = adaugareAeroport(vectorAeroport, aeroport, nrAeroporturi);


		}
		fclose(f);
	}
	//99 pentru ca 1 e terminator de sir
	//f gets returneaza un pointer la char 
	return vectorAeroport;


};

void afisareAeroport(struct Aeroport* aeroport) {
	printf("Aerporotul cu ID: %d cu nume %s si are %d terminale\n", aeroport->id,aeroport->nume, aeroport->nrTerminale);
}

void afisareVectorAeroporturi(struct Aeroport* aeroporturi,int dim) {
	printf("Afisare vector");
	for (int i = 0; i < dim; i++)
	{
		afisareAeroport(&aeroporturi[i]);
	}
}

void dezalocareVector(struct Aeroport** aeroporturi, int* dim) {
	for (int i = 0; i < (*dim); i++)
	{

	}
}


void main() {
	int dimensiune =2 ;
	struct Aeroport* aeroporturi = NULL;
	citireFisier("aeroporturi.txt", &dimensiune);

	afisareVectorAeroporturi(aeroporturi, dimensiune);

	
}
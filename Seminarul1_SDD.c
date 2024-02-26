#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// Structura, un tip de date pentru elementele introduse in aceasta
// Strucutra in C nu avem metode (se fac din afara)

struct Masina {
	char* marca;
	float capacitateCilindrica;
	int an;
};

//char * punem in parametrii ca sa nu mai creeam inca o masina si pentru a nu ocupa memorie pe stiva
void afisareMasina(const struct Masina* m) {
	if (m->marca != NULL) {
		printf("Marca este: %s\n", m->marca);
	}
	printf("Capacitatea cilindrica este: %5.2f\n", m->capacitateCilindrica);
	printf("Anul este: %d\n\n", m->an);
}

struct Masina initializareMasina(const char* marca, int an, float capacitateCilindrica) {
	struct Masina m;
	m.an = an;
	m.capacitateCilindrica = capacitateCilindrica;
	//prima data verificam daca e libera adresa si daca nu alocam memorie
	if (marca != NULL) {
		m.marca = malloc(strlen(marca) + 1);
		strcpy(m.marca, marca);
	}
	else {
		m.marca = malloc(strlen("N/A") + 1);
		strcpy(m.marca, "N/A");
	}
	return m;
}

void dezalocareMasina(struct Masina* masina) {
	free(masina->marca);
	masina->marca = NULL;
}

int main() {
	struct Masina masina1;
	//Dacia
	masina1.marca = (char*)malloc(sizeof(char) * (strlen("Dacia") + 1));
		strcpy(masina1.marca, "Dacia");
	//+1 terminatorul de sir de caractere
	//malloc primeste o dimensiune exprimata in bytes si folosim sizeof(), dupa care primim o adresa 
	// alocam spatiu pentru un vector de caractere
	//pointer la void = pointer generic ca sa se poata mula pe tipul nostru de data 
	//cast implicit-transformi tipul de data la cel dorit
	//cast expliciit --- adica ii pui in fata tipul de data (char*)

	masina1.capacitateCilindrica = 1.9;
	masina1.an = 2023;

	afisareMasina(&masina1);
	dezalocareMasina(&masina1);

	struct Masina masina2 = initializareMasina("Ford",2022,2.49);
	afisareMasina(&masina2);
	dezalocareMasina(&masina2);

	afisareMasina(&masina2);
	//dangling pointer- atunci cand adresa duce la o alta adresa
	return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

//HEAP ARBONE BINAR COMPLET - CARE ESTE REPREZENTAT PRITR UN VECTOR
//ARBORE binar are maxim 2 descendenti
//S - 2*i+1
//D - 2*o+2

typedef struct Mesaje Mesaj;
typedef Heap Heap;

struct Mesaj {
	char* text;
	int prioritate;
};

struct Heap {
	Mesaj* mesaj;
	int dimensiune;
	int dimnesiuneTotala;
};

Mesaj init(const char*, int prioritate) {
	Mesaj m;
	m.text = malloc(sizeof(char) * (1 + strlen(text)));
	strcpy(m.text, text);
	m.prioritate = prioritate;
	return m;
};

Heap initHeap(int dimensiune) {
	Heap h;
	h.vector = malloc(sizeof(Mesaj) + dimensiune);
	h.dimensiune = dimensiune;
	h.dimesiuneTotala = dimensiune;
	return h;

}

void afisareMesaj(Mesaj m) {
	print("Mesajul cu textul %s si prioritatea %d\n", m.text, m.prirotate);
}

void afisareHeap(Heap h) {
	for (int i = 0; i < h.dimensiune; i++)
	{
		afisareMesaj(h.vector[i]);
	}
}

void main() {
	Heap h;
	h = initHeap(6);

	h.vector[0] = init("Salut", 3);
	h.vector[1] = init("BUna", 8);
	h.vector[2] = init("Ceaw", 6);
	h.vector[3] = init("Noroc", 6);
	h.vector[4] = init("Cf", 6);
	h.vector[5] = init("Pa", 6);

	afisareMesaj(h);
	afisareHeap(h);
}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

//Dumitru Stefan
//D --- S

struct trupaDansuri {
    int idTrupa;
    int nrDansatori;
    char* denumireTrupa;
};


// Realizati o functie cu ajutorul careia sa cititi de la tastatura un articol de tipul construit de voi. Funcția returnează obiectul citit.
struct trupaDansuri citesteTrupaDansuri() {
    struct trupaDansuri trupa;
    printf("Introduceti ID-ul trupei: ");
    scanf("%d", &trupa.idTrupa);
    printf("Introduceti numarul de dansatori: ");
    scanf("%d", &trupa.nrDansatori);
    trupa.denumireTrupa = (char*)malloc(100 * sizeof(char));
    printf("Introduceti denumirea trupei: ");
    scanf("%s", trupa.denumireTrupa);
    return trupa;
}

//Realizati o functie care calculeaza ceva pentru un obiect de tipul implementat de voi. (o medie sau o suma, un maxim, un minim...sau orice altceva)
int calculeazaImpartireaDansatorilorPe3Scene(struct trupaDansuri trupa) {
    return trupa.nrDansatori / 3;
}

//Realizati o functie care modifica pentru un obiect primit ca parametru, un anumit camp. noua valoare este primita ca parametru.
void modificaNrDansatori(struct trupaDansuri* trupa, int nouNrDansatori) {
    if (trupa != NULL)
        trupa->nrDansatori = nouNrDansatori;
    else
        printf("Trupa nu exista");
};


//Realizați o funcție care afișează un obiect de tipul creat. Afișarea se face la console, și sunt afișate toate informațiile.
void afiseazaTrupaDansuri(struct trupaDansuri trupa) {
    printf("ID trupa: %d\n", trupa.idTrupa);
    printf("Numar dansatori: %d\n", trupa.nrDansatori);
    printf("Denumire trupa: %s\n", trupa.denumireTrupa);
};

void copiereVector(const char* sursa) {
    char* destinatie = (char*)malloc((strlen(sursa) + 1) * sizeof(char));
    if (destinatie == NULL) {
        printf("Eroare la alocarea memoriei.\n");
        exit(EXIT_FAILURE);
    }
    strcpy(destinatie, sursa);
    return destinatie;
};


//functia de concatenare 
int* concateneazaVectori(int* vector1, int dimensiune1, int* vector2, int dimensiune2) {
    int dimensiuneNoua = dimensiune1 + dimensiune2;

    int* vectorNou = (int*)malloc(dimensiuneNoua * sizeof(int));
    if (vectorNou == NULL) {
        printf("Eroare la alocarea memoriei.\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < dimensiune1; ++i) {
        vectorNou[i] = vector1[i];
    }
    for (int i = 0; i < dimensiune2; ++i) {
        vectorNou[dimensiune1 + i] = vector2[i];
    }

    return vectorNou;
}
//afisare unui vector
void afiseazaVector(struct trupaDansuri* vector, int dimensiune) {
    printf("Vectorul de obiecte este:\n");
    for (int i = 0; i < dimensiune; ++i) {
        printf("Trupa %d:\n", i + 1);
        printf("ID trupa: %d\n", vector[i].idTrupa);
        printf("Numar dansatori: %d\n", vector[i].nrDansatori);
        printf("Denumire trupa: %s\n", vector[i].denumireTrupa);
    }
}

int main(){
    struct trupaDansuri trupa = citesteTrupaDansuri();

    printf("\nTrupa citita:\n");
    afiseazaTrupaDansuri(trupa);

    printf("\nNumarul de dansatori impartit pe 3 scene este: %d\n\n", calculeazaImpartireaDansatorilorPe3Scene(trupa));

    afiseazaTrupaDansuri(trupa);

    modificaNrDansatori(&trupa, trupa.nrDansatori+1);
    printf("\nNumar dansatori modificat:\n");
    afiseazaTrupaDansuri(trupa);


    //vector alocat dinamic cu cel putin 5 obiecte
    int dimensiuneVector = 5;
    struct trupaDansuri* vectorTrupe;

    vectorTrupe = (struct trupaDansuri*)malloc(dimensiuneVector * sizeof(struct trupaDansuri));
    for (int i = 0; i < dimensiuneVector; ++i) {
        printf("\nIntroduceti datele pentru trupa %d:\n", i + 1);
        vectorTrupe[i] = citesteTrupaDansuri();
    }
    printf("\nTrupele introduse sunt:\n");
    for (int i = 0; i < dimensiuneVector; ++i) {
        printf("\nTrupa %d:\n", i + 1);
        printf("ID trupa: %d\n", vectorTrupe[i].idTrupa);
        printf("Numar dansatori: %d\n", vectorTrupe[i].nrDansatori);
        printf("Denumire trupa: %s\n", vectorTrupe[i].denumireTrupa);
    }
    for (int i = 0; i < dimensiuneVector; ++i) {
        free(vectorTrupe[i].denumireTrupa);
    }



    //concatenare
    int vector1[] = { 1, 2, 3 };
    int dimensiune1 = sizeof(vector1) / sizeof(vector1[0]);

    int vector2[] = { 4, 5, 6 };
    int dimensiune2 = sizeof(vector2) / sizeof(vector2[0]);

    int* vectorConcatenat = concateneazaVectori(vector1, dimensiune1, vector2, dimensiune2);

    printf("Noul vector concatenat: ");
    for (int i = 0; i < dimensiune1 + dimensiune2; ++i) {
        printf("%d ", vectorConcatenat[i]);
    }
    printf("\n");


     struct trupaDansuri vectorTrupe1[] = {
       {1, 10, "Trupa 1"},
       {2, 15, "Trupa 2"},
       {3, 20, "Trupa 3"}
    };
    dimensiuneVector = sizeof(vectorTrupe) / sizeof(vectorTrupe[0]);
    afiseazaVector(vectorTrupe, dimensiuneVector);

    free(trupa.denumireTrupa);
    free(vectorTrupe);
    free(vectorConcatenat);


    return 0;
};

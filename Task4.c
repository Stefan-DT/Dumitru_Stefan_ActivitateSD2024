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





//TASK 4

//1. Creati un fisier in care sa aveti minim 10 obiecte de tipul structurii create. Asezarea in fisier a elementelor o faceti la libera alegere.

void scriereFisier(const char* numeFisier) {
    FILE* fisier;
    if ((fisier = fopen(numeFisier, "r")) != NULL) {
        fclose(fisier);
        if (remove(numeFisier) != 0) {
            printf("Eroare la ștergerea fișierului.\n");
        }
        else {
            printf("Fișierul %s a fost sters cu succes.\n", numeFisier);
        }
    }
    else {
        printf("Fisierul %s nu exista.\n", numeFisier);
    }
    fisier = fopen("trupe.txt", "w");
    struct trupaDansuri trupe[] = {
       {1, 5, "Trupa_A"},
       {2, 8, "Trupa_B"},
       {3, 6, "Trupa_C"},
       {4, 10, "Trupa_D"},
       {5, 7, "Trupa_E"},
       {6, 12, "Trupa_F"},
       {7, 9, "Trupa_G"},
       {8, 11, "Trupa_H"},
       {9, 8, "Trupa_I"},
       {10, 6, "Trupa_J"}
    };

    for (int i = 0; i < 10; i++) {
        fprintf(fisier, "%d %d %s\n", trupe[i].idTrupa, trupe[i].nrDansatori, trupe[i].denumireTrupa);
    }

    fclose(fisier); 

    printf("Datele au fost scrise in fisierul trupe.txt.\n");
};


struct trupaDansuri* citesteTrupeDinFisier(const char* numeFisier, int* dimensiuneVector) {
    FILE* fisier;
    struct trupaDansuri* vectorTrupe;

    fisier = fopen(numeFisier, "r");
    if (fisier == NULL) {
        printf("Eroare la deschiderea fisierului.");
        exit(EXIT_FAILURE);
    }

    *dimensiuneVector = 0;

    vectorTrupe = (struct trupaDansuri*)malloc(sizeof(struct trupaDansuri));
    if (vectorTrupe == NULL) {
        printf("Eroare la alocarea memoriei.");
        exit(EXIT_FAILURE);
    }

    while (fscanf(fisier, "%d %d %s", &vectorTrupe[*dimensiuneVector].idTrupa, &vectorTrupe[*dimensiuneVector].nrDansatori, vectorTrupe[*dimensiuneVector].denumireTrupa) != EOF) {
        (*dimensiuneVector)++;
        vectorTrupe = (struct trupaDansuri*)realloc(vectorTrupe, (*dimensiuneVector + 1) * sizeof(struct trupaDansuri));
        if (vectorTrupe == NULL) {
            printf("Eroare la realocarea memoriei.");
            exit(EXIT_FAILURE);
        }
    }

    fclose(fisier);

    return vectorTrupe;
}

int main() {
    /*struct trupaDansuri trupa = citesteTrupaDansuri();

    printf("\nTrupa citita:\n");
    afiseazaTrupaDansuri(trupa);

    printf("\nNumarul de dansatori impartit pe 3 scene este: %d\n\n", calculeazaImpartireaDansatorilorPe3Scene(trupa));

    afiseazaTrupaDansuri(trupa);

    modificaNrDansatori(&trupa, trupa.nrDansatori + 1);
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
    */
    //task 4.1
    scriereFisier("trupe.txt");

    //task4.2
    const char* numeFisier = "trupe.txt";
    int dimensiuneVector;

    struct trupaDansuri* vectorTrupe = citesteTrupeDinFisier(numeFisier, &dimensiuneVector);

    printf("Obiectele citite din fisier sunt:\n");
    for (int i = 0; i < dimensiuneVector; i++) {
        printf("Trupa %d: ID=%d, NrDansatori=%d, Denumire=%s\n", i + 1, vectorTrupe[i].idTrupa, vectorTrupe[i].nrDansatori, vectorTrupe[i].denumireTrupa);
    }

    free(vectorTrupe);



    return 0;
};



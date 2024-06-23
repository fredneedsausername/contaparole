#pragma once

#include "fredalberobinario.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX_WORD_SIZE 127
#define MAX_FILE_NAME_LENGTH 50

FILE* output;

typedef struct {
    char* parola;
    int numOccorrenze;
} contaparole_Parola;

contaparole_Parola* contaparole_crea_parola(char* parola, int numOccorrenze);
int contaparole_funzione_comparazione_parola(const void* parola1, const void* parolaNodo2);
int contaparole_funzione_comparazione_struct(const void* parolaNodo1, const void* parolaNodo2);
int contaparole_funzione_distruzione_contenuto(void* contenuto);
char* contaparole_ottieni_prossima_parola(FILE* input);
int contaparole_conta_parola(alberobinario_NodoBinario* root, char* parola);
void contaparole_aggiungi_parola(alberobinario_NodoBinario* root, char* parola);
void contaparole_funzione_stampa(const void* contenuto);
void contaparole_inizializza_albero(alberobinario_NodoBinario* root, const char* parola);
void contaparole_loop_applicazione();

/* DOCUMENTAZIONE aggiornare return values

// contaparole_Parola * contaparole_crea_parola(char * parola, int numOccorrenze)
    funzione per creare lo struct contaparole_Parola a partire dai dati.

// int contaparole_funzione_comparazione_parola(const void * parola1, const void * parolaNodo2)
    funzione che prende una parola e uno struct contaparole_Parola, e che compara le stringhe parola con strcmp().

// int contaparole_funzione_comparazione_struct(const void * parolaNodo1, const void * parolaNodo2);
    funzione che prende due struct contaparole_Parola, e che compara le stringhe parola con strcmp().

// int contaparole_funzione_distruzione_contenuto(void * contenuto)
    free() il contenuto dello struct contaparole_Parola passato in argomento come puntatore a void, e free() il puntatore contenuto.
    ritorna -1 se contenuto  è uguale a NULL.
    ritorna 0 se la distruzione è andata bene.

// char * contaparole_ottieni_prossima_parola(FILE * input)
    ritorna NULL se ha raggiunto la fine del file.
    ritorna stringa vuota se ha incontrato un simbolo. Ogni singola volta che incontra un simbolo ritorna una stringa vuota.
    altrimenti ritorna la prossima parola nel file.

// int contaparole_conta_parola(alberobinario_NodoBinario * root, char * parola)
    funzione per ricavare il conteggio del numero di apparizioni di una parola.
    ritorna numOccorrenze se la parola è trovata.
    ritorna -1 se non è trovata.

// void contaparole_aggiungi_parola(alberobinario_NodoBinario * root, char * parola)
    aggiunge una parola all'albero binario, se è già presente aggiunge 1 al numero di apparizioni di quella parola.

// void contaparole_funzione_stampa(const void * contenuto);
    stampa tutte le parole lette al file output con relativo conteggio di frequenza.

// void contaparole_loop_applicazione()
    chiamare questa funzione per l'applicazione da terminale implementata con questa libreria.

// void contaparole_inizializza_albero(alberobinario_NodoBinario * root, const char * parola);
    da chiamare la prima volta che si utilizza un albero con questa libreria, pena il segmentation fault immediato quando si prova ad usarlo. parola è la prima parola, nel nodo root, dell'albero.

*/

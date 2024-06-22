
#include "contaparole.h"



contaparole_Parola * contaparole_crea_parola(char * parola, int numOccorrenze) {
    contaparole_Parola * ret = (contaparole_Parola *) malloc (sizeof(contaparole_Parola));
    ret->parola = strdup(parola);
    ret->numOccorrenze = numOccorrenze;
    return ret;
}

int contaparole_funzione_comparazione_parola(const void * parola1, const void * parolaNodo2) {
    const char * pparola1 = (const char *) parola1;
    const char * parola2 = ((contaparole_Parola *) parolaNodo2)->parola;
    return strcmp(pparola1, parola2);
}

int contaparole_funzione_comparazione_struct(const void * parolaNodo1, const void * parolaNodo2) {
    const char * parola1 = ((contaparole_Parola *) parolaNodo1)->parola;
    const char * parola2 = ((contaparole_Parola *) parolaNodo2)->parola;
    return strcmp(parola1, parola2);
}

int contaparole_funzione_distruzione_contenuto(void * contenuto) {
    if(contenuto == NULL) return -1;
    contaparole_Parola * contenuto_struct = (contaparole_Parola *) contenuto;
    free(contenuto_struct->parola);
    free(contenuto);
    return 0;
}

char * contaparole_ottieni_prossima_parola(FILE * input) {
    int buffer;
    char * retVet = (char *) malloc(sizeof(char) * MAX_WORD_SIZE + 1);
    retVet[0] = '\0';
    int index = 0;
    while(1) {
        buffer = fgetc(input);
        if(feof(input)) {
            //se una parola stava venendo costruita, ritornala
            //altrimenti, ritorna NULL
            if(retVet[0] == '\0') return NULL; // nessuna stringa in costruzione
            else {
                char * ret = (char *) malloc((sizeof(char) * index) + 1);
                for(int i = 0; i < index; i++) {
                    ret[i] = retVet[i];
                }   
                ret[index] = '\0';
                free(retVet);
                return ret;
            }
        }
        if(isalnum(buffer)) {
            retVet[index] = (char)buffer;
            index++;
        } else {
            // controllare se i prossimi caratteri sono simboli
            char * ret = (char *) malloc((sizeof(char) * index) + 1);
            for(int i = 0; i < index; i++) {
                ret[i] = retVet[i];
            }
            ret[index] = '\0';
            free(retVet);
            return ret; // se incontra un simbolo, ed ha appena incontrato un simbolo o ha appena iniziato a leggere da un file, ritorna una stringa vuota.
        }
    }
    char * ret = (char *) malloc(sizeof(char) * index + 1);
    for(int i = 0; i < index; i++) {
    ret[i] = retVet[i];
    }
    ret[index] = '\0';
    free(retVet);
    return ret;
}

int contaparole_conta_parola(alberobinario_NodoBinario * root, char * contenuto, alberobinario_pFunzioneComparazione pFComp) { 
    alberobinario_NodoBinario * nodoBinario = alberobinario_contenuto_cerca(root, contenuto, contaparole_funzione_comparazione_parola);
    if(nodoBinario == NULL) return -1;
    return (((contaparole_Parola *)(nodoBinario->contenuto))->numOccorrenze);
}

void contaparole_aggiungi_parola(alberobinario_NodoBinario * root, char * parola) {
    alberobinario_NodoBinario * nodoParolaSeTrovata = alberobinario_contenuto_cerca(root, parola, contaparole_funzione_comparazione_parola);
    if(nodoParolaSeTrovata) {
       ( ( ( (contaparole_Parola *)(nodoParolaSeTrovata->contenuto) ) )->numOccorrenze)++;
    } else {
        alberobinario_nodo_trova_crea(root, contaparole_crea_parola(parola, 1), sizeof(contaparole_Parola), contaparole_funzione_comparazione_struct, contaparole_funzione_distruzione_contenuto);
    }
}

void contaparole_funzione_stampa(const void * contenuto) {
    const contaparole_Parola * pcontenuto = (const contaparole_Parola *) contenuto;
    printf("%s, %i\n", pcontenuto->parola, pcontenuto->numOccorrenze);
}

void contaparole_inizializza_albero(alberobinario_NodoBinario * root, const char * parola) {
    root->contenuto = malloc(sizeof(contaparole_Parola));
    ((contaparole_Parola *)(root->contenuto))->parola = strdup(parola);
    ((contaparole_Parola *)(root->contenuto))->numOccorrenze = 1;
}


void contaparole_loop_applicazione() {
    alberobinario_NodoBinario * root = (alberobinario_NodoBinario *) malloc(sizeof(alberobinario_NodoBinario));
    char nomeFile[MAX_FILE_NAME_LENGTH];
    printf("Nome file: ");
    fgets(nomeFile, sizeof(nomeFile), stdin);
    if(nomeFile[strlen(nomeFile) - 1] == '\n') nomeFile[strlen(nomeFile) - 1] = '\0';
    FILE * input = fopen(nomeFile, "r");
    char * primaParola = contaparole_ottieni_prossima_parola(input);
    contaparole_inizializza_albero(root, primaParola);
    while(1) {
        char * parolaLetta = contaparole_ottieni_prossima_parola(input);
        if(parolaLetta == NULL) break;
        if(parolaLetta[0] == '\0') continue;
        contaparole_aggiungi_parola(root, parolaLetta);
    }
    alberobinario_stampa(root, contaparole_funzione_stampa);
    fclose(input);
    // distruggi l'albero binario a partire dal root.
}








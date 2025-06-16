#include "../include/utilities.h"

char *NomeSeq(char *primeiraLetra){
    int tamanho = strlen(primeiraLetra);
    int i = tamanho - 1;

    while (i >= 0){
        primeiraLetra[i]++;

        if(primeiraLetra[i] <= 'Z') return primeiraLetra;

        primeiraLetra[i] = 'A';
        i--;
    }

    int novoTam = tamanho + 1;
    char *novaLetra = (char *) malloc (novoTam + 1);
    if(novaLetra == NULL) return 0;

    novaLetra[0] = 'A';
    strcpy(novaLetra + 1, primeiraLetra);

    free(primeiraLetra);

    return novaLetra;
}

void embaralharIDs(int *arrayID, int n){
    if(n > 1){
        for (int i = n - 1; i > 0; i--){
            int j = rand() % (i + 1);
            int temp = arrayID[j];
            arrayID[j] = arrayID[i];
            arrayID[i] = temp;
        }
    }
}

void piscinaID(int *IDs, int max_ID){
    int min_ID = 1, faixa_entreID = max_ID - min_ID + 1;

    int *piscina_ids = (int *) malloc (faixa_entreID * sizeof(int));
    if (!piscina_ids) return;

    for (int i = 0; i < faixa_entreID; i++){
        piscina_ids[i] = min_ID + 1;
    }

    embaralharIDs(piscina_ids, faixa_entreID);
}
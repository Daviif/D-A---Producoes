#include "../include/buscas.h"
#include "../include/users.h"
#include "../include/eventos.h"


User *User_buscaSequencial_PorId(FILE *in, int chave, FILE *log){
    rewind(in);
    User *us;
    int cont = 0, encontrar;
    clock_t inicioT = clock();
    while ((us = lerUsuario(in)) != NULL){
        cont++;
        if (us -> id == chave){
            encontrar = 1;
            break;
        }
        free(us);
    }

    if(encontrar == 1){
        fprintf(log, "\nComparacoes Sequencial: %d ", cont);
        clock_t fimT = clock();
        double total = (fimT - inicioT)/CLOCKS_PER_SEC;
        fprintf(log, "\nTempo Sequencial: %f ", total);
        return us;
    }
    else{
        printf("Usuario nao encontrado");
        fprintf(log, "\nComparacoes Sequencial: %d ", cont);
        clock_t fimT = clock();
        double total = (fimT - inicioT)/CLOCKS_PER_SEC;
        fprintf(log, "\nTempo Sequencial: %f ", total);
    }

    return NULL;
}

Evento *Evento_buscaSequencial_PorId(FILE *in, int chave, FILE *log){
    rewind(in);
    Evento *ev; 

    int cont = 0, encontrar;
    clock_t inicioT = clock();

    while ((ev= lerEventos(in)) != NULL){
        if(ev -> id == chave)   {
            encontrar = 1;
            break;
        }
        free(ev);
    }
    if(encontrar == 1){
        fprintf(log, "\nComparacoes Sequencial: %d ", cont);
        clock_t fimT = clock();
        double total = (fimT - inicioT)/CLOCKS_PER_SEC;
        fprintf(log, "\nTempo Sequencial: %f ", total);
        return ev;
    }
    else{
        printf("Usuario nao encontrado");
        fprintf(log, "\nComparacoes Sequencial: %d ", cont);
        clock_t fimT = clock();
        double total = (fimT - inicioT)/CLOCKS_PER_SEC;
        fprintf(log, "\nTempo Sequencial: %f ", total);
    }

    return NULL;
}

Evento *Evento_buscaBinaria_PorId(FILE *in, int chave, int inicio, int fim, FILE *log){
    int cod = -1;
    Evento *ev = NULL;

    int cont;
    clock_t inicioT = clock();

    while(inicio <= fim && cod != chave){
        int meio = inicio + (fim - inicio) / 2;

        fseek(in, meio * tamanho_registroEv(), SEEK_SET);
        ev = lerEventos(in);
        if(ev == NULL) break;

        cod = ev -> id;

        if (cod == chave){
            fprintf(log, "\nComparacoes Binaria: %d ", cont);
            clock_t fimT = clock();
            double total = (fimT - inicioT)/CLOCKS_PER_SEC;
            fprintf(log, "\nTempo Binaria: %f ", total);
            return ev;
        }

        if(cod > chave){
            fim = meio - 1;
        }            
        else{
            inicio = meio + 1;
        }
    }

    if(ev) free(ev);

    return NULL;
}

User *User_buscaBinaria_PorID(FILE *in, int chave, int inicio, int fim, FILE *log){
    int cod = -1;
    User *us = NULL;
    int cont;
    clock_t inicioT;

    while(inicio <= fim){
        int meio = inicio + (fim - inicio) / 2;

        fseek(in, meio * tamanho_registroUs(), SEEK_SET);
        us = lerUsuario(in);
        if(us == NULL) break;

        cod = us->id;

        if (cod == chave){
            fprintf(log, "\nComparacoes Binaria: %d ", cont);
            clock_t fimT = clock();
            double total = (fimT - inicioT)/CLOCKS_PER_SEC;
            fprintf(log, "\nTempo Binaria: %f ", total);
            return us;
        }

        if(cod > chave){
            fim = meio - 1;
        }
        else{
            inicio = meio + 1;
        }
        free(us);
    }

    return NULL;
}
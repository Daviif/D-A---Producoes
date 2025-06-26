#include "../include/buscas.h"
#include "../include/users.h"
#include "../include/eventos.h"


User *User_buscaSequencial_PorId(FILE *in, int chave){
    rewind(in);
    User *us;

    while ((us = lerUsuario(in)) != NULL){
        if (us -> id == chave){
            return us;
        }
        free(us);
    }
    return NULL;
}

Evento *Evento_buscaSequencial_PorId(FILE *in, int chave){
    rewind(in);
    Evento *ev;

    while ((ev= lerEventos(in)) != NULL){
        if(ev -> id == chave)   {
            return ev;
        }
        free(ev);
    }
    return NULL;
    
}

Evento *Evento_buscaBinaria_PorId(FILE *in, int chave, int inicio, int fim){
    int cod = -1;
    Evento *ev = NULL;

    while(inicio <= fim && cod != chave){
        int meio = inicio + (fim - inicio) / 2;

        fseek(in, meio * tamanho_registroEv(), SEEK_SET);
        ev = lerEventos(in);
        if(ev == NULL) break;

        cod = ev -> id;

        if (cod == chave){
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
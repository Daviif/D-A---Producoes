#include "../include/HeapSort.h"

int cont;

int buscarId(RegistroHeap *r){
    if(r -> tipo == TIPO_Evento){
        return r -> dado.evento.id;
    }
    else{
        return r -> dado.user.id;
    }
}

void trocar(RegistroHeap *a, RegistroHeap *b){
    RegistroHeap temp = *a;
    *a = *b;
    *b = temp;
}

void Heapify(RegistroHeap v[], int tam, int i){
    int menor = i;
    int esq = 2 * i + 1;
    int dir = 2 * i + 2;

    if(esq < tam && buscarId(&v[esq]) < buscarId(&v[menor])){
        menor = esq;
    }
    if(esq < tam && buscarId(&v[dir]) < buscarId(&v[menor])){
        menor = dir;
    }

    if(menor != i){
        trocar(&v[i], &v[menor]);
        Heapify(v, tam, menor);
    }
}

void HeapSort(RegistroHeap v[], int tam, FILE *arq_eventos_out, FILE *arq_users_out){
    for(int i = tam / 2 - 1; i >= 0; i--){
        Heapify(v, tam, i);
    }
    for (int i = tam - 1; i > 0; i--){
        trocar(&v[0], &v[i]);
        Heapify(v, i, 0);
    }
    
    for (int i = 0; i < tam; i++) {
        if (v[i].tipo == TIPO_Evento)
            salvarEvento(&v[i].dado.evento, arq_eventos_out);
        else
            salvarUsuario(&v[i].dado.user, arq_users_out);
    }

}
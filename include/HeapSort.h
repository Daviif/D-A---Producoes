#ifndef _HEAP_SORT_
#define _HEAP_SORT_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "eventos.h"
#include "users.h"

typedef enum{
    TIPO_Evento,
    TIPO_User
} TipoR;

typedef struct {
    TipoR tipo;
    union {
        Evento evento;
        User user;
    } dado;
} RegistroHeap;

int buscarId(RegistroHeap *r);

void trocar(RegistroHeap *a, RegistroHeap *b);

void Heapify(RegistroHeap v[], int n, int i);

void HeapSort(RegistroHeap v[], int tam, FILE *arq_eventos_out, FILE *arq_users_out);

#endif
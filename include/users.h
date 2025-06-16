#ifndef USERS_H
#define USERS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef enum {
    Produtor,
    Cliente
} Tipo;

typedef struct{
    int id;
    char nome[100];
    char telefone[11];
    char cpf[11];
    Tipo tipo;
} User;


User CadastrarUsuario(int id, char *nome, char *telefone, char *cpf, Tipo tipo);

#endif
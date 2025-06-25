#ifndef USERS_H
#define USERS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PROD 100
#define MAX_CLI 500000

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


User *CriarUsuario(int id, char *nome, char *telefone, char *cpf, Tipo usuario);

User *lerUsuario(FILE *in);

void salvarUsuario(User *us, FILE *out);

void criarBaseUsuarios(FILE *out, int qtdUser);

void imprimirUser(User *us);

void imprimirBaseUser(FILE *out);

#endif
#ifndef UTILITIES_H
#define UTILITIES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void limpar_tela_ansi();

typedef void (*FuncaoSalvar)(void *dados, FILE *out);

char *NomeSeq(char *primeiraLetra);

void embaralhar(int *array, int n);

void pausarTela();

#endif
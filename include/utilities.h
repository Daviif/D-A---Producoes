#ifndef UTILITIES_H
#define UTILITIES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef void (*FuncaoSalvar)(void *dados, FILE *out);

char *NomeSeq(char *primeiraLetra);

void embaralharIDs(int *arrayID, int n);

void piscinaID(int *IDs, int max_ID);


#endif
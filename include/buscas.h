#ifndef _BUSCAS_H
#define _BUSCAS_H

#include "eventos.h"
#include "users.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

User *User_buscaSequencial_PorId(FILE *in, int chave);

Evento *Evento_buscaSequencial_PorId(FILE *in, int chave);

Evento *buscaBinaria_PorId(FILE *in, int chave, int inicio, int fim);

#endif
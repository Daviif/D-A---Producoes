#ifndef _CARRINHO_H
#define _CARRINHO_H

#include "eventos.h"
#include "users.h"

typedef struct{
    int id;
    Evento idEvento;
    User idCliente;
    int dtCompra;
} Ingresso;

typedef struct{
    int id;
    User idCliente;
    itemCarrinho Itens;
}Carrinho;

typedef struct{
    int id;
    Evento idEvento;
    int qtdIngressos;
}itemCarrinho;



#endif
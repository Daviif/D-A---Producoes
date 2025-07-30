#ifndef EVENTOS_H
#define EVENTOS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>

typedef struct
{
    int id;
    char nome[100];
    char descricao[150];
    int qtdIngresso;
    double valorIngresso;
} Evento;

Evento *criarEvento(int id, char *nome, char *descricao, int qtdIngresso, double valorIngresso);

Evento *lerEventos(FILE *in);

void salvarEvento(Evento *ev, FILE *out);

void criarBaseEventos(FILE *out, int qtdEventos);

void imprimirEvento(Evento *ev);

void imprimirBaseEvento(FILE *out);

int deletarEventoPorId(FILE *out, int idParaDeletar);

// Funções para Seleção por Substituição
 int obterIdEvento(void *reservatorio, int indice);
void lerEventoParaReservatorio(void *reservatorio, int indice, FILE *arqEventos);
void escreverEventoDoReservatorio(void *reservatorio, int indice, FILE *arqSaida);
int selecaoSubstituicao(FILE *arqEventos, int memDisponivel, int totalRegistros, FILE *log);

// Funções para Intercalação Ótima
typedef struct {
    FILE *arquivo;
    Evento registroAtual;
    int ativo;
    char nomeArquivo[100];
} ArquivoEntrada;

int encontrarMenorId(ArquivoEntrada *arquivos, int numArquivos);
int lerProximoRegistro(ArquivoEntrada *arquivo);
int intercalarArquivos(char **nomesArquivos, int numArquivos, char *nomeSaida, FILE *log);
int intercalacaoOtima(char **nomesArquivos, int numArquivos, char *nomeSaida, FILE *log);
int ordenarPorIntercalacaoOtima(FILE *arqEventos, int memDisponivel, int totalRegistros, FILE *log);

#endif
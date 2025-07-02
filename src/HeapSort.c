#include "../include/HeapSort.h"

void lerRegistro(FILE *arq, void *registro, int pos, int tipoRegistro) {
    size_t tamanho = tamanhoRegistro(tipoRegistro);
    fseek(arq, pos * tamanho, SEEK_SET);
    fread(registro, tamanho, 1, arq);
}

void escreverRegistro(FILE *arq, void *registro, int pos, int tipoRegistro) {
    size_t tamanho = tamanhoRegistro(tipoRegistro);
    fseek(arq, pos * tamanho, SEEK_SET);
    fwrite(registro, tamanho, 1, arq);
}

int obterId(void *registro, int tipoRegistro) {
    if (tipoRegistro == TIPO_Evento) {
        return ((Evento *)registro)->id;
    } else {
        return ((User *)registro)->id;
    }
}

void trocarRegistros(FILE *arq, int i, int j, int tipoRegistro) {
    size_t tamanho = tamanhoRegistro(tipoRegistro);
    void *reg_i = malloc(tamanho);
    void *reg_j = malloc(tamanho);

    lerRegistro(arq, reg_i, i, tipoRegistro);
    lerRegistro(arq, reg_j, j, tipoRegistro);

    escreverRegistro(arq, reg_i, j, tipoRegistro);
    escreverRegistro(arq, reg_j, i, tipoRegistro);

    free(reg_i);
    free(reg_j);
}

void heapify(FILE *arq, int n, int i, int tipoRegistro, int *c, int *t) {
    int maior = i;
    int esq = 2 * i + 1;
    int dir = 2 * i + 2;

    size_t tamanho = tamanhoRegistro(tipoRegistro);
    void *reg_maior = malloc(tamanho);
    void *reg_esq = malloc(tamanho);
    void *reg_dir = malloc(tamanho);

    
    lerRegistro(arq, reg_maior, i, tipoRegistro);

    if (esq < n) {
        (*c)++;
        lerRegistro(arq, reg_esq, esq, tipoRegistro);
        if (obterId(reg_esq, tipoRegistro) > obterId(reg_maior, tipoRegistro)) {
            maior = esq;
        }
    }

    if (dir < n) {
        (*c)++;
        lerRegistro(arq, reg_dir, dir, tipoRegistro);

        if (maior == esq) {
            lerRegistro(arq, reg_maior, esq, tipoRegistro);  // Atualiza reg_i
        }
        
        if (obterId(reg_dir, tipoRegistro) > obterId(reg_maior, tipoRegistro)) {
            maior = dir;
        }
    }

    free(reg_maior);
    free(reg_esq);
    free(reg_dir);

    if (maior != i) {
        (*t)++;
        trocarRegistros(arq, i, maior, tipoRegistro);
        heapify(arq, n, maior, tipoRegistro, c, t);
    }
}


void heapSort(FILE *arq, int n, int tipoRegistro, FILE *log) {
    int comparacoes = 0, trocas = 0;
    double tempo_execucao;
    clock_t inicioT = clock();

    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arq, n, i, tipoRegistro, &comparacoes, &trocas);
    }

    for (int i = n - 1; i > 0; i--) {
        trocarRegistros(arq, 0, i, tipoRegistro);
        trocas++;
        heapify(arq, i, 0, tipoRegistro, &comparacoes, &trocas);
    }
    fflush(arq);

    clock_t fimT= clock();
    tempo_execucao = ((double)(fimT - inicioT)) / CLOCKS_PER_SEC;

    fprintf(log, "\nTempo de Execução: %.6f\n", tempo_execucao);
    fprintf(log, "Comparações: %d\n", comparacoes);
    fprintf(log, "Numero de trocas: %d\n", trocas);
    fprintf(log, "------------------------------");
}
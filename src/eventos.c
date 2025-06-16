#include "../include/eventos.h"
#include "../include/utilities.h"

Evento *criarEvento(int id, char *nome, char *descricao, int qtdIngresso, double valorIngresso){
    Evento *ev = (Evento *) malloc (sizeof(Evento));

    if(ev) memset(ev, 0, sizeof(Evento));
    ev -> id = id;

    strncpy(ev -> nome, nome, sizeof(ev -> nome) - 1);
    ev -> nome[sizeof(ev -> nome) - 1] = '\0';
    strncpy(ev -> descricao, descricao, sizeof(ev -> descricao) - 1);
    ev -> nome[sizeof(ev -> descricao) - 1] = '\0';

    ev -> qtdIngresso = qtdIngresso;
    ev -> valorIngresso = valorIngresso;

    return ev;
}

void salvarEvento(Evento *ev, FILE *out){
    fwrite(&ev -> id, sizeof(int), 1, out);
    fwrite(ev -> nome, sizeof(char), sizeof(ev -> nome), out);
    fwrite(ev -> descricao, sizeof(char), sizeof(ev -> descricao), out);
    fwrite(&ev -> qtdIngresso, sizeof(int), 1, out);
    fwrite(&ev -> valorIngresso, sizeof(double), 1, out);
}

Evento *lerEventos(FILE *in){
    Evento *ev = (Evento *) malloc (sizeof(Evento));

    if(!ev) return NULL;
    if (fread(&ev->id, sizeof(int), 1, in) < 1) {
        free(ev);
        return NULL;
    }
    fread(ev->nome, sizeof(char), sizeof(ev->nome), in);
    fread(ev->descricao, sizeof(char), sizeof(ev->descricao), in);
    fread(&ev->qtdIngresso, sizeof(int), 1, in);
    fread(&ev->valorIngresso, sizeof(double), 1, in);
    return ev;

}

void criarBaseEventos(FILE *out, int qtdEventos) {
    Evento *ev;

    char nomeFmt[100];
    char descFmt[256];

    char *letra = (char *)malloc(2);
    if (letra == NULL) {
        perror("Falha na alocação inicial");
        return; // Correção: 'return' sem valor para função void
    }
    strcpy(letra, "A");

    int *piscina_ids = (int *) malloc (qtdEventos * sizeof(int));
    if(!piscina_ids) return;

    for(int i = 0; i < qtdEventos; i++){
        piscina_ids[i] = 1 + i;
    }
    embaralharIDs(piscina_ids, qtdEventos);
    printf("Gerando a base de Eventos...\n");

    for (int i = 0; i < qtdEventos; i++) {
        int idUnico = piscina_ids[i];

        sprintf(nomeFmt, "Evento %s", letra);
        sprintf(descFmt, "Descricao do evento de ID %d", idUnico);
       
        ev = criarEvento(idUnico, nomeFmt, descFmt, 20 + (rand() % 10000),  50.0 + (rand() % 200));
        
        if (ev) {
            salvarEvento(ev, out);
            free(ev); // 
        }

        letra = NomeSeq(letra);
        if (letra == NULL) { 
            perror("Falha ao gerar próxima sequência de nome");
            break;
        }
    }
    
    free(letra);
    free(piscina_ids);
    printf("Base de eventos gerada com sucesso!\n");
}

void imprimirEvento(Evento *ev) {
    if (!ev) return;
    printf("**********************************************");
    printf("\nID do evento: ");
    printf("%d", ev-> id);
    printf("\nNome: ");
    printf("%s", ev -> nome);
    printf("\nDescrição: ");
    printf("%s", ev -> descricao);
    printf("\nQuantidade de Ingressos disponiveis: ");
    printf("%d", ev -> qtdIngresso);
    printf("\nValor do Ingresso: ");
    printf("%.2f", ev-> valorIngresso);
    printf("\n**********************************************");
}

void imprimirBase(FILE *out){
    rewind(out);
    Evento *ev;

    while ((ev = lerEventos(out)) != NULL){
        imprimirEvento(ev);
    }
    free(ev);

    
}
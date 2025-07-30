#include "../include/eventos.h"
#include "../include/utilities.h"

Evento *criarEvento(int id, char *nome, char *descricao, int qtdIngresso, double valorIngresso)
{
    Evento *ev = (Evento *)malloc(sizeof(Evento));

    if (ev)
        memset(ev, 0, sizeof(Evento));
    ev->id = id;

    strncpy(ev->nome, nome, sizeof(ev->nome) - 1);
    ev->nome[sizeof(ev->nome) - 1] = '\0';
    strncpy(ev->descricao, descricao, sizeof(ev->descricao) - 1);
    ev->descricao[sizeof(ev->descricao) - 1] = '\0';

    ev->qtdIngresso = qtdIngresso;
    ev->valorIngresso = valorIngresso;

    return ev;
}

void salvarEvento(Evento *ev, FILE *out)
{
    fwrite(&ev->id, sizeof(int), 1, out);
    fwrite(ev->nome, sizeof(char), sizeof(ev->nome), out);
    fwrite(ev->descricao, sizeof(char), sizeof(ev->descricao), out);
    fwrite(&ev->qtdIngresso, sizeof(int), 1, out);
    fwrite(&ev->valorIngresso, sizeof(double), 1, out);
}

Evento *lerEventos(FILE *in)
{
    Evento *ev = (Evento *)malloc(sizeof(Evento));

    if (!ev)
        return NULL;
    if (fread(&ev->id, sizeof(int), 1, in) < 1)
    {
        free(ev);
        return NULL;
    }
    fread(ev->nome, sizeof(char), sizeof(ev->nome), in);
    fread(ev->descricao, sizeof(char), sizeof(ev->descricao), in);
    fread(&ev->qtdIngresso, sizeof(int), 1, in);
    fread(&ev->valorIngresso, sizeof(double), 1, in);
    return ev;
}

void criarBaseEventos(FILE *out, int qtdEventos)
{
    Evento *ev;

    char nomeFmt[100];
    char descFmt[256];

    char *letra = (char *)malloc(2);
    if (letra == NULL)
    {
        perror("Falha na alocação inicial");
        return; // Correção: 'return' sem valor para função void
    }
    strcpy(letra, "A");

    int *piscina_ids = (int *)malloc(qtdEventos * sizeof(int));
    if (!piscina_ids)
        return;

    for (int i = 0; i < qtdEventos; i++)
    {
        piscina_ids[i] = 1 + i;
    }
    embaralhar(piscina_ids, qtdEventos);
    printf("Gerando a base de Eventos...\n");

    for (int i = 0; i < qtdEventos; i++)
    {
        int idUnico = piscina_ids[i];

        sprintf(nomeFmt, "Evento %s", letra);
        sprintf(descFmt, "Descricao do evento de ID %d", idUnico);

        ev = criarEvento(idUnico, nomeFmt, descFmt, 20 + (rand() % 10000), 50.0 + (rand() % 200));

        if (ev)
        {
            salvarEvento(ev, out);
            free(ev); //
        }

        letra = NomeSeq(letra);
        if (letra == NULL)
        {
            perror("Falha ao gerar próxima sequência de nome");
            break;
        }
    }

    free(letra);
    free(piscina_ids);
    printf("Base de eventos gerada com sucesso!\n");
}

void imprimirEvento(Evento *ev)
{
    if (!ev)
        return;
    printf("**********************************************");
    printf("\nID do evento: ");
    printf("%d", ev->id);
    printf("\nNome: ");
    printf("%s", ev->nome);
    printf("\nDescricao: ");
    printf("%s", ev->descricao);
    printf("\nQuantidade de Ingressos disponiveis: ");
    printf("%d", ev->qtdIngresso);
    printf("\nValor do Ingresso: ");
    printf("%.2f", ev->valorIngresso);
    printf("\n**********************************************");
}

void imprimirBaseEvento(FILE *out)
{
    rewind(out);
    Evento *ev;

    while ((ev = lerEventos(out)) != NULL)
    {
        imprimirEvento(ev);
        free(ev);
    }
}

void *cadastrarEvento(FILE *out, char *nome, char *descricao, int qtdIngresso, double valorIngresso)
{
    Evento *ev;
    int count = 0;

    rewind(out);
    while ((ev = lerEventos(out)) != NULL)
    {
        count++;
    }

    ev = criarEvento(count + 1, nome, descricao, qtdIngresso, valorIngresso);

    if (ev)
    {
        salvarEvento(ev, out);
        free(ev);
    }
}

int deletarEventoPorId(FILE *out, int idParaDeletar)
{
    FILE *temp = tmpfile();
    if (!temp)
    {
        perror("Não foi possível criar o arquivo temporário");
        return 0;
    }

    rewind(out);
    Evento *ev;
    int encontrado = 0;

    while ((ev = lerEventos(out)) != NULL)
    {
        if (ev->id != idParaDeletar)
        {
            salvarEvento(ev, temp);
        }
        else
        {
            encontrado = 1;
        }
        free(ev);
    }

    if (!encontrado)
    {
        fclose(temp);
        return 0;
    }

    freopen(NULL, "wb+", out);
    rewind(temp);
    rewind(out);

    while ((ev = lerEventos(temp)) != NULL)
    {
        salvarEvento(ev, out);
        free(ev);
    }

    fclose(temp);
    return 1;
}

// Funções auxiliares para Seleção por Substituiçã
int obterIdEvento(void *reservatorio, int indice) {
    Evento *eventos = (Evento*)reservatorio;
    return eventos[indice].id;
}

void lerEventoParaReservatorio(void *reservatorio, int indice, FILE *arqEventos) {
    Evento *eventos = (Evento*)reservatorio;
    Evento *ev = lerEventos(arqEventos);
    if (ev) {
        eventos[indice] = *ev;
        free(ev);
    }
}

void escreverEventoDoReservatorio(void *reservatorio, int indice, FILE *arqSaida) {
    Evento *eventos = (Evento*)reservatorio;
    salvarEvento(&eventos[indice], arqSaida);
}

int selecaoSubstituicao(FILE *arqEventos, int memDisponivel, int totalRegistros, FILE *log) {
    clock_t inicioT = clock();
    long comparacoes = 0;
    
    int tamReg = tamanho_registroEv();
    
    // Aloca o reservatório (heap) com a memória disponível
    Evento *reservatorio = malloc(memDisponivel * sizeof(Evento));
    int *congelado = calloc(memDisponivel, sizeof(int));
    
    if (!reservatorio || !congelado) {
        fprintf(stderr, "Erro ao alocar memória.\n");
        return -1;
    }
    
    rewind(arqEventos);
    
    int numRuns = 0;
    int registrosProcessados = 0;
    
    // Carrega inicialmente o reservatório
    int registrosLidos = 0;
    for (int i = 0; i < memDisponivel && registrosLidos < totalRegistros; i++) {
        Evento *ev = lerEventos(arqEventos);
        if (ev) {
            reservatorio[i] = *ev;
            free(ev);
            registrosLidos++;
        } else {
            congelado[i] = 1; // Marca como congelado se não conseguiu ler
        }
    }
    
    while (registrosProcessados < totalRegistros) {
        numRuns++;
        char nomeParticao[100];
        sprintf(nomeParticao, "run_eventos_%d.dat", numRuns - 1);
        
        FILE *arqSaida = fopen(nomeParticao, "wb");
        if (!arqSaida) {
            fprintf(stderr, "Erro ao criar partição %s.\n", nomeParticao);
            free(reservatorio);
            free(congelado);
            return -1;
        }
        
        int ultimoId = -1;
        int registrosAtivos = 0;
        
        // Conta registros ativos (não congelados)
        for (int i = 0; i < memDisponivel; i++) {
            if (!congelado[i]) {
                registrosAtivos++;
            }
        }
        
        // Processa a corrida atual
        while (registrosAtivos > 0) {
            int minIndice = -1;
            int minId = INT_MAX;
            
            // Encontra o menor ID entre os registros ativos
            for (int i = 0; i < memDisponivel; i++) {
                if (!congelado[i]) {
                    comparacoes++;
                    if (reservatorio[i].id < minId) {
                        minId = reservatorio[i].id;
                        minIndice = i;
                    }
                }
            }
            
            if (minIndice == -1) {
                break; // Não há mais registros ativos
            }
            
            // Escreve o registro com menor ID
            salvarEvento(&reservatorio[minIndice], arqSaida);
            ultimoId = reservatorio[minIndice].id;
            registrosProcessados++;
            
            // Tenta ler um novo registro
            if (registrosLidos < totalRegistros) {
                Evento *novoEv = lerEventos(arqEventos);
                if (novoEv) {
                    reservatorio[minIndice] = *novoEv;
                    free(novoEv);
                    registrosLidos++;
                    
                    // Verifica se o novo registro deve ser congelado
                    if (reservatorio[minIndice].id < ultimoId) {
                        congelado[minIndice] = 1;
                        registrosAtivos--;
                    }
                } else {
                    // Não há mais registros para ler
                    congelado[minIndice] = 1;
                    registrosAtivos--;
                }
            } else {
                // Não há mais registros para ler
                congelado[minIndice] = 1;
                registrosAtivos--;
            }
        }
        
        fclose(arqSaida);
        
        // Reseta os congelados para a próxima corrida
        for (int i = 0; i < memDisponivel; i++) {
            congelado[i] = 0;
        }
        
        // Recarrega o reservatório se ainda há registros para processar
        if (registrosProcessados < totalRegistros) {
            for (int i = 0; i < memDisponivel && registrosLidos < totalRegistros; i++) {
                Evento *ev = lerEventos(arqEventos);
                if (ev) {
                    reservatorio[i] = *ev;
                    free(ev);
                    registrosLidos++;
                } else {
                    congelado[i] = 1;
                }
            }
        }
    }
    
    free(reservatorio);
    free(congelado);
    
    clock_t fimT = clock();
    double tempo_execucao = ((double)(fimT - inicioT)) / CLOCKS_PER_SEC;
    
    fprintf(log, "\n------------------------------\n");
    fprintf(log, "Algoritmo: Seleção com Substituição (Corridas de Eventos)\n");
    fprintf(log, "Tempo de Execução: %.6f segundos\n", tempo_execucao);
    fprintf(log, "Comparações: %ld\n", comparacoes);
    fprintf(log, "Número de corridas geradas: %d\n", numRuns);
    fprintf(log, "Arquivos gerados: run_eventos_0.dat, ...\n");
    fprintf(log, "------------------------------\n");
    
    printf("\nCriação de corridas finalizada. %d corridas foram geradas.\n", numRuns);
    
    return numRuns;
}



// Função para encontrar o menor ID entre os arquivos ativos
int encontrarMenorId(ArquivoEntrada *arquivos, int numArquivos) {
    int menorIndice = -1;
    int menorId = INT_MAX;
    
    for (int i = 0; i < numArquivos; i++) {
        if (arquivos[i].ativo && arquivos[i].registroAtual.id < menorId) {
            menorId = arquivos[i].registroAtual.id;
            menorIndice = i;
        }
    }
    
    return menorIndice;
}

// Função para ler próximo registro de um arquivo
int lerProximoRegistro(ArquivoEntrada *arquivo) {
    Evento *ev = lerEventos(arquivo->arquivo);
    if (ev) {
        arquivo->registroAtual = *ev;
        free(ev);
        return 1;
    } else {
        arquivo->ativo = 0;
        return 0;
    }
}

// Função para intercalar múltiplos arquivos ordenados
int intercalarArquivos(char **nomesArquivos, int numArquivos, char *nomeSaida, FILE *log) {
    clock_t inicioT = clock();
    long comparacoes = 0;
    
    ArquivoEntrada *arquivos = malloc(numArquivos * sizeof(ArquivoEntrada));
    if (!arquivos) {
        fprintf(stderr, "Erro ao alocar memória para arquivos.\n");
        return -1;
    }
    
    // Abre todos os arquivos de entrada
    for (int i = 0; i < numArquivos; i++) {
        arquivos[i].arquivo = fopen(nomesArquivos[i], "rb");
        if (!arquivos[i].arquivo) {
            fprintf(stderr, "Erro ao abrir arquivo %s.\n", nomesArquivos[i]);
            for (int j = 0; j < i; j++) {
                fclose(arquivos[j].arquivo);
            }
            free(arquivos);
            return -1;
        }
        strcpy(arquivos[i].nomeArquivo, nomesArquivos[i]);
        arquivos[i].ativo = 1;
        
        // Lê o primeiro registro de cada arquivo
        if (!lerProximoRegistro(&arquivos[i])) {
            arquivos[i].ativo = 0;
        }
    }
    
    // Abre arquivo de saída
    FILE *arquivoSaida = fopen(nomeSaida, "wb");
    if (!arquivoSaida) {
        fprintf(stderr, "Erro ao criar arquivo de saída %s.\n", nomeSaida);
        for (int i = 0; i < numArquivos; i++) {
            fclose(arquivos[i].arquivo);
        }
        free(arquivos);
        return -1;
    }
    
    int registrosEscritos = 0;
    
    // Intercala os registros
    while (1) {
        int menorIndice = encontrarMenorId(arquivos, numArquivos);
        
        if (menorIndice == -1) {
            break; // Todos os arquivos foram processados
        }
        
        // Escreve o registro com menor ID
        salvarEvento(&arquivos[menorIndice].registroAtual, arquivoSaida);
        registrosEscritos++;
        comparacoes++;
        
        // Lê próximo registro do arquivo que foi usado
        lerProximoRegistro(&arquivos[menorIndice]);
    }
    
    // Fecha todos os arquivos
    for (int i = 0; i < numArquivos; i++) {
        fclose(arquivos[i].arquivo);
    }
    fclose(arquivoSaida);
    free(arquivos);
    
    clock_t fimT = clock();
    double tempo_execucao = ((double)(fimT - inicioT)) / CLOCKS_PER_SEC;
    
    fprintf(log, "\n------------------------------\n");
    fprintf(log, "Algoritmo: Intercalação Ótima (Eventos)\n");
    fprintf(log, "Tempo de Execução: %.6f segundos\n", tempo_execucao);
    fprintf(log, "Comparações: %ld\n", comparacoes);
    fprintf(log, "Registros escritos: %d\n", registrosEscritos);
    fprintf(log, "Arquivo de saída: %s\n", nomeSaida);
    fprintf(log, "------------------------------\n");
    
    return registrosEscritos;
}

// Função principal de Intercalação Ótima
int intercalacaoOtima(char **nomesArquivos, int numArquivos, char *nomeSaida, FILE *log) {
    if (numArquivos <= 0) {
        fprintf(stderr, "Número inválido de arquivos para intercalar.\n");
        return -1;
    }
    
    if (numArquivos == 1) {
        // Se há apenas um arquivo, apenas copia
        FILE *origem = fopen(nomesArquivos[0], "rb");
        FILE *destino = fopen(nomeSaida, "wb");
        
        if (!origem || !destino) {
            fprintf(stderr, "Erro ao copiar arquivo único.\n");
            if (origem) fclose(origem);
            if (destino) fclose(destino);
            return -1;
        }
        
        Evento *ev;
        int registrosCopiados = 0;
        while ((ev = lerEventos(origem)) != NULL) {
            salvarEvento(ev, destino);
            free(ev);
            registrosCopiados++;
        }
        
        fclose(origem);
        fclose(destino);
        
        fprintf(log, "\n------------------------------\n");
        fprintf(log, "Algoritmo: Intercalação Ótima (Cópia Simples)\n");
        fprintf(log, "Registros copiados: %d\n", registrosCopiados);
        fprintf(log, "Arquivo de saída: %s\n", nomeSaida);
        fprintf(log, "------------------------------\n");
        
        return registrosCopiados;
    }
    
    return intercalarArquivos(nomesArquivos, numArquivos, nomeSaida, log);
}

// Função para ordenar arquivo usando intercalação ótima
int ordenarPorIntercalacaoOtima(FILE *arqEventos, int memDisponivel, int totalRegistros, FILE *log) {
    clock_t inicioT = clock();
    
    // Primeiro, cria as corridas usando seleção por substituição
    int numRuns = selecaoSubstituicao(arqEventos, memDisponivel, totalRegistros, log);
    
    if (numRuns <= 0) {
        fprintf(stderr, "Erro na criação das corridas.\n");
        return -1;
    }
    
    // Aloca array com nomes dos arquivos de corrida
    char **nomesArquivos = malloc(numRuns * sizeof(char*));
    if (!nomesArquivos) {
        fprintf(stderr, "Erro ao alocar memória para nomes de arquivos.\n");
        return -1;
    }
    
    // Preenche nomes dos arquivos de corrida
    for (int i = 0; i < numRuns; i++) {
        nomesArquivos[i] = malloc(100 * sizeof(char));
        sprintf(nomesArquivos[i], "run_eventos_%d.dat", i);
    }
    
    // Intercala as corridas para criar arquivo final ordenado
    int resultado = intercalacaoOtima(nomesArquivos, numRuns, "eventos_ordenados.dat", log);
    
    // Libera memória
    for (int i = 0; i < numRuns; i++) {
        free(nomesArquivos[i]);
    }
    free(nomesArquivos);
    
    clock_t fimT = clock();
    double tempo_total = ((double)(fimT - inicioT)) / CLOCKS_PER_SEC;
    
    fprintf(log, "\nTempo total de ordenação: %.6f segundos\n", tempo_total);
    printf("\nOrdenação por Intercalação Ótima concluída!\n");
    printf("Arquivo ordenado: eventos_ordenados.dat\n");
    
    return resultado;
}
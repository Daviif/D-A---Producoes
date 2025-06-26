#include "../include/utilities.h"
#include "../include/users.h"

void limpar_tela_ansi()
{
    printf("\033[2J\033[H");
}

char *NomeSeq(char *primeiraLetra)
{
    int tamanho = strlen(primeiraLetra);
    int i = tamanho - 1;

    while (i >= 0)
    {
        primeiraLetra[i]++;

        if (primeiraLetra[i] <= 'Z')
            return primeiraLetra;

        primeiraLetra[i] = 'A';
        i--;
    }

    int novoTam = tamanho + 1;
    char *novaLetra = (char *)malloc(novoTam + 1);
    if (novaLetra == NULL)
        return 0;

    novaLetra[0] = 'A';
    strcpy(novaLetra + 1, primeiraLetra);

    free(primeiraLetra);

    return novaLetra;
}

void embaralhar(int *array, int n)
{
    if (n > 1)
    {
        for (int i = n - 1; i > 0; i--)
        {
            int j = rand() % (i + 1);
            int temp = array[j];
            array[j] = array[i];
            array[i] = temp;
        }
    }
}

void pausarTela()
{
    printf("\n\nPressione ENTER para continuar...");
    getchar();
    getchar();
}

int tamanho_registroEv() {
    return sizeof(int) 
           + sizeof(char) * 100 
           + sizeof(char) * 150
           + sizeof(int)
           + sizeof(double); 
}

int tamanho_registroUs() {
    return sizeof(int) 
           + sizeof(char) * 100 
           + sizeof(char) * 100
           + sizeof(char) * 50
           + sizeof(char) * 12
           + sizeof(char) * 12
           + sizeof(Tipo); 
}

int tamanho_arquivoEv(FILE *arq) {
    fseek(arq, 0, SEEK_END);
    int tam = trunc(ftell(arq) / tamanho_registroEv());
    return tam;
}

int tamanho_arquivoUs(FILE *arq) {
    fseek(arq, 0, SEEK_END);
    int tam = trunc(ftell(arq) / tamanho_registroUs());
    return tam;
}
#include "../include/utilities.h"

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
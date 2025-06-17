#include "eventos.c"
#include "users.c"
#include "utilities.c"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void limpar_tela_ansi() {
    printf("\033[2J\033[H");
}


int main(){
    srand(time(NULL));

    FILE *arq_eventos, *arq_users;
    FILE *out;
    FILE *log;

    Evento *ev;
    User *us;

    if((arq_eventos = fopen("eventos.dat", "w+b")) == NULL){
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }
    if ((arq_users = fopen("users.dat", "w + b")) == NULL){
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }

    //Flag para controlar o loop
    int sair = 1;

    do{
        limpar_tela_ansi();
        printf("--------------------------- MENU ---------------------------\n");
        printf("1 - Ordenar Base\n");
        printf("2 - Fazer Busca\n");
        printf("3 - Cadastrar Usuário\n");
        printf("4 - Login\n");
        printf("5 - Opções Eventos\n");
        printf("6 - Carrinho\n");
        printf("7 - Logout\n");
        printf("0 - sair\n");
        printf("-------------------------- SAIDA ---------------------------\n");
        scanf("%d", &sair);

        switch (sair){
            case 1:
                ;
                int esc1 = 0;
                do{
                    limpar_tela_ansi();
                    printf("----------------- Tipo de Ordenação -----------------\n");
                    printf("Algum tipo de ordenação...\n");
                    printf("3 - Voltar\n");
                    printf("----------------- SAIDA -----------------\n");
                    scanf("%d", &esc1);
                    
                    if(esc1 == 3){
                        break;
                    }
                } while(esc1 != 3);

                break;
            case 2:
                ;
                int esc2 = 0;
                limpar_tela_ansi();
            default:
                break;
            }


    } while (sair != 0);
    
}
#include "eventos.c"
#include "users.c"
#include "utilities.c"
#include "HeapSort.c"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ERROR(msg) fprintf(stderr, "\033[1;31m%s\033[0m\n", msg)

int main()
{
    srand(time(NULL));

    FILE *arq_eventos, *arq_users;
    FILE *out;
    FILE *log;

    Evento *ev;
    User *us;

    if ((arq_eventos = fopen("eventos.dat", "wb+")) == NULL)
    {
        ERROR("erro ao abrir arquivo eventos.dat");
        exit(1);
    }

    if ((arq_users = fopen("users.dat", "wb+")) == NULL)
    {
        ERROR("Erro ao abrir arquivo users.dat");
        exit(1);
    }

    int tamEv = 5, tamUs = 10;

    User *usuarioLogado = NULL;

    criarBaseEventos(arq_eventos, tamEv);
    criarBaseUsuarios(arq_users, tamUs);

    RegistroHeap heap[tamEv + tamUs];
    // Flag para controlar o loop
    int sair = 1;

    do
    {
        limpar_tela_ansi();
        printf("--------------------------- MENU ---------------------------\n");
        printf("1 - Ordenar Base\n");
        printf("2 - Fazer Busca\n");
        printf("3 - Cadastrar Usuário\n");
        printf("4 - Login\n");
        printf("5 - Menu Eventos\n");
        printf("6 - Carrinho\n");
        printf("7 - Logout\n");
        printf("0 - sair\n");
        printf("-------------------------- SAIDA ---------------------------\n");
        scanf("%d", &sair);

        switch (sair)
        {
        case 1:
            limpar_tela_ansi();
            int esc1 = 0;
            do
            {
                limpar_tela_ansi();
                printf("----------------- Tipo de Ordenação -----------------\n");
                printf("Usaremos a Ordenaçao por HeapSort!\n");
                printf("Voce deseja odernar:\n");
                printf("1 - A base de Eventos\n");
                printf("2 - A base de Usuarios\n");
                printf("3 - Voltar\n");
                printf("----------------- SAIDA -----------------\n");
                scanf("%d", &esc1);

                if (esc1 == 3)
                {
                    break;
                }

                switch (esc1)
                {
                case 1:
                    limpar_tela_ansi();
                    printf("\nVoce escolheu ordenar a base de eventos!\n");
                    printf("A base desordenada:\n");
                    imprimirBaseEvento(arq_eventos);
                    printf("\n\n");
                    printf("Agora a base ordenada!");
                    rewind(arq_eventos);
                    HeapSort(heap, tamEv, arq_eventos, arq_users);
                    imprimirBaseEvento(arq_eventos);

                    pausarTela();
                    break;
                case 2:
                    limpar_tela_ansi();
                    printf("\nVoce escolheu ordenar a base de Usuarios!\n");
                    printf("A base desordenada:\n");
                    imprimirBaseUser(arq_users);
                    printf("\n\n");
                    printf("Agora a base ordenada!");
                    HeapSort(heap, tamUs, arq_eventos, arq_users);
                    imprimirBaseUser(arq_users);

                    pausarTela();
                    break;
                default:
                    break;
                }
            } while (esc1 != 3);

            pausarTela();
            break;
        case 2:
            limpar_tela_ansi();
            int esc2 = 0;

            pausarTela();
            break;
        case 3:
            limpar_tela_ansi();

            printf("Informe os dados para o cadastro: \n");
            printf("Nome: Davi | Email: davi@email.com | Senha: davi123 | Telefone: (31) 99999-9999 | CPF: 111.222.333-00 | Tipo: Produtor");
            cadastrarUsuario(arq_users, "Davi", "davi@email.com", "davi123", "(31) 99999-9999", "111.222.333-00", 0);
            tamUs++;
            // imprimirBaseUser(arq_users);

            pausarTela();
            break;
        case 4:
            if (usuarioLogado)
            {
                printf("\nVoce ja esta logado.\n");
            }
            else
            {
                char emailLogin[100] = "davi@email.com";
                char senhaLogin[50] = "davi123";
                printf("--- Login ---\n");
                printf("Email: davi@email.com ");
                // scanf("%s", emailLogin);
                printf("Senha: davi123");
                // scanf("%s", senhaLogin);

                usuarioLogado = loginPorEmailSenha(arq_users, emailLogin, senhaLogin);

                if (usuarioLogado)
                {
                    printf("\nLogin bem-sucedido! Bem-vindo(a), %s!\n", usuarioLogado->nome);
                }
                else
                {
                    ERROR("\nEmail ou senha incorretos.\n");
                }
            }

            pausarTela();
            break;

        case 5:
            limpar_tela_ansi();

            if (usuarioLogado == NULL)
            {
                int escVisitante;
                do
                {
                    limpar_tela_ansi();
                    printf("--- Menu de Eventos (Visitante) ---\n");
                    printf("1 - Listar Eventos\n");
                    printf("2 - Voltar ao Menu Principal\n");
                    printf("-------------------------------------\n");
                    printf("Escolha uma opcaoo: ");
                    scanf("%d", &escVisitante);

                    switch (escVisitante)
                    {
                    case 1:
                        printf("\n--- Lista de Todos os Eventos ---\n");
                        imprimirBaseEvento(arq_eventos);
                        pausarTela();
                        break;
                    case 2:
                        printf("\nVoltando ao menu principal...\n");
                        break;
                    default:
                        ERROR("\nOpcaoo invalida!\n");
                        pausarTela();
                        break;
                    }
                } while (escVisitante != 2);
                break;
            }

            if (usuarioLogado->tipo == Produtor)
            {
                int escProdutor;
                do
                {
                    limpar_tela_ansi();
                    printf("--- Menu de Eventos (Produtor) ---\n");
                    printf("1 - Cadastrar Novo Evento\n");
                    printf("2 - Listar Eventos\n");
                    printf("3 - Deletar um Evento\n");
                    printf("4 - Voltar ao Menu Principal\n");
                    printf("----------------------------------\n");
                    printf("Escolha uma opcao: ");
                    scanf("%d", &escProdutor);

                    switch (escProdutor)
                    {
                    case 1:
                        printf("Informe os dados para o cadastro: \n");
                        printf("Nome: Arraial D&A Producoes | Descricao: O melhor arraial da região! | Quantidade de Ingressos: 100 | Valo(R$): 20.50");
                        cadastrarEvento(arq_eventos, "Arraial D&A Producoes", "O melhor arraial da regiao!", 100, 20.5);

                        pausarTela();
                        break;
                    case 2:
                        printf("\n--- Listagem de Eventos ---\n");
                        imprimirBaseEvento(arq_eventos);

                        pausarTela();
                        break;
                    case 3:
                        printf("\n--- Exclusão de Evento ---\n");

                        rewind(arq_eventos);

                        Evento *ev = lerEventos(arq_eventos);
                        if (ev)
                        {
                            int idParaExcluir = ev->id;
                            free(ev);

                            rewind(arq_eventos);
                            if (deletarEventoPorId(arq_eventos, idParaExcluir))
                                printf("Evento com ID %d excluído com sucesso!\n", idParaExcluir);
                            else
                                printf("Evento com ID %d não encontrado.\n", idParaExcluir);
                        }
                        else
                        {
                            printf("Nenhum evento disponível para exclusão.\n");
                        }

                        pausarTela();
                        break;

                    case 4:
                        printf("\nVoltando ao menu principal...\n");
                        break;
                    default:
                        ERROR("\nOpcao invalida!\n");
                        pausarTela();
                    }
                } while (escProdutor != 4);
            }
            else if (usuarioLogado->tipo == Cliente)
            {
                int escCliente;
                do
                {
                    limpar_tela_ansi();
                    printf("------ Menu de Eventos (Cliente) ------\n");
                    printf("1 - Listar Todos os Eventos\n");
                    printf("2 - Adicionar Ingresso ao Carrinho\n");
                    printf("3 - Comprar Ingresso (Direto)\n");
                    printf("4 - Voltar ao Menu Principal\n");
                    printf("---------------------------------------\n");
                    printf("Escolha uma opcaoo: ");
                    scanf("%d", &escCliente);

                    switch (escCliente)
                    {
                    case 1:
                        printf("\n--- Lista de Todos os Eventos ---\n");
                        imprimirBaseEvento(arq_eventos);
                        pausarTela();
                        break;
                    case 2:
                        printf("\nFuncionalidade 'Adicionar ao Carrinho' a ser implementada.\n");
                        pausarTela();
                        break;
                    case 3:
                        printf("\nFuncionalidade 'Comprar Ingresso' a ser implementada.\n");
                        pausarTela();
                        break;
                    case 4:
                        printf("\nVoltando ao menu principal...\n");
                        break;
                    default:
                        ERROR("\nOpcaoo invalida!\n");
                        pausarTela();
                    }
                } while (escCliente != 4);
            }

            pausarTela();
            break;
        case 7:

            if (usuarioLogado)
            {
                printf("\n%s deslogado com sucesso.\n", usuarioLogado->nome);
                free(usuarioLogado);
                usuarioLogado = NULL;
            }
            else
            {
                printf("\nNenhum usuario esta logado.\n");
            }

            pausarTela();
            break;
        default:
            break;
        }

    } while (sair != 0);
}
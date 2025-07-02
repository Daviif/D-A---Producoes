#include "eventos.c"
#include "users.c"
#include "utilities.c"
#include "HeapSort.c"
#include "buscas.c"
#include "carrinho.c"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define ERROR(msg) fprintf(stderr, "\033[1;31m%s\033[0m\n", msg)

int main()
{
    srand(time(NULL));

    FILE *arq_eventos, *arq_users, *arq_carrinho, *arq_ingressos;
    FILE *log;

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

    if ((arq_carrinho = fopen("carrinhos.dat", "wb+")) == NULL)
    {
        ERROR("Erro ao abrir arquivo carrinhos.dat");
        exit(1);
    }

    if ((arq_ingressos = fopen("ingressos.dat", "wb+")) == NULL)
    {
        ERROR("Erro ao abrir arquivo ingressos.dat");
        exit(1);
    }
    if ((log = fopen("log.txt", "a+")) == NULL){
        ERROR("Erro ao abrir arquivo log.txt");
        exit(1);
    }

    int tamEv = 10, tamUs = 10;

    User *usuarioLogado = NULL;

    criarBaseEventos(arq_eventos, tamEv);
    criarBaseUsuarios(arq_users, tamUs);

    int sair = 1;

    do
    {
        limpar_tela_ansi();
        printf("--------------------------- MENU ---------------------------\n");
        printf("1 - Ordenar Base\n");
        printf("2 - Fazer Busca\n");
        printf("3 - Cadastrar UsuArio\n");
        printf("4 - Login\n");
        printf("5 - Menu Eventos\n");
        printf("6 - Carrinho\n");
        printf("7 - Ingressos\n");
        printf("8 - Logout\n");
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
                            printf("------------------------------------\n");
                            printf("Agora a base ordenada!\n");
                            rewind(arq_eventos);
                            int total_eventos = tamanho_arquivoEv(arq_eventos);
                            heapSort(arq_eventos, total_eventos, TIPO_Evento, log);
                            imprimirBaseEvento(arq_eventos);

                            pausarTela();
                            break;
                        case 2:
                            limpar_tela_ansi();
                            printf("\nVoce escolheu ordenar a base de Usuarios!\n");
                            printf("A base desordenada:\n");
                            imprimirBaseUser(arq_users);
                            printf("\n\n");
                            printf("------------------------------------\n");
                            printf("Agora a base ordenada!\n");
                            rewind(arq_users);
                            int total_users = tamanho_arquivoUs(arq_users);
                            heapSort(arq_users, total_users, TIPO_User,log);
                            imprimirBaseUser(arq_users);

                            pausarTela();
                            break;
                        default:
                            break;
                    }
                } while (esc1 != 3);
                break;
            case 2:
                limpar_tela_ansi();
                int esc2 = 0;

                do
                {
                    printf("----------------- Tipo de Busca -----------------\n");
                    printf("1 - Busca Sequencial\n");
                    printf("2 - Busca Binária\n");
                    printf("3 - Voltar\n");
                    printf("----------------- SAIDA -----------------\n");
                    scanf("%d", &esc2);

                    if (esc2 == 3)
                    {
                        break;
                    }

                    switch (esc2)
                    {
                        case 1:
                        {
                            int esc02 = 0;
                            do
                            {
                                limpar_tela_ansi();
                                printf("----------------- OPCOES -----------------\n");
                                printf("Voce deseja usar Busca Sequencial em:\n");
                                printf("1 - Eventos\n");
                                printf("2 - Usuarios\n");
                                printf("3 - Voltar\n");
                                printf("----------------- SAIDA -----------------\n");
                                scanf("%d", &esc02);

                                if (esc02 == 3)
                                {
                                    break;
                                }

                                switch (esc02)
                                {
                                case 1:
                                {
                                    Evento *ev;
                                    int id;
                                    printf("Voce escolheu Eventos!\n");
                                    printf("Informe o ID do evento: ");
                                    scanf("%d", &id);
                                    rewind(arq_eventos);
                                    ev = Evento_buscaSequencial_PorId(arq_eventos, id, log);
                                    if (!ev)
                                    {
                                        printf("Id de numero %d nao encontrado.", id);
                                        printf("Tente novamente");
                                        break;
                                    }
                                    imprimirEvento(ev);
                                    pausarTela();
                                    break;
                                }
                                case 2:
                                {
                                    User *us;
                                    int id;
                                    printf("Voce escolheu Usuarios!\n");
                                    printf("Informe o ID do usuario: ");
                                    scanf("%d", &id);
                                    rewind(arq_users);
                                    us = User_buscaSequencial_PorId(arq_users, id, log);
                                    if (!us)
                                    {
                                        printf("Id de numero %d nao encontrado.", id);
                                        printf("Tente novamente");
                                        break;
                                    }
                                    imprimirUser(us);
                                    pausarTela();
                                    break;
                                }
                                default:
                                    printf("Opcao Invalida");
                                    break;
                                }
                            } while (esc02 != 3);
                            break;
                        }
                        case 2:
                        {
                            int esc02 = 0;
                            do
                            {
                                limpar_tela_ansi();
                                printf("----------------- OPCOES -----------------\n");
                                printf("Voce deseja usar Busca Binária em:\n");
                                printf("1 - Eventos\n");
                                printf("2 - Usuarios\n");
                                printf("3 - Voltar\n");
                                printf("----------------- SAIDA -----------------\n");
                                scanf("%d", &esc02);

                                if (esc02 == 3)
                                {
                                    break;
                                }

                                switch (esc02)
                                {
                                case 1:
                                {
                                    Evento *ev;
                                    int idB;
                                    printf("Você escolheu Eventos!\n");
                                    printf("A base tem que estar ordenada!\nOrdenando...\n");
                                    int total_eventos = tamanho_arquivoEv(arq_eventos);
                                    heapSort(arq_eventos, total_eventos, TIPO_Evento, log);
                                    printf("Ordenado!\nAgora informe o ID do evento: ");
                                    scanf("%d", &idB);

                                    rewind(arq_eventos);
                                    ev = Evento_buscaBinaria_PorId(arq_eventos, idB, 0, tamanho_arquivoEv(arq_eventos) - 1, log);

                                    if (!ev)
                                    {
                                        printf("Id de numero %d não encontrado.", idB);
                                        printf("Tente novamente");
                                        pausarTela();
                                        break;
                                    }
                                    imprimirEvento(ev);
                                    pausarTela();
                                    break;
                                }
                                case 2:
                                {
                                    User *us;
                                    int idB;
                                    printf("Você escolheu Usuarios!\n");
                                    printf("A base tem que estar ordenada!\nOrdenando...\n");
                                    int total_users = tamanho_arquivoUs(arq_users);
                                    heapSort(arq_users, total_users, TIPO_User, log);
                                    printf("Ordenado!\nAgora informe o ID do Usuario: ");
                                    scanf("%d", &idB);
                                    rewind(arq_users);

                                    us = User_buscaBinaria_PorID(arq_users, idB, 0, tamanho_arquivoUs(arq_users) - 1, log);
                                    if (!us)
                                    {
                                        printf("Id de numero %d não encontrado.", idB);
                                        printf("Tente novamente");
                                        break;
                                    }
                                    imprimirUser(us);
                                    pausarTela();
                                    break;
                                }
                                default:
                                    printf("Opção Invalida");
                                    break;
                                }
                            } while (esc02 != 3);
                            break;
                        }
                        default:
                            printf("Opção Invalida");
                            break;
                    }
                } while (esc2 != 3);
                break;
            case 3:
                limpar_tela_ansi();

                printf("Informe os dados para o cadastro: \n");
                printf("Nome: Davi | Email: davi@email.com | Senha: davi123 | Telefone: (31) 99999-9999 | CPF: 111.222.333-00 | Tipo: Produtor");
                cadastrarUsuario(arq_users, "Davi", "davi@email.com", "davi123", "(31) 99999-9999", "111.222.333-00", 0);
                cadastrarUsuario(arq_users, "Arthur", "arthur@email.com", "arthur123", "(31) 99999-9999", "111.222.333-00", 1);
                imprimirBaseUser(arq_users);

                pausarTela();
                break;
            case 4:
                if (usuarioLogado)
                {
                    printf("\nVoce ja esta logado.\n");
                }
                else
                {
                    //char emailLogin[100] = "davi@email.com";
                    //char senhaLogin[50] = "davi123";
                    char emailLogin[100] = "arthur@email.com";
                    char senhaLogin[50] = "arthur123";
                    printf("--- Login ---\n");
                    printf("Email: davi@email.com ");
                    printf("Senha: davi123");

                    //Logar Produtor
                    //usuarioLogado = loginPorEmailSenha(arq_users, emailLogin, senhaLogin);
                    //Logar Usuario
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
                            limpar_tela_ansi();

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
                            int idParaExcluir = 3;

                            printf("Informe o ID do evento a ser deletado: ");
                            scanf("%d", &idParaExcluir);
                            rewind(arq_eventos);

                            Evento *ev = lerEventos(arq_eventos);
                            if (ev)
                            {
                                
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
                            break;
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
                        printf("3 - Voltar ao Menu Principal\n");
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
                            rewind(arq_eventos);
                            Evento *ev = lerEventos(arq_eventos);
                            if (!ev)
                            {
                                printf("Nenhum evento encontrado.\n");
                                break;
                            }

                            rewind(arq_carrinho);
                            Carrinho *car = NULL;
                            int encontrado = 0;
                            FILE *tempCarrinho = tmpfile();

                            while ((car = lerCarrinho(arq_carrinho)) != NULL)
                            {
                                if (car->idCliente == usuarioLogado->id)
                                {
                                    encontrado = 1;
                                    break;
                                }
                                salvarCarrinho(car, tempCarrinho);
                                free(car);
                            }

                            if (!encontrado)
                            {
                                int novoId = gerarIdUnico(arq_carrinho, sizeof(Carrinho));
                                car = criarCarrinho(novoId, usuarioLogado->id);
                                salvarCarrinho(car, arq_carrinho);
                            }

                            ItemCarrinho item;
                            item.id = 0;
                            item.idEvento = ev->id;
                            item.quantidade = 1 + rand() % 10;

                            adicionarItemAoCarrinho(arq_carrinho, car->id, &item);

                            printf("Item adicionado ao carrinho com sucesso!\n");

                            if (ev)
                                free(ev);
                            if (car)
                                free(car);
                            if (tempCarrinho)
                                fclose(tempCarrinho);

                            pausarTela();
                            break;
                        case 3:
                            printf("\nVoltando ao menu principal...\n");
                            break;
                        default:
                            ERROR("\nOpcaoo invalida!\n");
                            pausarTela();
                            break;
                        }
                    } while (escCliente != 3);
                }

                break;
            case 6:
                if (usuarioLogado == NULL)
                {
                    ERROR("Faça login para continuar!");
                    break;
                }
                else
                {
                    int esc;
                    do
                    {
                        limpar_tela_ansi();
                        printf("--- Carrinho ---\n");
                        printf("1 - Consultar Carrinho\n");
                        printf("2 - Limpar Carrinho\n");
                        printf("3 - Finalizar carrinho (comprar)\n");
                        printf("4 - Voltar para o menu inicial\n");
                        printf("-------------------------------------\n");
                        printf("Escolha uma opcaoo: ");
                        scanf("%d", &esc);

                        switch (esc)
                        {
                        case 1:
                            rewind(arq_carrinho);
                            Carrinho *c;
                            while ((c = lerCarrinho(arq_carrinho)) != NULL)
                            {
                                if (c->idCliente == usuarioLogado->id)
                                {
                                    printf("sss %d", c->idCliente);
                                    imprimirCarrinho(c);
                                    free(c);
                                    break;
                                }
                                free(c);
                            }
                            pausarTela();
                            break;

                        case 2:
                            rewind(arq_carrinho);
                            Carrinho *c2;
                            int achouRemover = 0;

                            while ((c2 = lerCarrinho(arq_carrinho)) != NULL)
                            {
                                if (c2->idCliente == usuarioLogado->id)
                                {
                                    achouRemover = 1;
                                    if (c2->totalItens > 0)
                                    {
                                        removerItemDoCarrinho(arq_carrinho, c2->id, c2->itens[0].idEvento);
                                        printf("Item removido do carrinho.\n");
                                    }
                                    else
                                    {
                                        printf("Carrinho esta vazio.\n");
                                    }
                                    free(c2);
                                    break;
                                }
                                free(c2);
                            }
                            if (!achouRemover)
                                printf("Carrinho não encontrado.\n");

                            pausarTela();
                            break;
                        case 3:
                            rewind(arq_carrinho);
                            Carrinho *c3;
                            while ((c3 = lerCarrinho(arq_carrinho)) != NULL)
                            {
                                if (c3->idCliente == usuarioLogado->id)
                                {
                                    finalizarCarrinho(arq_carrinho, arq_ingressos, c3->id);
                                    printf("Carrinho finalizado com sucesso!\n");
                                    free(c3);
                                    break;
                                }
                                free(c3);
                            }
                            pausarTela();
                            break;

                        case 4:
                            printf("\nVoltando ao menu principal...\n");
                            break;

                        default:
                            ERROR("\nOpcaoo invalida!\n");
                            pausarTela();
                            break;
                        }
                    } while (esc != 4);
                }

                pausarTela();
                break;
            case 7:
                if (usuarioLogado == NULL)
                {
                    ERROR("Faça login para visualizar seus ingressos!");
                }
                else
                {
                    rewind(arq_ingressos);
                    listarIngressos(arq_ingressos, usuarioLogado->id);
                }

                pausarTela();
                break;
            case 8:

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
    
    fclose(arq_eventos);
    fclose(arq_users);
    fclose(arq_carrinho);
    fclose(arq_ingressos);
    fclose(log);
    return 0;
}
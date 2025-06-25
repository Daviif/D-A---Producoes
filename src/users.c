#include "../include/users.h"

User *CadastrarUsuario(int id, char *nome, char *telefone, char *cpf, Tipo usuario){
    User *us = (User *) malloc (sizeof(User));
    int *piscina_ids = (int *) malloc (sizeof(int));
    if(!piscina_ids) return NULL;

    if(us) memset(us, 0, sizeof(User));

    us -> id = id;
    strncpy(us -> nome, nome, sizeof(us -> nome) - 1);
    us -> nome[sizeof(us -> nome) - 1] = '\0';
    strncpy(us -> telefone, telefone, sizeof(us -> telefone) - 1);
    us -> telefone[sizeof(us -> telefone) - 1] = '\0';
    strncpy(us -> cpf, cpf,sizeof(us -> cpf) - 1);
    us -> cpf[sizeof(us -> cpf) - 1] = '\0';
    us -> tipo = usuario;

    return us;
}

void salvarUsuario(User *us, FILE *out){
    fwrite(&us -> id, sizeof(int), 1, out);
    fwrite(us -> nome, sizeof(char), sizeof(us -> nome), out);
    fwrite(us -> telefone, sizeof(char), sizeof(us -> telefone), out);
    fwrite(us -> cpf, sizeof(char), sizeof(us -> cpf), out);
    fwrite(&us -> tipo, sizeof(Tipo), sizeof(us -> tipo), out);
}

User *lerUsuario(FILE *in){
    User *us = (User *) malloc (sizeof(User));

    if(!us) return NULL;
    if (fread(&us->id, sizeof(int), 1, in) < 1) {
        free(us);
        return NULL;
    }
    fread(us->nome, sizeof(char), sizeof(us->nome), in);
    fread(us->telefone, sizeof(char), sizeof(us->telefone), in);
     fread(us->cpf, sizeof(char), sizeof(us->cpf), in);
    fread(&us->tipo, sizeof(Tipo), 2, in);
    return us;
}

void criarBaseUsuarios(FILE *out, int qtdUser){
    User *us;

    char nomeUs[100];
    char telFmt[50];
    char cpfFmt[15];


    char *letra = (char *)malloc(2);
    if (letra == NULL) {
        perror("Falha na alocação inicial");
        return; // Correção: 'return' sem valor para função void
    }
    strcpy(letra, "A");

    int *piscina_ids = (int *) malloc (qtdUser * sizeof(int));
    if(!piscina_ids) return;

    for(int i = 0; i < qtdUser; i++){
        piscina_ids[i] = 1 + i;
    }
    embaralhar(piscina_ids, qtdUser);
    printf("Gerando a base de Usuarios...\n");

    for (int i = 0; i < qtdUser; i++) {
        int idUnico = piscina_ids[i];

        sprintf(nomeUs, "Evento %s", letra);
        sprintf(telFmt, "(00) 99988-766%d%d", idUnico, idUnico);
        sprintf(cpfFmt, "000.000.000-%d%d",idUnico > 9 ? 0 : idUnico, i * 2 + 1);
       
        us = CadastrarUsuario(idUnico, nomeUs, telFmt, cpfFmt,  idUnico %5 == 0 ? Produtor : Cliente);
        
        if (us) {
            salvarUsuario(us, out);
            free(us); // 
        }

        letra = NomeSeq(letra);
        if (letra == NULL) { 
            perror("Falha ao gerar próxima sequência de nome");
            break;
        }
    }
    
    free(letra);
    free(piscina_ids);
    printf("Base de Usuários gerada com sucesso!\n");
}

void imprimirUser(User *us) {
    if (!us) return;
    printf("**********************************************");
    printf("\nID do Usuario: ");
    printf("%d", us-> id);
    printf("\nNome: ");
    printf("%s", us -> nome);
    printf("\nTelefone: ");
    printf("%s%d", us -> telefone);
    printf("\nCPF: ");
    printf("%s%d", us -> cpf);
    printf("\nTipo do Usuario: ");
    printf("%d - %s", us-> tipo, us -> tipo == 0 ? "Produtor" : "Cliente");
    printf("\n**********************************************");
}

void imprimirBaseUser(FILE *out){
    rewind(out);
    User *us;

    while ((us = lerUsuario(out)) != NULL){
        imprimirUser(us);
    }
    free(us);    
}
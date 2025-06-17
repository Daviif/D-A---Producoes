#include "../include/users.h"

User *CadastrarUsuario(char *nome, char *telefone, char *cpf, Tipo usuario){
    User *us = (User *) malloc (sizeof(User));
    int *piscina_ids = (int *) malloc (sizeof(int));
    if(!piscina_ids) return NULL;
    int id;

    if(usuario == Cliente){
        for(int i = 0; i < MAX_CLI; i++){
            piscina_ids[i] = 1 + i;
            id = piscina_ids[i];
        }
        embaralhar(piscina_ids, MAX_CLI);
    }
    else if (usuario == Produtor){
        for(int i = 0; i < MAX_PROD; i++){
            piscina_ids[i] = 1 + i;
            id = piscina_ids[i];
        }
        embaralhar(piscina_ids, MAX_PROD);
    }

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


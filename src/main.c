#include "eventos.c"
#include "utilities.c"


int main(){
    srand(time(NULL));

    FILE *arq_eventos, *arq_users;
    FILE *out;
    FILE *log;

    Evento *ev;

    if((arq_eventos = fopen("eventos.dat", "w+b")) == NULL){
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }
    if ((arq_users = fopen("users.dat", "w + b")) == NULL){
        printf("Erro ao abrir aqruivo\n");
        exit(1);
    }

    criarBaseEventos(arq_eventos, 2);
    imprimirBase(arq_eventos);

}
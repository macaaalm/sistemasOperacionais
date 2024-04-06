#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <string.h>

// tipo de dado para armazenar tempo e direcao para cada pessoa
struct Pessoa {
    int tempo;
    int direcao;
};

struct thread_data {
    struct Pessoa *fila;
    int qtd;
    int *tempo;
    int *indice;
};

// funcao para realizar um ciclo da escada rolante (direcao 1 ou 0)
int escada_direcao (struct Pessoa fila[], int qtd, int tempo, int *indice){
    int t = tempo, t_aux;
    for (int i = *indice; i < qtd; i++){
        t_aux = fila[i].tempo;
        // se o tempo da pessoa no topo da fila for menor que o tempo contado
        if (fila[i].tempo < t){
            t_aux = tempo;
        }
        // se o tempo da pessoa no topo da fila for menor ou igual ao tempo contado + 10
        // mais pessoas irao usar a escada rolante nesse ciclo
        if (fila[i].tempo <= t+10){
            (*indice)++;
            t = t_aux;
        // senao, retornar tempo do ciclo
        // nao ha mais pessoas para usar a escada rolante nesse ciclo
        } else{
            return t+10;
        }
    }
    return t+10;
}

int main(void) {
    // declaracao de variaveis
    int qtd_pessoas, i, qtd_0 = 0, qtd_1 = 0, indice0 = 0, indice1 = 0;
    FILE * arquivo;
    // ponteiros para indice de arrays que atuam como filas
    int *ptr0, *ptr1;
    ptr0 = &indice0;
    ptr1 = &indice1;

    // le arquivo e cria vetor de pessoas
    arquivo = fopen ("teste.txt", "r");
    fscanf(arquivo, "%d", &qtd_pessoas);
    struct Pessoa pessoas [qtd_pessoas];

    // calcular quantas pessoas em cada direcao
    for (i = 0; i < qtd_pessoas; i++) {
        fscanf(arquivo, "%d %d", &pessoas[i].tempo, &pessoas[i].direcao);
        if (pessoas[i].direcao == 0){
            qtd_0++;
        } else{
            qtd_1++;
        }
    }

    // alocar pessoas em filas (arrays) de acordo com a direcao
    struct Pessoa fila0 [qtd_0];
    struct Pessoa fila1 [qtd_1];
    int pessoas0 = 0, pessoas1 = 0;
    for (i = 0; i < qtd_pessoas; i++) {
        if (pessoas[i].direcao == 0){
            fila0 [pessoas0] = pessoas[i];
            pessoas0++;
        } else{
            fila1 [pessoas1] = pessoas[i];
            pessoas1++;
        }
    }

    pid_t filhoPID = fork();

  if (filhoPID < 0){
    printf("Erro ao criar processo filho\n");
  } else if (filhoPID == 0){
    key_t chave = ftok("memoriaComp.txt",11);

    int shmid = shmget(chave, sizeof(int), 0666 | IPC_CREAT);

    int* tempo = (int*) shmat(shmid, (void*)0, 0);

    printf("Aqui eh o processo filho %d\n", filhoPID);
    *tempo = 0;

    while(indice0 < qtd_0){
        *tempo = escada_direcao(fila0, qtd_0, *tempo, ptr0);
    }

    shmdt(tempo);

    return 0;
    
  } else{
    key_t chave = ftok("memoriaComp.txt",11);

    int shmid = shmget(chave, sizeof(int), 0666 | IPC_CREAT);

    int* tempo = (int*) shmat(shmid, (void*)0, 0);
    
    printf("Aqui eh o processo pai %d\n", filhoPID);
    while(indice1 < qtd_1){
        *tempo = escada_direcao(fila1, qtd_1, *tempo, ptr1);
    }
    printf("%d", *tempo);
    
    shmdt(tempo);

    shmctl(shmid, IPC_RMID, NULL);

    return 0;
  }
    
    // calcular tempo total
    // usando loop while para calcular cada ciclo da escada rolante
    //printf("%d\n", tempo);
    //return 0;
}


/*
int main(void) {
  
  pid_t filhoPID = fork();

  if (filhoPID < 0){
    printf("Erro ao criar processo filho\n");
  } else if (filhoPID == 0){
    key_t chave = ftok("memoriaComp.txt",11);
    int shmid = shmget(chave, sizeof(int), 0666 | IPC_CREAT);

    int* str = (int*) shmat(shmid, (void*)0, 0);

    printf("Aqui eh o processo filho %d\n", filhoPID);
    *str = 222;

    shmdt(str);

    return 0;
    
  } else{
    key_t chave = ftok("memoriaComp.txt",11);

    int shmid = shmget(chave, sizeof(int), 0666 | IPC_CREAT);

    int* str = (int*) shmat(shmid, (void*)0, 0);
    
    printf("Aqui eh o processo pai %d\n", filhoPID);
    printf("%d", *str);
    
    shmdt(str);

    shmctl(shmid, IPC_RMID, NULL);

    return 0;
  }
}

*/

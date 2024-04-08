#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

pthread_mutex_t lock;
int i = 0;
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


void *thread_func(void *arg) {
    struct thread_data *data = (struct thread_data *)arg;
    //pthread_mutex_lock(&lock);
    if (i == 0) {
        printf("Thread criada!\n");
        i++;
    } else {
        printf("Thread criada!\n");
    } 
    while (*(data->indice) < data->qtd) {
        pthread_mutex_lock(&lock);
        *(data->tempo) = escada_direcao(data->fila, data->qtd, *(data->tempo), data->indice);
        printf("fila com qtd %d rodou %d\n", data->qtd, *data->tempo);
        if (i == 1){ 
            sleep(1);
            i++;
        }
        pthread_mutex_unlock(&lock);
    }
    //pthread_mutex_unlock(&lock);
    return NULL;
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

    // calcular tempo total
    // usando loop while para calcular cada ciclo da escada rolante
    int tempo = 0;
    pthread_t thread0, thread1;

    struct thread_data data0 = {fila0, qtd_0, &tempo, ptr0};
    struct thread_data data1 = {fila1, qtd_1, &tempo, ptr1};
    
    pthread_mutex_init(&lock, NULL);
   
    if (pessoas[0].direcao == 0){
        if(pthread_create(&thread0, NULL, thread_func, &data0) != 0){
            printf("Erro ao criar thread0!");
        }
        if(pthread_create(&thread1, NULL, thread_func, &data1) != 0){
            printf("Erro ao criar thread1!");
        } 
    } else{
        if(pthread_create(&thread1, NULL, thread_func, &data1) != 0){
            printf("Erro ao criar thread1!");
        } 
        if(pthread_create(&thread0, NULL, thread_func, &data0) != 0){
            printf("Erro ao criar thread0!");
        }
    }
    pthread_join(thread0, NULL);
    pthread_join(thread1, NULL);
    pthread_mutex_destroy(&lock);
    printf("%d\n", tempo);
    return 0;
}

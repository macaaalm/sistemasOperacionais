#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

//64kB stack
#define FIBER_STACK 1024*64

struct c {
 int saldo;
 pthread_mutex_t bloqueio; //adiciono um mutex a estrutura da conta
};

struct thread_data {
    struct c *c1;
    struct c *c2;
};

typedef struct c conta;

conta from, to, conta1, conta2;
int valor;

//a thread filha executara essa funcao
void* transferencia(void *arg) {
 struct thread_data *data = (struct thread_data*)arg;

 //bloqueio as contas antes de acessa-las
 pthread_mutex_lock(&data->c1->bloqueio);
 pthread_mutex_lock(&data->c2->bloqueio);

 if (data->c1->saldo >= valor) { //caso eu tiver saldo suficiente na conta 'from'...
  data->c1->saldo -= valor; //aqui retiro o valor da conta 'from'
  printf("Transferencia de %d reais para a conta %d\n", valor, data->c2->saldo);
  data->c2->saldo += valor; //e depois adiciono a conta 'to'
  printf("Transferencia de %d reais para a conta %d\n", valor, data->c1->saldo);
 }

 //desbloqueio as contas apos acessa-las
 pthread_mutex_unlock(&data->c2->bloqueio);
 pthread_mutex_unlock(&data->c1->bloqueio);

 printf("Transferencia realizada com sucesso!\n");
 printf("Saldo de c1: %d\n", data->c1->saldo);
 printf("Saldo de c2: %d\n", data->c2->saldo);

 return NULL;
}

int main() {
 void* stack;
 pid_t pid;
 int i;

 //aqui inicializo os mutexes
 pthread_mutex_init(&from.bloqueio, NULL);
 pthread_mutex_init(&to.bloqueio, NULL);

 //as contas comecam com saldo 100
 from.saldo = 100;
 to.saldo = 100;
 conta1.saldo = 100;
 conta2.saldo = 100;

 printf("Transferindo 1 para a conta c2\n");
 valor = 1;

 struct thread_data *data = (struct thread_data*)malloc(sizeof(struct thread_data)*100);
 // criar um vetor de threads (utilizando ponteiro)
 pthread_t *threads;
 // alocar memoria dinamicamente para o vetor de threads
 threads = (pthread_t*)malloc(sizeof(pthread_t)*100);

 for (i = 0; i < 100; i++) {
   data[i].c1 = &from;
   data[i].c2 = &to;
   pthread_create(&threads[i], NULL, transferencia, &data[i]);
 }
  
 for (i = 0; i < 100; i++) {
   pthread_join(threads[i], NULL);
 }

 //aqui eu destruo os mutexes
 pthread_mutex_destroy(&from.bloqueio);
 pthread_mutex_destroy(&to.bloqueio);

 printf("Transferencias concluidas e memoria liberada.\n");

 free(data);
 free(threads);

 return 0;
}



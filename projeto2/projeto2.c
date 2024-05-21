#define _GNU_SOURCE
#include <stdlib.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <sched.h>
#include <stdio.h>
#include <pthread.h> //pthread para usar mutex

//64kB stack
#define FIBER_STACK 1024*64

struct c {
 int saldo;
 pthread_mutex_t bloqueio; //adiciono um mutex a estrutura da conta
};

struct thread_data {
    struct c c1;
    struct c c2;
};

typedef struct c conta;

conta from, to, conta1, conta2;
int valor;

//a thread filha executara essa funcao
void* transferencia( void *arg)
{
 //bloqueio as contas antes de acessa-las
 pthread_mutex_lock(&from.bloqueio);
 pthread_mutex_lock(&to.bloqueio);

 if (from.saldo >= valor){ //caso eu tiver saldo suficiente na conta 'from'...
 from.saldo -= valor; //aqui retiro o valor da conta 'from'
  printf("Transferencia de %d reais para a conta %d\n", valor, to.saldo);
 to.saldo += valor; //e depois adiciono a conta 'to'
   printf("Transferencia de %d reais para a conta %d\n", valor, from.saldo);
 }

 //desbloqueio as contas apos acessa-las
 pthread_mutex_unlock(&to.bloqueio);
 pthread_mutex_unlock(&from.bloqueio);

 printf("Transferencia realizada com sucesso!\n");
 printf("Saldo de c1: %d\n", from.saldo);
 printf("Saldo de c2: %d\n", to.saldo);

 return 0;
}

int main()
{
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

 printf( "Transferindo 10 para a conta c2\n" );
 valor = 10;

struct thread_data *data = (struct thread_data*)malloc(sizeof(struct thread_data)*100);
  // criar um vetor de threads (utilizando ponteiro)
  pthread_t *threads;
  // alocar memoria dinamicamente para o vetor de threads
  threads = (pthread_t*)malloc(sizeof(pthread_t)*100);

 for (i = 0; i < 10; i++) {
   data[i].c1 = from;
   data[i].c2 = to;
   pthread_create(&threads[i], NULL, transferencia, &data[i]);
 }
  
   for (i = 0; i < 10; i++) {
     pthread_join(threads[i], NULL);
   }

  
  printf("\nsaldo from: %d\n", from.saldo);
  printf("saldo to: %d\n", to.saldo);

  

 //aqui eu destruo os mutexes
 pthread_mutex_destroy(&from.bloqueio);
 pthread_mutex_destroy(&to.bloqueio);

 printf("Transferencias concluidas e memoria liberada.\n");



 return 0;
}


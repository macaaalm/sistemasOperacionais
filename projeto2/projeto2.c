#define _GNU_SOURCE
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// criar mutex para acessar contas 1 e 2 (to, from)
pthread_mutex_t lockc1;
pthread_mutex_t lockc2;

// tipo de dado struct (conta)
struct conta {
  char nome[100];
  int saldo; 
};

// tipo de dado enviado para thread
struct thread_data {

  struct conta *c1;
  struct conta *c2;
};

// valor utilizado na transferencia
int valor;

// a thread filha executara essa funcao
void *transferencia(void *arg) {
  struct thread_data *data = (struct thread_data *)arg;

  // bloqueio as contas antes de acessa-las
  pthread_mutex_lock(&lockc1);
  pthread_mutex_lock(&lockc2);

  if (data->c1->saldo >= valor) { // caso eu tiver saldo suficiente na conta 'c1'...
    data->c1->saldo -= valor; // aqui retiro o valor da conta 'c1'
    data->c2->saldo += valor; // e depois adiciono a conta 'c2'
    printf("Transferencia de %d reais da conta %s para a conta %s\n", valor, data->c1->nome, data->c2->nome);
    // mensagem de transferencia realizada com sucesso
    printf("Transferencia realizada com sucesso!\n");
    printf("Saldo da conta %s: %d\n", data->c1->nome, data->c1->saldo);
    printf("Saldo da conta %s: %d\n", data->c2->nome, data->c2->saldo);
  } else{
    printf("Saldo insuficiente na conta %s\n", data->c1->nome);
  }
  
  // desbloqueio as contas apos acessa-las
  pthread_mutex_unlock(&lockc1);
  pthread_mutex_unlock(&lockc2);

  return NULL;
}

int main() {
  void *stack;
  pid_t pid;
  int i;

  // aqui inicializo os mutexes
  pthread_mutex_init(&lockc1, NULL);
  pthread_mutex_init(&lockc2, NULL);

  // criar variaveis conta (from, to) com nomes (conta1, conta2)
  struct conta from, to;
  strcpy(from.nome, "conta1");
  strcpy(to.nome, "conta2");
  
  // as contas comecam com saldo 100
  from.saldo = 100;
  to.saldo = 100;
  
  valor = 1; // valor da transferencia

  // criar vetor de thread_data
  struct thread_data *data = (struct thread_data *)malloc(sizeof(struct thread_data) * 100);
  
  // criar um vetor de threads (utilizando ponteiro)
  pthread_t *threads;
  // alocar memoria dinamicamente para o vetor de threads
  threads = (pthread_t *)malloc(sizeof(pthread_t) * 100);
  
  // criar 100 threads
  for (i = 0; i < 100; i++) {
    if (i % 5 == 0) { // exemplificando como as contas podem trocar de ordem (20
                      // vezes nesse caso)
      data[i].c1 = &to;
      data[i].c2 = &from;
      pthread_create(&threads[i], NULL, transferencia, &data[i]);
    } else {
      data[i].c1 = &from;
      data[i].c2 = &to;
      pthread_create(&threads[i], NULL, transferencia, &data[i]);
    }
  }

  // esperar threads terminarem a execucao
  for (i = 0; i < 100; i++) {
    pthread_join(threads[i], NULL);
  }

  // aqui eu destruo os mutexes
  pthread_mutex_destroy(&lockc1);
  pthread_mutex_destroy(&lockc2);

  printf("Transferencias concluidas e memoria liberada.\n");

  // liberar memoria
  free(data);
  free(threads);

  return 0;
}

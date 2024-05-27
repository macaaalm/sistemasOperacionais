#define _GNU_SOURCE
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

pthread_mutex_t lockc1;
pthread_mutex_t lockc2;

struct conta {
  char nome[100];
  int saldo; // adiciono um mutex a estrutura da conta
};

struct thread_data {
  struct conta *c1;
  struct conta *c2;
};

int valor;

// a thread filha executara essa funcao
void *transferencia(void *arg) {
  struct thread_data *data = (struct thread_data *)arg;

  // bloqueio as contas antes de acessa-las
  pthread_mutex_lock(&lockc1);
  pthread_mutex_lock(&lockc2);

  if (data->c1->saldo >=
      valor) { // caso eu tiver saldo suficiente na conta 'from'...
    data->c1->saldo -= valor; // aqui retiro o valor da conta 'from'
    data->c2->saldo += valor; // e depois adiciono a conta 'to'
    printf("Transferencia de %d reais da conta %s\n", valor, data->c1->nome);
    printf("Transferencia de %d reais para a conta %s\n", valor,
           data->c2->nome);
  }
  printf("Transferencia realizada com sucesso!\n");
  printf("Saldo da conta %s: %d\n", data->c1->nome, data->c1->saldo);
  printf("Saldo da conta %s: %d\n", data->c2->nome, data->c2->saldo);
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

  struct conta from, to;
  strcpy(from.nome, "conta1");
  strcpy(to.nome, "conta2");
  // as contas comecam com saldo 100
  from.saldo = 100;
  to.saldo = 100;

  printf("Transferindo 10 para a conta c2\n");
  valor = 1;

  struct thread_data *data =
      (struct thread_data *)malloc(sizeof(struct thread_data) * 100);
  // criar um vetor de threads (utilizando ponteiro)
  pthread_t *threads;
  // alocar memoria dinamicamente para o vetor de threads
  threads = (pthread_t *)malloc(sizeof(pthread_t) * 100);

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

  for (i = 0; i < 100; i++) {
    pthread_join(threads[i], NULL);
  }

  // aqui eu destruo os mutexes
  pthread_mutex_destroy(&lockc1);
  pthread_mutex_destroy(&lockc2);

  printf("Transferencias concluidas e memoria liberada.\n");

  free(data);
  free(threads);

  return 0;
}


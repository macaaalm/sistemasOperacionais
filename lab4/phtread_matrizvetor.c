#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define N 3

int matriz[N][N] = {{5, 3, 1}, {1, 2, 7}, {6, 3, 9}};
int vetor[N] = {5, 1, 3};

typedef struct {
  int linha;  
  int resultado; 
} ThreadArgs;

// funcao que thread executara
void *phtread_matrizvetor(void *arg) {
  ThreadArgs *args = (ThreadArgs *)arg;
  args->resultado = 0;
  for (int i = 0; i < N; i++) {
    args->resultado += matriz[args->linha][i] * vetor[i];
  }
  pthread_exit(NULL);
}

int main() {
  pthread_t threads[N];
  ThreadArgs args[N];

  // criando threads
  for (int i = 0; i < N; i++) {
    args[i].linha = i;
    if (pthread_create(&threads[i], NULL, phtread_matrizvetor, (void *)&args[i]) != 0) {
      perror("ERRO em pthread_create");
      exit(EXIT_FAILURE);
    }
  }

  int resultado[N];
  for (int i = 0; i < N; i++) {
    pthread_join(threads[i], NULL);
    resultado[i] = args[i].resultado;
  }

  printf("Matriz:\n");
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      printf("%d ", matriz[i][j]);
    }
    printf("\n");
  }

  printf("\nVetor:\n");
  for (int i = 0; i < N; i++) {
    printf("%d\n", vetor[i]);
  }

  printf("\nResultado: ");
  for (int i = 0; i < N; i++) {
    printf("%d ", resultado[i]);
  }

  return 0;
}


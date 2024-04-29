#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct thread_data {
  int *linha_matriz;
  int *vetor;
  int *resultado;
  int colunas;
  int indice;
};

int** alocar_matriz(int linhas, int colunas){
  int** matriz;
  matriz = (int**)malloc(sizeof(int*)*linhas);
  for (int i = 0; i < linhas; i++) {
    matriz[i] = (int*)malloc(sizeof(int)*colunas);
  }
  return matriz;
}

void inserir_valores(int** matriz, int* vetor, int linhas, int colunas){
  int num;
  printf("\nInsira os valores para os elementos da matriz:\n");
  for (int i = 0; i < linhas; i++){
    for (int j = 0; j < colunas; j++){
      printf("matriz[%d][%d]:", i, j);
      scanf("%d",&num);
      matriz[i][j] = num;
    }
  }

  printf("\nInsira os valores para os elementos do vetor:\n");
  for (int i = 0; i < colunas; i++){
    printf("vetor[%d]:", i);
    scanf("%d",&num);
    vetor[i] = num;
  }
}

void *thread_func(void *arg){
  struct thread_data *data = (struct thread_data *)arg;

  for (int i = 0; i < data->colunas; i++){
    data->resultado[data->indice] += data->linha_matriz[i]*data->vetor[i];
    //printf("data: %d\n",data->resultado[data->indice]);
  }

  return NULL;
}

int main(void){
  int linhas, colunas;
  int **matriz;
  int *vetor;
  int *resultado;matriz = (int**)malloc(sizeof(int*)*linhas);
for (int i = 0; i < linhas; i++) {
  matriz[i] = (int*)malloc(sizeof(int)*colunas);
}

  printf("Informe o numero de linhas da matriz: ");
  scanf("%d",&linhas);
  printf("Informe o numero de colunas da matriz: ");
  scanf("%d",&colunas);

  matriz = alocar_matriz(linhas, colunas);

  vetor = (int*)malloc(sizeof(int)*colunas);

  resultado = (int*)malloc(sizeof(int)*linhas);

  inserir_valores(matriz, vetor, linhas, colunas);

  pthread_t *threads;
  threads = (pthread_t*)malloc(sizeof(pthread_t)*linhas);

  struct thread_data *data;
  data = (struct thread_data*)malloc(sizeof(struct thread_data)*linhas);

  for (int i = 0; i < linhas; i++){
    data[i].linha_matriz = matriz[i];
    data[i].vetor = vetor;
    data[i].resultado = resultado;
    data[i].colunas = colunas;
    data[i].indice = i;
    pthread_create(&threads[i], NULL, thread_func, &data[i]);
  }

  for (int i = 0; i < linhas; i++){
    pthread_join(threads[i], NULL);
  }

  printf("\nMatriz:\n");
  for (int i = 0; i < linhas; i++) {
    for (int j = 0; j < linhas; j++) {
      printf("%d ", matriz[i][j]);
    }
    printf("\n");
  }

  printf("\nVetor:\n");
  for (int i = 0; i < linhas; i++) {
    printf("%d\n", vetor[i]);
  }
  printf("\nResultado: \n");
    for (int j = 0; j < linhas; j++){
        printf("%d \n", resultado[j]);
    }
  return 0;
}

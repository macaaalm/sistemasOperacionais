#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// tipo de dado "thread_data" para armazenar dados enviados para threads
struct thread_data {
    int *linha_matriz;
    int *vetor;
    int *resultado;
    int colunas;
    int indice;
};

// alocar memoria dinamicamente para matriz
int** alocar_matriz(int linhas, int colunas){
    int** matriz;
    // alocar memoria para linhas da matriz (vetores de inteiros)
    matriz = (int**)malloc(sizeof(int*)*linhas);
    for (int i = 0; i < linhas; i++){
        // alocar memoria para colunas da matriz (inteiros), que sao armazenados dentro do vetor de cada linha
        matriz[i] = (int*)malloc(sizeof(int)*colunas);
    }
    return matriz;
}

// funcao para inserir valores para os elementos da matriz e do vetor
void inserir_valores(int** matriz, int* vetor, int linhas, int colunas){
    int num;

    printf("\nInsira os valores para os elementos da matriz:\n");
    for (int i = 0; i < linhas; i++){
        for (int j = 0; j < colunas; j++){
            printf("matriz[%d][%d]: ", i, j);
            scanf("%d",&num);
            matriz[i][j] = num;
        }
    }

    printf("\nInsira os valores para os elementos do vetor:\n");
    for (int i = 0; i < colunas; i++){
        printf("vetor[%d]: ", i);
        scanf("%d",&num);
        vetor[i] = num;
    }
}

// funcao que a thread executara
void *thread_func(void *arg){
    struct thread_data *data = (struct thread_data *)arg;

    // calculo do elemento[data->indice] do vetor resultado
    for (int i = 0; i < data->colunas; i++){
        data->resultado[data->indice] += data->linha_matriz[i]*data->vetor[i];
    }

    return NULL;
}

int main(void){
    // declaracao de veriaveis
    int linhas, colunas;
    int **matriz;
    int *vetor;
    int *resultado;

    // leitura do input do usuario
    printf("Informe o numero de linhas da matriz: ");
    scanf("%d",&linhas);
    printf("Informe o numero de colunas da matriz: ");
    scanf("%d",&colunas);

    // alocar memoria dinamicamente para as variaveis: matriz, vetor e resultado
    matriz = alocar_matriz(linhas, colunas);

    vetor = (int*)malloc(sizeof(int)*colunas);

    resultado = (int*)malloc(sizeof(int)*linhas);

    // receber input do usuario
    inserir_valores(matriz, vetor, linhas, colunas);

    // criar um vetor de threads (utilizando ponteiro)
    pthread_t *threads;
    // alocar memoria dinamicamente para o vetor de threads
    threads = (pthread_t*)malloc(sizeof(pthread_t)*linhas);

    // criar um vetor do tipo de dado "thread_data"
    struct thread_data *data;
    // alocar memoria dinamicamente para o vetor de "thread_data", uma variavel "thread_data" para cada thread criada
    data = (struct thread_data*)malloc(sizeof(struct thread_data)*linhas);

    // criar threads, quantidade de threads = numero de linhas da matriz (uma thread para calcular cada elemento do vetor "resultado")
    for (int i = 0; i < linhas; i++){
        // atribuir valores para data[i], que sera utilizado pela threada[i]
        data[i].linha_matriz = matriz[i];
        data[i].vetor = vetor;
        data[i].resultado = resultado;
        data[i].colunas = colunas;
        data[i].indice = i;
        pthread_create(&threads[i], NULL, thread_func, &data[i]);
    }

    // esperar todas as threads terminarem a execucao
    for (int i = 0; i < linhas; i++){
        pthread_join(threads[i], NULL);
    }

    // imprimir valores da matriz, vetor e resultado para o usuario

    printf("\nMatriz:\n");
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }

    printf("\nVetor:\n");
    for (int i = 0; i < colunas; i++) {
        printf("%d\n", vetor[i]);
    }

    printf("\nResultado: \n");
    for (int j = 0; j < linhas; j++){
        printf("%d \n", resultado[j]);
    }

    return 0;
}

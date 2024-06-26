#include <stdio.h>
#include <stdlib.h>

// tipo de dado para armazenar tempo e direcao para cada pessoa
struct Pessoa {
  int tempo;
  int direcao;
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
  }
  for (i = 0; i < qtd_pessoas; i++) {
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
  while (indice0 < qtd_0 || indice1 < qtd_1){
    // se nao houver pessoas na fila 1
    if (indice0 < qtd_0 && indice1 >= qtd_1){
      tempo = escada_direcao(fila0, qtd_0, tempo, ptr0);
    // se nao houver pessoas na fila 0
    } else if (indice0 >= qtd_0 && indice1 < qtd_1){ 
      tempo = escada_direcao(fila1, qtd_1, tempo, ptr1);
    // se houver pessoas em ambas as filas
    } else{
      // se tempo da pessoa no topo da fila0 for menor que o tempo no topo da fila1
      if (fila0[indice0].tempo < fila1[indice1].tempo){
        // se pessoa no topo da fila0 chegou com a escada rolante parada
        if (tempo < fila0[indice0].tempo){
          tempo = fila0[indice0].tempo;
        }
        tempo = escada_direcao(fila0, qtd_0, tempo, ptr0);
      // se tempo da pessoa no topo da fila1 for menor que o tempo no topo da fila0
      } else{
        // se pessoa no topo da fila1 chegou com a escada rolante parada
        if (tempo < fila1[indice1].tempo){
          tempo = fila1[indice1].tempo;
        }
        tempo = escada_direcao(fila1, qtd_1, tempo, ptr1);
      }
    }
  }

  // imprimir tempo total
  printf("%d\n", tempo);
  
  return 0;
}

#include <stdio.h>
#include <stdlib.h>

struct Pessoa {
  int tempo;
  int direcao;
};

int direcao (struct Pessoa pessoas[], int direcao0, int tempo){
  int t = tempo;
  for (int i = 0; i < direcao0; i++){
    if (pessoas[i].tempo <= t+10){
      t = pessoas[i].tempo;
    } else{
      return t+10;
    }
  }
  printf("%d\n", 2);
  return t+10;
}

int main(void) {
  int qtd_pessoas, i, direcao0 = 0, direcao1 = 0;
  FILE * arquivo;

  arquivo = fopen ("teste.txt", "r");
  fscanf(arquivo, "%d", &qtd_pessoas);
  struct Pessoa pessoas[qtd_pessoas];
  for (i = 0; i < qtd_pessoas; i++) {
    fscanf(arquivo, "%d %d", &pessoas[i].tempo, &pessoas[i].direcao);
  }
  for (i = 0; i < qtd_pessoas; i++) {
    if (pessoas[i].direcao == 0){
      direcao0++;
    } else{
      direcao1++;
    }
    printf("%d %d\n", pessoas[i].tempo, pessoas[i].direcao);
  }

  printf("Tempo final: %d", direcao(pessoas, direcao0, 5));
  printf("Pessoas na direcao 0: %d\n", direcao0);
  printf("Pessoas na direcao 1: %d\n", direcao1);
  
  return 0;
}

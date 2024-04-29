# ATIVIDADE 4
# EXERCÍCIO  – MULTIPLICAÇÃO MATRIZ-VETOR

## Alunos:
* Eduardo Honorio Friaca - RA: 10408959
* Matheus Marcal Ramos de Oliveira - RA: 10409001
* Pedro Akira Cardoso Toma - RA: 10390171

## A Figura mostra o exemplo da multiplicação matriz-vetor:

![image](https://github.com/macaaalm/sistemasOperacionais/assets/113950201/00c568fb-ee66-4fe9-9f3e-623118d6e165)

## Construa uma solução utilizando pthreads para resolver o problema da multiplicação matriz-vetor

## Implementação 
###  `pthread_matrizvetor.c`
Primeiramente, recebemos a entrada do usuário para as dimensões da matriz. Alocamos dinamicamente espaço na memória para a matriz, vetor e o resultado (outro vetor) utilizando ponteiros e a função `malloc()`. Em seguida, solicitamos ao usuário que insira os valores para os elementos da matriz e do vetor. Para preparar o uso de threads, criamos um vetor de threads (também alocado dinamicamente) e um vetor de estruturas "thread_data", cada uma associada a um elemento a ser calculado no vetor "resultado".

Antes de criar cada thread, foram atribuídos valores que serão passados como parâmetros, incluindo a linha da matriz (vetor), o vetor, o resultado (vetor), o número de colunas (int) e o índice (int). O número de colunas controlará o loop for para calcular um elemento do resultado, enquanto o índice determinará qual elemento do resultado armazenará o valor calculado.

A função `thread_func` implementa a operação realizada por cada thread do programa. Para cada elemento no vetor e na linha da matriz passada como argumento, do índice 0 até a quantidade de colunas menos um, é realizado o cálculo da multiplicação desses valores. O resultado é então somado ao valor do elemento no vetor `resultado[data->indice]`. Essa função é responsável por calcular os elementos individuais do vetor resultado, aproveitando a concorrência proporcionada pelo uso de threads.

Utilizando a função `pthread_create`, todas as threads a serem utilizadas foram criadas. Em seguida, ao empregar a função `pthread_join` para cada thread, o programa espera que todas elas terminem a execução antes de prosseguir.

Ao final, a matriz, o vetor e o vetor "resultado" serão mostrados ao usuário, apresentando os resultados da operação de multiplicação matriz-vetor realizada de forma concorrente utilizando threads.

## Como testar o código?

### Passo 1)
É necessário compilar o código com a flag `pthread` para indicar ao compilador que o código irá utilizar funcionalidades de threads da biblioteca pthread (POSIX Threads), dessa forma executamos o seguinte comando `gcc pthread_matrizvetor.c -o pthreadCompilado -lpthread`:

![image](https://github.com/macaaalm/sistemasOperacionais/assets/113950201/fb0e06a0-eeb5-4612-9b53-b48fc467247d)

### Passo 2)
Após a compilação, utilizamos o comando `./` para rodar o código compilado, no nosso caso utilizaremos `./pthreadCompilado`:

![image](https://github.com/macaaalm/sistemasOperacionais/assets/113950201/e0d9b156-3179-4110-81ec-776e07ccd3fd)

### Passo 3)
Com o código sendo executado, será pedido o número de linhas e colunas desejadas para a matriz que iremos multiplicar, portanto, informaremos de acordo com o exemplo que fizemos (uma matriz 3 por 3): 

![image](https://github.com/macaaalm/sistemasOperacionais/assets/113950201/00f548b2-8f9e-4b02-8d4f-a57007807a1f)

### Passo 4)
Logo em seguida será pedido para inserir os valores da matriz, portanto, iremos inserir os valores do exemplo que fizemos:

![image](https://github.com/macaaalm/sistemasOperacionais/assets/113950201/03c009eb-507a-4c70-a6a3-64e19241f493)

### Passo 5)
Alocando os devidos elementos da matriz, o programa pedirá para inserir os elementos do vetor, vamos inserir os valores do exemplo que fizemos:

![image](https://github.com/macaaalm/sistemasOperacionais/assets/113950201/481a2586-e85c-4323-9216-0fe3830b643c)

### Passo 6)
Após todos esses passos, será mostrado a matriz, o vetor e o resultado final da multiplicação entre ambos:

![image](https://github.com/macaaalm/sistemasOperacionais/assets/113950201/3472e2be-874b-4d5d-aa9f-6ff237a95981)




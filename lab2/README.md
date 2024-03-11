# EXERCÍCIO 1 – COMUNICAÇÃO ENTRE PROCESSOS 

### Considere o seguinte trecho de código na linguagem C:
![image](https://github.com/macaaalm/sistemasOperacionais/assets/113950201/96f295f4-3843-4e8b-9fe5-9c2fd9692a3e)

### Você é capaz de identificar os trechos executados por pai e filho?

A função fork, por duplicar um processo em pai e filho, retorna um Process ID (PID) diferente para os dois processos. Portanto, é possível identificar quem é quem pelo PID, sendo o filho igual a 0 e o pai maior que 0, caso menor que 0 o fork deu algum erro.

No código acima o processo pai é o processo principal já sendo executado, porém na linha 11 a função fork foi chamada e o processo foi duplicado e a paritr do PID podemos notar quando será executado pai e filho. Nesse caso, filho será executado na linha 16 à 19 e pai na linha 20 à 25.


### Considere ainda o exemplo a seguir:
![image](https://github.com/macaaalm/sistemasOperacionais/assets/113950201/c271cdb4-9c9a-43a4-904e-397dc34a4d20)

### Quantos processos serão criados?

A função fork(), tem o objetivo de duplicar os processos, logo em sua primeira chamada, o processo pai P0 cria o filho P1. 
A partir da segunda chamada, o processo pai P0 cria mais um filho P2 e o processo filho P1 cria outro processo filho P3.
Já na terceira chamada cada um dos processos criados anteriormente criam um processo filho cada, gerando P4, P5, P6 e P7.
Seguindo a lógica a seguir:

![image](https://github.com/macaaalm/sistemasOperacionais/assets/113950201/fb4f96e0-77af-45f3-a236-fc98d7944916)

Dessa forma, o total de processos será de 8, seguindo também o cálculo de 2^n, nesse caso 2^3 = 8.

### EXERCÍCIO: Construa um exemplo, na linguagem C, onde os processos pai e filho trocam algum tipo de mensagem.

Usando o fork-question-1.c disponibilizado pelo professor, rodamos na AWS e esse foi o resultado:

![image](https://github.com/macaaalm/sistemasOperacionais/assets/113950201/a7d8b490-5efc-4f52-a64c-d027c2ab30d7)

Dessa forma, adaptamos o código para que houvesse a comunicação entre processos de pai e filho. Ao pesquisarmos sobre IPC - Inter-Process Communication, o método de pipeline foi o escolhido para ser utilizado, tendo como papel manusear uma mesma área da memória principal para ambos pai e filho. 
A sua leitura é feita pelo file descriptor na posição 0, e a sua escrita na posição 1. Utilizando 3 parâmetros, o primeiro da condição de escrita/leitura (1 ou 0), o segundo é o endereço do buffer que contém os dados escritos ou a serem escritos, e o terceiro parâmentro define o tamanho do buffer.
Logo, o código abaixo foi desenvolvido dentro da AWS:

![image](https://github.com/macaaalm/sistemasOperacionais/assets/113950201/6c0c3379-aa8d-4d77-a892-d93149e8d583)

Tendo como resultado o mesmo valor de value para os dois processos:

![image](https://github.com/macaaalm/sistemasOperacionais/assets/113950201/bd69ecdf-d6bb-4ac2-aa3c-c97e12c6d9be)


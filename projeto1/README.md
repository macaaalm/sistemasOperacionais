# PROJETO 1
# Problema E - Escada Rolante

## Alunos:
* Eduardo Honorio Friaca - RA: 10408959
* Matheus Marcal Ramos de Oliveira - RA: 10409001
* Pedro Akira Cardoso Toma - RA: 10390171

### Problema implementado com Threads: 

  A implementação do problema com threads coemça com a criação de variáveis globais, sendo elas 'mutex', 'variavel condicional' e 'vez'. A variável vez armazenará o valor para decidir qual thread irá ser executada. Dois tipos de estrutura de dados serão utilizados: 'Pessoa', que armazenará tempo e direção de cada pessoa, e 'thread_data', que irá as informações enviadas para as threads. 

  A função 'escada_direcao' simula um ciclo da escada rolante em uma determinada direção (0 ou 1), e itera sobre as pessoas na fila e calcula o tempo necessário para que todas as pessoas da fila atual utilizem a escada naquele ciclo. A função 'thread_func' é a função que cada thread executará, ela controla o acesso concorrente à escada, garantindo que apenas uma thread execute de cada vez. As threads aguardam sua vez de acordo com a variável vez e utilizam a variável condicional para esperar ou serem notificadas de que é sua vez de executar. 

  Por fim, a função main irá ler os dados de um arquivo (entrada.txt), criar as filas de pessoas com base na direção em que elas estão se movendo, inicializar as variáveis e estruturas necessárias, criar duas threads (uma para cada direção da escada) e aguardar a conclusão da execução das threads. Após isso, imprime o tempo total de utilização da escada.


### Problema implementado com Processos: 

  A implementação do problema com processos utiliza uma estrutura de dado 'Pessoa' que armazenará tempo e direção de cada pessoa. A função 'escada_direcao', assim como nas threads, simula um ciclo da escada rolante em uma determinada direção (0 ou 1), e itera sobre as pessoas na fila e calcula o tempo necessário para que todas as pessoas da fila atual utilizem a escada naquele ciclo. Já a função main irá tanto ler os dados do arquivo "entrada.txt" quanto utilizará fork() para criar os processos necessários para a execução do programa, nesse caso, o processo filho será criado e ambos os processos (pai e filho) utilizam memória compartilhada para armazenar informações sobre o uso da escada rolante, como o tempo atual, os índices das filas e a direção atual da escada.

  Os processos simulam o uso da escada rolante para uma direção específica (processo filho sempre na direção 0, e processo pai sempre na direção 1), utilizam um loop para percorrer a fila correspondente (fila0 ou fila1) e atualiza o tempo de uso da escada conforme as pessoas a utilizam. Durante o loop, utiliza "busy waiting" para esperar sua vez de executar na escada rolante e após percorrer toda a fila em uma direção, verifica se ainda há pessoas na fila oposta, se houver, muda a direção da escada para permitir que essas pessoas também a utilizem. O processo pai aguarda o término do processo filho, imprime o tempo total de uso da escada rolante e finaliza o processo.

### Perguntas: 

#### 1. Qual a estratégia que você utilizou para evitar que duas pessoas acessem a escada rolante ao mesmo tempo em cada abordagem?




#### 2. Como garantir que somente uma das direções está ativa de cada vez em cada uma das abordagens?

##### Em Threads:

Ao utilizar a variável 'vez' para decidir qual direção deve ser executada primeiro. Uma variável condicional (`lock`) é utilizada em conjunto com o mutex para garantir que apenas uma pessoa por vez, em uma direção específica, tenha acesso ao código que calcula o tempo de uso da escada rolante. Isso significa que as pessoas em direções diferentes aguardam a finalização do uso da escada pela direção atual antes de acessá-la.

#### Em Processos:

No código, além da mesma variável 'vez', é adotada a técnica de "busy waiting" para coordenar o acesso à escada rolante entre os processos. Isso significa que o processo que não está na vez de utilizar a escada fica em um loop `while`, aguardando até que seja sua vez de executar. Essa abordagem garante que apenas um processo por vez, em cada direção, evitando acesso simultâneo e garantindo uma utilização ordenada e segura do recurso.

#### 3. Discorra sobre as diferenças entre as implementações utilizando threads e processos e diga qual foi mais eficiente na solução do problema, justificando sua resposta.

A abordagem com threads é mais eficiente devido à sua capacidade de controlar o acesso à escada rolante de forma mais precisa. Utilizando uma variável condicional, ela assegura que uma thread em espera só retome sua execução quando a thread ativa sinaliza. Isso implica que apenas uma thread está realmente em atividade, ou seja, consumindo recursos de processamento, durante sua vez de utilizar a escada.

Por outro lado, no caso dos processos, ambos os processos estão sempre ativos, mesmo que um deles esteja aguardando sua vez de utilizar a escada. Embora uma variável de controle impeça que o processo inativo manipule os dados compartilhados, ainda há consumo de recursos de processamento durante esse período de espera. Isso pode resultar em um uso menos eficiente dos recursos do sistema, uma vez que ambos os processos estão constantemente em execução.

### Testes pertinentes

### E_3 
Entrada pequena básica: 

![image](https://github.com/macaaalm/sistemasOperacionais/assets/113950201/c813f6bd-341e-4704-9c3b-acd133546cd7)

Resultado com Threads:

![image](https://github.com/macaaalm/sistemasOperacionais/assets/113950201/d9a04726-4c20-4217-b450-e8639328be0c)

Resultado com Processos:

![image](https://github.com/macaaalm/sistemasOperacionais/assets/113950201/d226ba59-c4aa-455b-9bc0-7fe8d054d98b)

Resultado esperado:

![image](https://github.com/macaaalm/sistemasOperacionais/assets/113950201/b6dfbd49-72ad-4132-9123-76974aa05a61)


### E_8 
Entrada pequena mudando direção mais aleatoriamente: 

![image](https://github.com/macaaalm/sistemasOperacionais/assets/113950201/1e7b738f-c101-4fe2-be3b-b83cef1bbbb0)

Resultado com Threads:

![image](https://github.com/macaaalm/sistemasOperacionais/assets/113950201/b57d25b0-5f38-4e1f-abd5-11c5d7f707c5)

Resultado com Processos:

![image](https://github.com/macaaalm/sistemasOperacionais/assets/113950201/65fb25e2-1f16-4f34-982a-da50bca98eca)

Resultado esperado:

![image](https://github.com/macaaalm/sistemasOperacionais/assets/113950201/c4ca9da5-b25c-4c28-a51d-a97479108a8f)


### E_12 
Entrada maior mudando direção mais aleatoriamente: 

![image](https://github.com/macaaalm/sistemasOperacionais/assets/113950201/78ee8995-308d-4aa2-9556-4ce893bf6e0a)

Resultado com Threads:

![image](https://github.com/macaaalm/sistemasOperacionais/assets/113950201/d3ed835c-8f98-4c35-92bf-6144464e43c5)

Resultado com Processos:

![image](https://github.com/macaaalm/sistemasOperacionais/assets/113950201/68203b3e-e1e5-4126-9366-59b8939188cc)

Resultado esperado:

![image](https://github.com/macaaalm/sistemasOperacionais/assets/113950201/84a8e343-0ce8-4a2a-ac04-3ba5d00e7a0c)


### E_24 
Exemplo de uma das maiores entradas: 

![image](https://github.com/macaaalm/sistemasOperacionais/assets/113950201/f17442bb-0292-4fd1-b8b3-442c66692739)

Resultado com Threads:

![image](https://github.com/macaaalm/sistemasOperacionais/assets/113950201/d5dd5707-87f6-408f-8659-69fcc62a4ad4)

Resultado com Processos:

![image](https://github.com/macaaalm/sistemasOperacionais/assets/113950201/3ad053b0-7add-4d93-b7c9-b334145e48c9)

Resultado esperado:

![image](https://github.com/macaaalm/sistemasOperacionais/assets/113950201/cb9c5295-6874-45ab-a518-166ede54698b)


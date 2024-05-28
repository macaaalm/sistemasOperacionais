# PROJETO 1
# Problema E - Escada Rolante

## Alunos:
* Eduardo Honorio Friaca - RA: 10408959
* Matheus Marcal Ramos de Oliveira - RA: 10409001
* Pedro Akira Cardoso Toma - RA: 10390171

### Como o programa funciona?
Pensando no problema inical de acesso indevido aos saldos e transferências das contas por duas threads, causando inconsistência no resultado em si. Por isso, criamos dois mutex, visando imposibilitar que as transferências acessem o saldo das duas contas ao mesmo tempo, para que tenha uma garantia de que as contas possam ser acessadas somente por uma thread, dessa forma impedindo que alguma conta possa passar a ter saldo negativo.

Inicializamos cada conta com valores fixos e definimos um valor de tranferência também fixo. Em um loop for, criamos cem threads, que representam as tranferências realizadas entre as contas criadas, podendo variar em sua ordem de que recebe e quem transfere (representado pelo if de divisores de 5, para ocorrer 20 tranferências com ordem trocada).

### Como executar o programa?
Utilizamos a plataforma AWS Academy para realizar e rodar o projeto, dessa forma:

1) Depois de baixar o programa ou copiá-lo para um arquivo .c, será necessário compilar o código para que possa ser executado, utilizando o comando `gcc projeto2.c -o projeto2`: 

![image](https://github.com/macaaalm/sistemasOperacionais/assets/113950201/47177f2b-932b-4f85-a4d4-2bf8605fc357)

2) Após compilação, utilizar o comando `./` para rodar o programa, no nosso caso será `./projeto2`:

![image](https://github.com/macaaalm/sistemasOperacionais/assets/113950201/a19b2dc9-9dee-44fc-b180-7f404bb34d34)

3)  Ao rodar o programa, será possível ver as saídas de como as transações estão sendo executadas:

![image](https://github.com/macaaalm/sistemasOperacionais/assets/113950201/3d4e2cca-bf54-47d9-a1d9-f1603bc77065)

4) O saldo final irá aparecer no final da execução do programa:

![image](https://github.com/macaaalm/sistemasOperacionais/assets/113950201/f52dc766-6f0d-4ae8-b0df-958f721dec39)



# EXERCÍCIO 1 – COMUNICAÇÃO ENTRE PROCESSOS 

### Considere o seguinte trecho de código na linguagem C:
![image](https://github.com/macaaalm/sistemasOperacionais/assets/113950201/96f295f4-3843-4e8b-9fe5-9c2fd9692a3e)

### Você é capaz de identificar os trechos executados por pai e filho?

A função fork, por duplicar um processo em pai e filho, retorna um Process ID (PID) diferente para os dois processos. Portanto, é possível identificar quem é quem pelo PID, sendo o filho igual a 0 e o pai maior que 0, caso menor que 0 o fork deu algum erro.

No código acima o processo pai é o processo principal já sendo executado, porém na linha 11 a função fork foi chamada e o processo foi duplicado e a paritr do PID podemos notar quando será executado pai e filho. Nesse caso, filho será executado na linha 16 à 19 e pai na linha 20 à 25.


### Considere ainda o exemplo a seguir:
![image](https://github.com/macaaalm/sistemasOperacionais/assets/113950201/c271cdb4-9c9a-43a4-904e-397dc34a4d20)

### Quantos processos serão criados?
![image](https://github.com/macaaalm/sistemasOperacionais/assets/113950201/fb4f96e0-77af-45f3-a236-fc98d7944916)

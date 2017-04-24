## Portugol - Uma linguagem algorítmica em Português 

### Introdução 

Linguagem desenvolvida com inspiração em C, em português, para facilitar o ensino de algoritmos a alunos iniciando em programação. 

O projeto iniciou em 23/Abril/2009, e inaugura sua participação no github no aniversário de 8 anos.

Uma das características marcantes do compilador Portugol é a geração de um bytecode semelhante à linguagem Assembly, chamada de quádruplas. É uma ótima opção para ensinar o básico de Assembly, como se converte código, como ficam os laços e atribuições.

A linguagem é compilada em três passos:

1. Análise léxica e sintática.
2. Análise sintática, de escopo e de indentação
3. Análise semântica e geração de código.

### Comandos

Os comandos válidos na linguagem Portugol são:

* se ... entao ... senao : condição típica para decisões
* inicio ... fim : marca um bloco de comandos subordinados
* imprima : imprime uma mensagem ou variável na saída padrão
* leia : lê um valor da entrada padrão
* enquanto : comando para laço condicional
* para : comando para laço com inicialização, condição e incremento
* aborte : termina abruptamente o programa
* retorne : retorna de uma função para a função chamadora
* saia : termina o programa com um código de sucesso/erro

### Tipos de dados

* inteiro : valores inteiros com sinal (int)
* real : valores reais com sinal (float)
* texto : cadeia de caracteres (string, char \*)
* nada : ponteiro para variável sem tipo (void \*)
* ponteiro : ponteiro para inteiro, real ou texto.

### Expressões e operadores (relacionais e lógicos)

* atribuição: c = 0; 
* incremento: c++; ++c; (pós e préfixado)
* decremento: c--; --c; (pós e préfixado)
* apontador: \*p = 0; (dereferenciador de ponteiros)
* endereço: p = & c; (endereço de uma variável)
* Aritméticas: - (unário), +, -, \*, /, e % (módulo, ou resto da divisão)
* Relacionais: >=, <=, ==, !=, > e <
* Lógicas: e, ou e nao (sem acentos)

### Opções mais avançadas

* tipo funcao(arg1, arg2, arg3) :  pode-se declarar funções com até 3 argumentos (\*) 
* externa : define uma função externa
* define : define uma macro
* \#debug : se ativado, o compilador imprimirá a árvore sintática durante a compilação
* \_ARVORE: ativado, liga impressão da árvore sintática
* \_TABELA: ativado, liga a impressão da tabela de símbolos

Nota: (\*) limite de 3 argumentos nas funções imposto no momento, mas suficiente para o estudo dos algoritmos básicos.

### Constantes e miscelâneas

* Números podem ser escritos em notação científica
* Comentários são feitos com o símbolo // e são apenas de linha
* Strings são entre "aspas" (duplas)
* Formato para imprimir e ler: %d, %f ou %s (inteiros, reais e _strings_) com uso de modificadores

* inc, dec, incpos, incpre decpos, decpre
* pont upont uend pattrib
* ponti pontr ponts
* indent intcon realcon textocon principal

### Prioridade dos operadores

Os operadores são processados na seguinte ordem (do menos prioritário para o de maior prioridade):

* incremento pós-fixado
* ou
* e
* nao
* operadores relacionais
* atribuição
* adição e subtração
* multiplicação, divisão e módulo
* incremento pré-fixado
* dereferenciamento de ponteiros
* endereço de variáveis

### Exemplos

Abaixo um exemplo de código em sua correta indentação:

* Extensão utilizada pelo Portugol: **ptg**
* Arquivo: **teste.ptg**

```
inteiro principal(nada)
inicio;

    real o;
    inteiro u;

    imprima("digite um numero %f\n", o);
    leia("%f", o);
    se(o<0.0) entao
    inicio;
        imprima("%s\n","erro: numero negativo!");
        saia(1);
    fim;
    senao
        se(o==0.0) entao
        inicio;
            imprima("%f\n", 1.0); // Comentario de linha
            saia(0);
        fim;

    para(u=1; u<5; u=u+1)
    inicio;
        imprima("%d\n", u);
    fim;
    retorne 1;
fim;
```

### Syntax highlighting

Se você usa o editor _Kate_ (do _KDE_) ou compatíveis com o _XML_ de _syntax highlighting_, basta usar o seguinte comando para ver o código colorido:

```
$ cp ptg.xml /home/user/.kde/share/apps/katepart/syntax/
```

### Autor e Copyright

* Autor: Prof. Dr. Ruben Carlo Benante
* Email: rcb@upe.br
* Data: 2009-04-23 até data corrente (autom. atualizado)
* Licensa: GNU/GPL v2.0


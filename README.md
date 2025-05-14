# Corta_Gastos 💵💸
Repositório para o projeto Corta_Gasto que se baseia em um código em C onde o usuário pode gerir com diversas funções os seus gastos.

 **Características do Programa** 🦾

 * Código desenvolvido em linguagem C; 🖥️
 * A estrutura de dados escolhida foi a lista duplamente encadeada (Fila); 🔗
 * O programa é acessado através do terminal; ⌨️
 * Ele tem CRUD + duas funções extras (Procurar Gastos Específicos e Mostrar Dados Estatísticos); 📊
 * O programa ainda tem duas funções de Carregar e Salvar lista para que quando for fechado e reaberto, os dados sejam mantidos em um arquivo de texto chamado `banco_dados.txt`; 💾

 **Estruturas de Dados** 🎲

 ```c
 typedef struct Gasto {
     char nome[25];
     float valor;
 } Gasto;
 ```
 > Estrutura que representa uma despesa, contendo o nome (limite de 24 caracteres) e o valor correspondente.

 ```c
 typedef struct No {
     Gasto gasto;
     struct No *anterior;
     struct No *proximo;
 } No;
 ```
 > Cada nó da lista representa um gasto e possui ponteiros para o elemento anterior e o seguinte, caracterizando a lista duplamente encadeada.

 **Funções Principais** ⚖️

 #### `No *criarNo(Gasto gasto)`
 Inicializa um novo nó da lista com os dados de um gasto.

 #### `void inserirGasto(No **inicio, Gasto gasto)`
 Adiciona um novo gasto ao final da lista encadeada.

 #### `void exibirGastos(No *inicio)`
 Percorre a lista e imprime todos os gastos registrados.

 #### `void excluirGasto(No **inicio, char nome[25])`
 Busca e remove o primeiro gasto da lista com o nome fornecido.

 #### `void modificarGasto(No **inicio, Gasto gastomod, char nome[25])`
 Altera os dados de um gasto já existente, identificado pelo seu nome original.

 #### `void mostrarDados(No *inicio)`
 Calcula e exibe:
 - O total de gastos cadastrados;
 - A soma total dos valores;
 - A média dos gastos registrados.

 #### `void procurarGasto(No *inicio, char nome[25])`
 Soma e apresenta os valores de todos os gastos com o nome especificado.

 #### `void salvarGastos(No* inicio)`
 Salva os dados da lista no arquivo `banco_dados.txt`, sobrescrevendo o conteúdo anterior.

 #### `void carregarGastos(No** inicio)`
 Lê os dados do arquivo `banco_dados.txt` e os insere na lista em memória para uso imediato.

 **Função Main 🔢**

 1. Listar todos os gastos cadastrados
 2. Adicionar um novo gasto
 3. Remover um gasto existente
 4. Editar um gasto
 5. Visualizar estatísticas gerais
 6. Buscar gastos por nome
 7. Limpar o terminal
 0. Encerrar a aplicação (com salvamento dos dados)

 **Estrutura do Arquivo de Dados 📂**

 O arquivo `banco_dados.txt` armazena os dados no seguinte formato:  Cada par de linhas representa um gasto.

```
 nome_do_gasto
 valor
 nome_do_gasto
 valor
 ...
```

**Compilação do Projeto 📠**

Para compilar o projeto, utilize o seguinte comando no terminal:

```
gcc main.c -o main
```
Para executar o programa após a compilação:
```
./main
```

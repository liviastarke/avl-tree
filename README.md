# Implementação de Árvore AVL

Este repositório contém:

- Um diário de produção (arquivo txt para anotarmos as decisões tomadas e motivos, que será a base para o relatório do projeto)

- Código fonte (arquivos .c e .h)

- Este README, com os requisitos (feitos e por fazer), divisão de tarefas e links para referência

Para informações detalhadas sobre o desenvolvimento, consultar o diário de produção.

### Compilação

```bash
gcc arvore.c balanceamento.c stack.c -o arvore
```

Ao adicionar a opção -g ao final do comando de compilação se torna possível debugar o código com `gdb arvore`.

## Requisitos

- [x] Inserção (Lívia)

- [x] Remoção (Bruno)

- [x] Busca (Lívia)

- [x] Lógica de chamada de função de autobalanceamento (ambos)

- [x] Rotação simples (Lívia)

- [x] Rotação dupla (Bruno)

- [x] Algoritmo de percurso (Bruno)

- [x] Interface (Bruno)

### Estruturas utilizadas

- [x] File: representa um arquivo com nome, tamanho e extensão.

- [x] Node: representa um nó na árvore, contém um arquivo.

- [x] Stack: uma pilha para algoritmos de percurso na árvore.

## Materiais para referência

[Clear screen](https://www.geeksforgeeks.org/c/clear-console-c-language/)

[Make e makefile](https://www.gnu.org/software/make/manual/make.html)

[CMake](https://cmake.org/cmake/help/latest/guide/tutorial/index.html)


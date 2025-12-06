# Trabalho Prático: Análise Experimental de Algoritmos de Ordenação e Busca

## 1. Descrição do Projeto
Implementação e análise empírica de algoritmos de ordenação O(N²) (Selection, Insertion, Bubble e Bubble Otimizado) e de busca (Sequencial e Binária). O projeto mede Tempo, Comparações e Trocas em diferentes cenários (Aleatório, Crescente, Decrescente) e tamanhos (1.000, 10.000, 100.000).

## 2. Instruções de Compilação

Para compilar o projeto, execute os seguintes comandos no terminal:

```bash
# Compilação do Gerador de Dados
gcc -o codigo/gerador codigo/gerador_dados.c codigo/utils.c -Wall

# Compilação do Teste de Ordenação
gcc -o codigo/ordenacao codigo/ordenacao.c codigo/utils.c -Wall

# Compilação do Teste de Busca
gcc -o codigo/busca codigo/busca.c codigo/utils.c codigo/ordenacao.c -Wall
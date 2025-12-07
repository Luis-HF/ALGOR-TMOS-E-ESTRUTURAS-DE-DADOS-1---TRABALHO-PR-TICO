Trabalho Prático: Análise Experimental de Algoritmos de Ordenação e Busca
1. 🎯 Objetivo do Projeto

Este projeto visa implementar e analisar o desempenho empírico dos algoritmos de ordenação O(N2) (Selection, Insertion, Bubble e Bubble Otimizado) e dos algoritmos de Busca (Sequencial e Binária). O foco é comparar a complexidade teórica com o comportamento real (tempo, trocas e comparações) sob nove diferentes cenários de entrada (3 tamanhos x 3 organizações).

2. 🛠️ Pré-requisitos e Instalação

Para rodar o projeto, você precisa dos seguintes programas instalados:
A. Compilador C

É necessário o GNU Compiler Collection (GCC) para compilar o código-fonte C.
>>sudo apt install build-essential

B. Python e Bibliotecas de Análise

É necessário o Python 3 e as bibliotecas Pandas e Matplotlib para processar os dados coletados (CSV) e gerar os gráficos obrigatórios.
>>pip install pandas matplotlib

3. ⚙️ Instruções de Compilação

Execute os seguintes comandos no terminal, a partir do diretório raiz do projeto, para compilar os três executáveis necessários (todos são salvos na pasta codigo/):

# 1. Compila o Gerador de Dados
>>gcc -o codigo/gerador codigo/gerador.c codigo/utils.c -Wall

# 2. Compila o Teste de Ordenação
>>gcc -o codigo/ordenacao codigo/ordenacao.c codigo/utils.c -Wall

Agora devemos comentar a função main() inteira que está dentro de ordenacao.c para que seja possível compilar corretamente o próximo.

# 3. Compila o Teste de Busca
>>gcc -o codigo/busca codigo/busca.c codigo/ordenacao.c codigo/utils.c -Wall

4. 🚀 Instruções de Execução (Coleta de Dados)

Execute os programas na ordem abaixo para gerar todos os dados de entrada e saída:
mkdir -p dados results
>>./codigo/gerador

>>./codigo/ordenacao

>>./codigo/busca

5. 📊 Geração dos Gráficos e Visualização

Para visualizar os resultados e preparar o Relatório, execute o script Python.
Passo D: Rodar o Script de Geração de Gráficos

Execute o arquivo plot_graphs.py (assumindo que ele está na raiz do projeto):

>>python plot_graphs.py

Resultados Finais

Após a execução do script Python, a pasta resultados/ conterá os arquivos CSV completos e os três gráficos PNG necessários para a análise do relatório.
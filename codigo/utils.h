#ifndef UTILS_H
#define UTILS_H

// Estrutura para armazenar o vetor e as métricas de desempenho
typedef struct {
    int* vetor;
    long long tamanho;
    long long trocas;       // Contador de trocas (swaps)
    long long comparacoes;  // Contador de comparações
    double tempo_ms;        // Tempo de execução em milissegundos
} Resultado;

// Definições de cenários e tamanhos
#define TAMANHO_PEQUENO 1000
#define TAMANHO_MEDIO 10000
#define TAMANHO_GRANDE 100000

// Funções auxiliares
void inicializar_resultado(Resultado* res, long long N);
void liberar_resultado(Resultado* res);
void trocar(int* a, int* b, Resultado* res); // Inclui a contagem de trocas
void copiar_vetor(int* destino, const int* origem, long long N);
int comparar(int a, int b, Resultado* res); // Inclui a contagem de comparações

// Funções de manipulação de arquivo binário
long long ler_vetor_binario(const char* nome_arquivo, int** vetor);
void escrever_vetor_binario(const char* nome_arquivo, const int* vetor, long long N);

#endif
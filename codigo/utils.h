#ifndef UTILS_H
#define UTILS_H

typedef struct {
    int* vetor;
    long long tamanho;
    long long trocas;
    long long comparacoes;
    double tempo_ms;
} Resultado;

#define TAMANHO_PEQUENO 1000
#define TAMANHO_MEDIO 10000
#define TAMANHO_GRANDE 100000

void inicializar_resultado(Resultado* res, long long N);
void liberar_resultado(Resultado* res);
void trocar(int* a, int* b, Resultado* res);
void copiar_vetor(int* destino, const int* origem, long long N);
int comparar(int a, int b, Resultado* res);

long long ler_vetor_binario(const char* nome_arquivo, int** vetor);
void escrever_vetor_binario(const char* nome_arquivo, const int* vetor, long long N);

#endif
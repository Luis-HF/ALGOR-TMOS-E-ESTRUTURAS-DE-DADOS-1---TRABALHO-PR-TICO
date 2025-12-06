#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

// --- Funções de Estrutura e Memória ---

/**
 * Inicializa a estrutura Resultado, alocando memória para o vetor e zerando métricas.
 */
void inicializar_resultado(Resultado* res, long long N) {
    res->tamanho = N;
    res->trocas = 0;
    res->comparacoes = 0;
    res->tempo_ms = 0.0;
    res->vetor = (int*)malloc(N * sizeof(int));
    if (res->vetor == NULL) {
        perror("Erro de alocação de memória para o vetor");
        exit(EXIT_FAILURE);
    }
}

/**
 * Libera a memória alocada para o vetor dentro da estrutura Resultado.
 */
void liberar_resultado(Resultado* res) {
    if (res->vetor != NULL) {
        free(res->vetor);
        res->vetor = NULL;
    }
}

/**
 * Cria uma cópia limpa do vetor original.
 */
void copiar_vetor(int* destino, const int* origem, long long N) {
    for (long long i = 0; i < N; i++) {
        destino[i] = origem[i];
    }
}

// --- Funções de Contagem de Métricas (Cruciais para a Avaliação) ---

/**
 * Realiza a troca de dois elementos e incrementa o contador de trocas.
 * Esta função deve ser usada por todos os algoritmos que realizam swaps.
 */
void trocar(int* a, int* b, Resultado* res) {
    int temp = *a;
    *a = *b;
    *b = temp;
    res->trocas++; // Contagem de Trocas (Swaps)
}

/**
 * Compara dois inteiros. Esta função deve ser usada por todos os algoritmos
 * de ordenação e busca para garantir a contagem precisa de comparações.
 * Retorna: -1 se a < b, 0 se a == b, 1 se a > b.
 */
int comparar(int a, int b, Resultado* res) {
    res->comparacoes++; // Contagem de Comparações
    if (a < b) return -1;
    if (a > b) return 1;
    return 0;
}

// --- Funções de Manipulação de Arquivos Binários ---

/**
 * Lê um vetor de números inteiros de um arquivo binário.
 * Retorna o número de elementos (N) lidos, ou -1 em caso de erro.
 */
long long ler_vetor_binario(const char* nome_arquivo, int** vetor) {
    FILE* arquivo = fopen(nome_arquivo, "rb");
    if (arquivo == NULL) {
        perror("Erro ao abrir arquivo para leitura");
        *vetor = NULL;
        return -1;
    }

    // Calcula o tamanho do arquivo
    fseek(arquivo, 0, SEEK_END);
    long long tamanho_bytes = ftell(arquivo);
    fseek(arquivo, 0, SEEK_SET);

    // Calcula o número de inteiros
    long long N = tamanho_bytes / sizeof(int);

    // Aloca memória para o vetor
    *vetor = (int*)malloc(N * sizeof(int));
    if (*vetor == NULL) {
        perror("Erro de alocação de memória na leitura");
        fclose(arquivo);
        return -1;
    }

    // Lê o vetor do arquivo
    size_t lidos = fread(*vetor, sizeof(int), N, arquivo);
    fclose(arquivo);

    if (lidos != N) {
        fprintf(stderr, "Aviso: Não foi possível ler todos os %lld elementos do arquivo %s.\n", N, nome_arquivo);
        free(*vetor);
        *vetor = NULL;
        return -1;
    }

    return N;
}

/**
 * Escreve um vetor de números inteiros em um arquivo binário.
 */
void escrever_vetor_binario(const char* nome_arquivo, const int* vetor, long long N) {
    FILE* arquivo = fopen(nome_arquivo, "wb");
    if (arquivo == NULL) {
        perror("Erro ao abrir arquivo para escrita");
        return;
    }

    // Escreve o vetor no arquivo binário
    size_t escritos = fwrite(vetor, sizeof(int), N, arquivo);
    fclose(arquivo);

    if (escritos != N) {
        fprintf(stderr, "Aviso: Nem todos os %lld elementos foram escritos no arquivo %s.\n", N, nome_arquivo);
    }
}
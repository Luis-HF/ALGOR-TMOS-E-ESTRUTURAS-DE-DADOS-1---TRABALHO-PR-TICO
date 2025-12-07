#include <stdio.h>
#include <stdlib.h>
#include "utils.h"


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

void liberar_resultado(Resultado* res) {
    if (res->vetor != NULL) {
        free(res->vetor);
        res->vetor = NULL;
    }
}

void copiar_vetor(int* destino, const int* origem, long long N) {
    for (long long i = 0; i < N; i++) {
        destino[i] = origem[i];
    }
}

void trocar(int* a, int* b, Resultado* res) {
    int temp = *a;
    *a = *b;
    *b = temp;
    res->trocas++;
}

int comparar(int a, int b, Resultado* res) {
    res->comparacoes++;
    if (a < b) return -1;
    if (a > b) return 1;
    return 0;
}

long long ler_vetor_binario(const char* nome_arquivo, int** vetor) {
    FILE* arquivo = fopen(nome_arquivo, "rb");
    if (arquivo == NULL) {
        perror("Erro ao abrir arquivo para leitura");
        *vetor = NULL;
        return -1;
    }

    fseek(arquivo, 0, SEEK_END);
    long long tamanho_bytes = ftell(arquivo);
    fseek(arquivo, 0, SEEK_SET);

    long long N = tamanho_bytes / sizeof(int);

    *vetor = (int*)malloc(N * sizeof(int));
    if (*vetor == NULL) {
        perror("Erro de alocação de memória na leitura");
        fclose(arquivo);
        return -1;
    }

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

void escrever_vetor_binario(const char* nome_arquivo, const int* vetor, long long N) {
    FILE* arquivo = fopen(nome_arquivo, "wb");
    if (arquivo == NULL) {
        perror("Erro ao abrir arquivo para escrita");
        return;
    }

    size_t escritos = fwrite(vetor, sizeof(int), N, arquivo);
    fclose(arquivo);

    if (escritos != N) {
        fprintf(stderr, "Aviso: Nem todos os %lld elementos foram escritos no arquivo %s.\n", N, nome_arquivo);
    }
}
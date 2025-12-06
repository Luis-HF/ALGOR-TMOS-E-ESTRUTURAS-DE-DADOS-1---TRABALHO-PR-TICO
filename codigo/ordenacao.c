#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "utils.h"

// --- 1. Algoritmos de Ordenação ---

// Selection Sort (Padrão)
void selection_sort(Resultado* res) {
    long long N = res->tamanho;
    for (long long i = 0; i < N - 1; i++) {
        long long min_idx = i;
        for (long long j = i + 1; j < N; j++) {
            // Conta a comparação
            if (comparar(res->vetor[j], res->vetor[min_idx], res) < 0) { 
                min_idx = j;
            }
        }
        // Troca o elemento encontrado com o primeiro elemento não ordenado
        if (i != min_idx) {
            trocar(&res->vetor[i], &res->vetor[min_idx], res);
        }
    }
}

// Bubble Sort (Padrão)
void bubble_sort(Resultado* res) {
    long long N = res->tamanho;
    for (long long i = 0; i < N - 1; i++) {
        for (long long j = 0; j < N - 1 - i; j++) {
            // Conta a comparação
            if (comparar(res->vetor[j], res->vetor[j + 1], res) > 0) { 
                trocar(&res->vetor[j], &res->vetor[j + 1], res);
            }
        }
    }
}

// Bubble Sort Otimizado
void bubble_sort_otimizado(Resultado* res) {
    long long N = res->tamanho;
    int houve_troca;
    for (long long i = 0; i < N - 1; i++) {
        houve_troca = 0;
        for (long long j = 0; j < N - 1 - i; j++) {
            if (comparar(res->vetor[j], res->vetor[j + 1], res) > 0) {
                trocar(&res->vetor[j], &res->vetor[j + 1], res);
                houve_troca = 1;
            }
        }
        // Interrompe se o vetor estiver ordenado (otimização)
        if (houve_troca == 0) {
            break;
        }
    }
}

// Insertion Sort
void insertion_sort(Resultado* res) {
    long long N = res->tamanho;
    for (long long i = 1; i < N; i++) {
        int chave = res->vetor[i];
        long long j = i - 1;
        
        // Comparações e deslocamentos
        // A comparação aqui é a base do loop 'while'
        while (j >= 0 && comparar(res->vetor[j], chave, res) > 0) {
            // Deslocamento (não é uma troca completa, mas é um movimento de elemento)
            res->vetor[j + 1] = res->vetor[j];
            res->trocas++; // Contabilizando o movimento como "movimentação de elemento"
            j = j - 1;
        }
        res->vetor[j + 1] = chave;
    }
}

// --- 2. Função de Teste e Registro ---

void testar_ordenacao(const char* arq_entrada, const char* arq_saida, void (*algoritmo)(Resultado*), const char* nome_algoritmo, int* vetor_original, long long N) {
    // Aloca e inicializa a estrutura de resultado
    Resultado res;
    inicializar_resultado(&res, N);
    
    // Cria uma cópia do vetor original para que o teste seja limpo
    copiar_vetor(res.vetor, vetor_original, N);

    clock_t inicio = clock();
    algoritmo(&res);
    clock_t fim = clock();

    // Calcula tempo em milissegundos
    res.tempo_ms = ((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000.0;
    
    // Salva as métricas no arquivo CSV
    FILE* saida = fopen(arq_saida, "a");
    if (saida == NULL) {
        perror("Erro ao abrir arquivo de saída");
        liberar_resultado(&res);
        return;
    }

    // Adiciona o nome do arquivo, algoritmo, N, tempo, comparacoes, trocas
    fprintf(saida, "%s;%s;%lld;%.3f;%lld;%lld\n", 
            arq_entrada, nome_algoritmo, N, res.tempo_ms, res.comparacoes, res.trocas);

    fclose(saida);
    liberar_resultado(&res);
}

// --- 3. Função Principal ---

int executar_testes_ordenacao() {
    const char* arquivos[] = {
        "dados/pequeno_aleatorio.bin", "dados/medio_aleatorio.bin", "dados/grande_aleatorio.bin",
        "dados/pequeno_crescente.bin", "dados/medio_crescente.bin", "dados/grande_crescente.bin",
        "dados/pequeno_decrescente.bin", "dados/medio_decrescente.bin", "dados/grande_decrescente.bin"
    };
    int num_arquivos = 9;
    const char* arq_saida = "resultados/metricas_ordenacao.csv";

    // Cria o cabeçalho do arquivo CSV
    FILE* saida = fopen(arq_saida, "w");
    if (saida != NULL) {
        fprintf(saida, "Arquivo;Algoritmo;Tamanho_N;Tempo_ms;Comparacoes;Trocas\n");
        fclose(saida);
    } else {
        perror("Erro ao criar arquivo CSV");
        return 1;
    }

    // Lista de algoritmos a serem testados
    void (*algoritmos[])(Resultado*) = {
        selection_sort, bubble_sort, bubble_sort_otimizado, insertion_sort
    };
    const char* nomes_algoritmos[] = {
        "SelectionSort", "BubbleSort", "BubbleSortOtimizado", "InsertionSort"
    };
    int num_algoritmos = 4;

    for (int i = 0; i < num_arquivos; i++) {
        int* vetor_original = NULL;
        long long N = ler_vetor_binario(arquivos[i], &vetor_original);
        if (vetor_original == NULL) continue;

        printf("Testando arquivo: %s (N=%lld)\n", arquivos[i], N);

        for (int j = 0; j < num_algoritmos; j++) {
            // Testa o algoritmo e registra as métricas
            testar_ordenacao(arquivos[i], arq_saida, algoritmos[j], nomes_algoritmos[j], vetor_original, N);
        }

        free(vetor_original);
    }

    return 0;
}
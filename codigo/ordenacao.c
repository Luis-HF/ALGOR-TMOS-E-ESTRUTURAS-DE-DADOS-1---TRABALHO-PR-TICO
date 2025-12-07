#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "utils.h"

void selection_sort(Resultado* res) {
    long long N = res->tamanho;
    for (long long i = 0; i < N - 1; i++) {
        long long min_idx = i;
        for (long long j = i + 1; j < N; j++) {
            if (comparar(res->vetor[j], res->vetor[min_idx], res) < 0) { 
                min_idx = j;
            }
        }
        if (i != min_idx) {
            trocar(&res->vetor[i], &res->vetor[min_idx], res);
        }
    }
}

void bubble_sort(Resultado* res) {
    long long N = res->tamanho;
    for (long long i = 0; i < N - 1; i++) {
        for (long long j = 0; j < N - 1 - i; j++) {
            if (comparar(res->vetor[j], res->vetor[j + 1], res) > 0) { 
                trocar(&res->vetor[j], &res->vetor[j + 1], res);
            }
        }
    }
}

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
        if (houve_troca == 0) {
            break;
        }
    }
}

void insertion_sort(Resultado* res) {
    long long N = res->tamanho;
    for (long long i = 1; i < N; i++) {
        int chave = res->vetor[i];
        long long j = i - 1;
        while (j >= 0 && comparar(res->vetor[j], chave, res) > 0) {
            res->vetor[j + 1] = res->vetor[j];
            res->trocas++;
            j = j - 1;
        }
        res->vetor[j + 1] = chave;
    }
}

void testar_ordenacao(const char* arq_entrada, const char* arq_saida, void (*algoritmo)(Resultado*), const char* nome_algoritmo, int* vetor_original, long long N) {
    Resultado res;
    inicializar_resultado(&res, N);
    copiar_vetor(res.vetor, vetor_original, N);
    clock_t inicio = clock();
    algoritmo(&res);
    clock_t fim = clock();
    res.tempo_ms = ((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000.0;
    FILE* saida = fopen(arq_saida, "a");
    if (saida == NULL) {
        perror("Erro ao abrir arquivo de saída");
        liberar_resultado(&res);
        return;
    }

    fprintf(saida, "%s;%s;%lld;%.3f;%lld;%lld\n", 
            arq_entrada, nome_algoritmo, N, res.tempo_ms, res.comparacoes, res.trocas);

    fclose(saida);
    liberar_resultado(&res);
}

int executar_testes_ordenacao() {
    const char* arquivos[] = {
        "dados/pequeno_aleatorio.bin", "dados/medio_aleatorio.bin", "dados/grande_aleatorio.bin",
        "dados/pequeno_crescente.bin", "dados/medio_crescente.bin", "dados/grande_crescente.bin",
        "dados/pequeno_decrescente.bin", "dados/medio_decrescente.bin", "dados/grande_decrescente.bin"
    };
    int num_arquivos = 9;
    const char* arq_saida = "resultados/metricas_ordenacao.csv";

    FILE* saida = fopen(arq_saida, "w");
    if (saida != NULL) {
        fprintf(saida, "Arquivo;Algoritmo;Tamanho_N;Tempo_ms;Comparacoes;Trocas\n");
        fclose(saida);
    } else {
        perror("Erro ao criar arquivo CSV");
        return 1;
    }

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
            testar_ordenacao(arquivos[i], arq_saida, algoritmos[j], nomes_algoritmos[j], vetor_original, N);
        }

        free(vetor_original);
    }

    return 0;
}


int main() {
   return executar_testes_ordenacao();
}
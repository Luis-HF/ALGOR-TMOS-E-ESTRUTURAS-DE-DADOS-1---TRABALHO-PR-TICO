#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "utils.h"

void gerar_vetor(int* vetor, long long N, const char* cenario) {
    if (strcmp(cenario, "aleatorio") == 0) {
        srand(time(NULL));
        for (long long i = 0; i < N; i++) {
            vetor[i] = rand() % 1000000;
        }
    } else if (strcmp(cenario, "crescente") == 0) {
        // Crescente (Melhor Caso)
        for (long long i = 0; i < N; i++) {
            vetor[i] = (int)i;
        }
    } else if (strcmp(cenario, "decrescente") == 0) {
        // Decrescente (Pior Caso)
        for (long long i = 0; i < N; i++) {
            vetor[i] = (int)(N - i);
        }
    }
}

int main() {
    long long tamanhos[] = {TAMANHO_PEQUENO, TAMANHO_MEDIO, TAMANHO_GRANDE};
    const char* nomes_tamanhos[] = {"pequeno", "medio", "grande"};
    const char* cenarios[] = {"aleatorio", "crescente", "decrescente"};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            long long N = tamanhos[i];
            const char* nome_tam = nomes_tamanhos[i];
            const char* cenario = cenarios[j];
            
            int* vetor = (int*)malloc(N * sizeof(int));
            if (vetor == NULL) {
                perror("Erro de alocação");
                return 1;
            }

            gerar_vetor(vetor, N, cenario);

            char nome_arquivo[100];
            sprintf(nome_arquivo, "dados/%s_%s.bin", nome_tam, cenario);
            
            escrever_vetor_binario(nome_arquivo, vetor, N);
            printf("Arquivo gerado: %s (N=%lld)\n", nome_arquivo, N);

            free(vetor);
        }
    }

    return 0;
}
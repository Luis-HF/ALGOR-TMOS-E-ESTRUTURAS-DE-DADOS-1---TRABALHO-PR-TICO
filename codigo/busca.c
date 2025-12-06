#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"
#include "ordenacao.h" // Inclui os sorts para ordenar o vetor Grande

// --- 1. Algoritmos de Busca ---

// Busca Sequencial
long long busca_sequencial(Resultado* res, int chave) {
    for (long long i = 0; i < res->tamanho; i++) {
        res->comparacoes++; // Conta a comparação
        if (res->vetor[i] == chave) {
            return i; // Encontrado
        }
    }
    return -1; // Não encontrado
}

// Busca Binária (Requer vetor ordenado)
long long busca_binaria(Resultado* res, int chave) {
    long long esquerda = 0;
    long long direita = res->tamanho - 1;
    
    while (esquerda <= direita) {
        long long meio = esquerda + (direita - esquerda) / 2;
        
        res->comparacoes++; // Conta a comparação na verificação do meio
        if (res->vetor[meio] == chave) {
            return meio; // Encontrado
        }
        
        res->comparacoes++; // Conta a comparação para decidir o lado
        if (res->vetor[meio] < chave) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }
    return -1; // Não encontrado
}

// --- 2. Função de Teste e Registro ---

void testar_busca(const char* arq_saida, void (*algoritmo)(Resultado*), const char* nome_algoritmo, int* vetor_original, long long N, int valor_busca, const char* status_busca, double tempo_ordenacao) {
    Resultado res;
    inicializar_resultado(&res, N);
    copiar_vetor(res.vetor, vetor_original, N);

    clock_t inicio = clock();
    long long indice = busca_sequencial(&res, valor_busca); // Busca
    clock_t fim = clock();

    res.tempo_ms = ((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000.0;
    
    FILE* saida = fopen(arq_saida, "a");
    if (saida == NULL) {
        perror("Erro ao abrir arquivo de saída");
        liberar_resultado(&res);
        return;
    }

    fprintf(saida, "%s;%s;%d;%s;%.3f;%lld;%.3f\n", 
            nome_algoritmo, 
            status_busca, 
            valor_busca,
            (indice != -1 ? "Encontrado" : "NaoEncontrado"),
            res.tempo_ms, 
            res.comparacoes,
            tempo_ordenacao); // O tempo de ordenação só será relevante para a busca binária

    fclose(saida);
    liberar_resultado(&res);
}


// --- 3. Função Principal ---

int main() {
    // Focaremos no vetor GRANDE aleatório, conforme instrução
    const char* arq_entrada = "dados/grande_aleatorio.bin";
    const char* arq_saida = "resultados/metricas_busca.csv";
    int* vetor_original = NULL;
    long long N = ler_vetor_binario(arq_entrada, &vetor_original);
    if (vetor_original == NULL) return 1;

    // Define valores para busca: um existente e um inexistente
    int valor_existente = vetor_original[N / 2]; 
    int valor_inexistente = -1; // Assumindo que valores no vetor são positivos

    // Cria o cabeçalho do arquivo CSV
    FILE* saida = fopen(arq_saida, "w");
    if (saida != NULL) {
        fprintf(saida, "Algoritmo;Status_Busca;Valor_Busca;Resultado;Tempo_Busca_ms;Comparacoes_Busca;Tempo_Ordenacao_ms\n");
        fclose(saida);
    } else {
        perror("Erro ao criar arquivo CSV");
        free(vetor_original);
        return 1;
    }

    // 1. Teste de Busca Sequencial (Não precisa ordenar)
    printf("Testando Busca Sequencial...\n");
    testar_busca(arq_saida, (void (*)(Resultado*))busca_sequencial, "Sequencial", vetor_original, N, valor_existente, "Existente", 0.0);
    testar_busca(arq_saida, (void (*)(Resultado*))busca_sequencial, "Sequencial", vetor_original, N, valor_inexistente, "Inexistente", 0.0);

    // 2. Teste de Busca Binária (Precisa ordenar primeiro)
    printf("Ordenando vetor para Busca Binária...\n");
    Resultado res_ordenacao;
    inicializar_resultado(&res_ordenacao, N);
    copiar_vetor(res_ordenacao.vetor, vetor_original, N);

    // Use um algoritmo de ordenação rápido (ex: qsort ou InsertionSort/BubbleSort)
    // Para fins do trabalho, usaremos Insertion Sort para ter o tempo medido
    clock_t inicio_ord = clock();
    insertion_sort(&res_ordenacao); // Usando um dos seus algoritmos de O(N^2)
    clock_t fim_ord = clock();
    double tempo_ordenacao_ms = ((double)(fim_ord - inicio_ord) / CLOCKS_PER_SEC) * 1000.0;
    
    // Agora o vetor em res_ordenacao.vetor está ordenado
    
    // Teste para Busca Binária
    printf("Testando Busca Binária...\n");
    
    // O teste para busca binária será feito no vetor ORDENADO. 
    // Copiamos o vetor ordenado de volta para vetor_original para reuso no teste_busca
    copiar_vetor(vetor_original, res_ordenacao.vetor, N); 
    
    testar_busca(arq_saida, (void (*)(Resultado*))busca_binaria, "Binaria", vetor_original, N, valor_existente, "Existente", tempo_ordenacao_ms);
    testar_busca(arq_saida, (void (*)(Resultado*))busca_binaria, "Binaria", vetor_original, N, valor_inexistente, "Inexistente", tempo_ordenacao_ms);
    
    liberar_resultado(&res_ordenacao);
    free(vetor_original);
    
    return 0;
}
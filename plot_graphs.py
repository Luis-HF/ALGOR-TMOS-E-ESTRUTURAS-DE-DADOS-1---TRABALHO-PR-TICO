import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

# --- Configuração ---
ARQUIVO_ORDENACAO = 'resultados/metricas_ordenacao.csv'
DIRETORIO_GRAFICOS = 'resultados/'

# 1. Carregar os Dados
try:
    df = pd.read_csv(ARQUIVO_ORDENACAO, sep=';')
except FileNotFoundError:
    print(f"Erro: Arquivo não encontrado em {ARQUIVO_ORDENACAO}. Certifique-se de que a etapa de ordenação foi executada.")
    exit()

# Converter N para formato numérico
df['Tamanho_N'] = df['Tamanho_N'].astype(int)

# --- GRÁFICO 1: Tempo x Tamanho (Cenário Aleatório) ---

def plot_tempo_vs_tamanho(df):
    plt.figure(figsize=(10, 6))
    
    # Filtrar apenas o cenário Aleatório
    df_aleatorio = df[df['Arquivo'].str.contains('aleatorio')]
    
    algoritmos = df_aleatorio['Algoritmo'].unique()
    
    for alg in algoritmos:
        # Agrupa pelo tamanho e pega a média do tempo para cada algoritmo
        data = df_aleatorio[df_aleatorio['Algoritmo'] == alg].groupby('Tamanho_N')['Tempo_ms'].mean()
        
        # Plotar
        plt.plot(data.index, data.values, marker='o', label=alg)

    plt.title('Tempo de Execução vs. Tamanho do Vetor (Cenário Aleatório)')
    plt.xlabel('Tamanho do Vetor (N)')
    plt.ylabel('Tempo de Execução (ms)')
    plt.xscale('log') # Usa escala logarítmica para N=1000, 10000, 100000
    plt.grid(True, which="both", ls="--")
    plt.legend()
    plt.savefig(DIRETORIO_GRAFICOS + 'grafico1_tempo_vs_tamanho.png')
    print("Gráfico 1 gerado: grafico1_tempo_vs_tamanho.png")
    plt.close()
    
    # 

# --- GRÁFICO 2: Trocas (Selection Sort vs. Bubble Sort) ---

def plot_trocas_comparacao(df):
    plt.figure(figsize=(8, 5))
    
    # Filtrar para Tamanho Médio e Cenário Aleatório
    # Filtrar Algoritmos: Selection Sort e Bubble Sort (Padrão)
    filtro = (df['Tamanho_N'] == 10000) & \
             (df['Arquivo'].str.contains('aleatorio')) & \
             (df['Algoritmo'].isin(['SelectionSort', 'BubbleSort']))

    df_barras = df[filtro].groupby('Algoritmo')['Trocas'].mean()

    # Plotar
    barras = plt.bar(df_barras.index, df_barras.values, color=['skyblue', 'salmon'])

    plt.title('Trocas: Selection Sort vs. Bubble Sort (N=10.000, Aleatório)')
    plt.xlabel('Algoritmo')
    plt.ylabel('Número de Trocas (Swaps)')
    
    # Adicionar os valores nas barras
    for bar in barras:
        yval = bar.get_height()
        plt.text(bar.get_x() + bar.get_width()/2, yval + 500, f'{yval:,.0f}', ha='center', va='bottom')

    plt.savefig(DIRETORIO_GRAFICOS + 'grafico2_trocas_comparacao.png')
    print("Gráfico 2 gerado: grafico2_trocas_comparacao.png")
    plt.close()
    
    # 

# --- GRÁFICO 3: Desempenho do Insertion Sort em Cenários ---

def plot_insertion_sort_cenarios(df):
    plt.figure(figsize=(10, 6))
    
    # Filtrar apenas Insertion Sort
    df_insertion = df[df['Algoritmo'] == 'InsertionSort']

    # Extrair o cenário do nome do arquivo
    df_insertion['Cenario'] = df_insertion['Arquivo'].apply(
        lambda x: x.split('_')[1].replace('.bin', '')
    )

    # Agrupar por Tamanho e Cenário, pegando a média do Tempo
    pivot = df_insertion.pivot_table(index='Tamanho_N', columns='Cenario', values='Tempo_ms', aggfunc='mean')
    
    pivot.plot(kind='line', marker='o', ax=plt.gca())

    plt.title('Insertion Sort: Tempo de Execução por Cenário')
    plt.xlabel('Tamanho do Vetor (N)')
    plt.ylabel('Tempo de Execução (ms)')
    plt.xscale('log')
    plt.grid(True, which="both", ls="--")
    plt.legend(title='Cenário')
    plt.savefig(DIRETORIO_GRAFICOS + 'grafico3_insertion_sort_cenarios.png')
    print("Gráfico 3 gerado: grafico3_insertion_sort_cenarios.png")
    plt.close()
    
# --- Execução Principal ---

if __name__ == "__main__":
    plot_tempo_vs_tamanho(df.copy())
    plot_trocas_comparacao(df.copy())
    plot_insertion_sort_cenarios(df.copy())

    print("\nTodos os gráficos foram salvos na pasta 'resultados/'.")
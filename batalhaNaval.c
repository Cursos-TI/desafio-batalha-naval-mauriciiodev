#include <stdio.h>
#include <stdlib.h> // Para a função abs() (valor absoluto)

// --- Constantes do Jogo ---
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3         // Mantendo o tamanho do navio dos níveis anteriores
#define AGUA 0
#define NAVIO 3                 // Representação de um navio no tabuleiro principal
#define AREA_AFETADA_HABILIDADE 5 // Representação de uma área afetada por habilidade na exibição final

// --- Constantes das Matrizes de Habilidade ---
#define TAMANHO_MATRIZ_HABILIDADE 5 // Usaremos matrizes 5x5 para as habilidades
#define HABILIDADE_AFETA 1          // Valor na matriz de habilidade indicando área afetada
#define HABILIDADE_NAO_AFETA 0      // Valor na matriz de habilidade indicando área não afetada

// --- Orientações dos Navios (do Nível Aventureiro) ---
#define HORIZONTAL 0
#define VERTICAL 1
#define DIAGONAL_PRINCIPAL 2  // Linha e coluna aumentam
#define DIAGONAL_SECUNDARIA 3 // Linha aumenta, coluna diminui

// --- Protótipos das Funções ---

// Funções do Tabuleiro Principal e Navios (do Nível Aventureiro)
void inicializar_tabuleiro(int tabuleiro[][TAMANHO_TABULEIRO]);
// A função tentar_posicionar_navio completa do nível aventureiro seria usada aqui.
// Para este exemplo, incluirei uma versão muito simplificada para popular o tabuleiro.
int tentar_posicionar_navio_simplificado(int tabuleiro[][TAMANHO_TABULEIRO], int l, int c, int tam, int ori);

// Funções para gerar as Matrizes de Habilidade
void limpar_matriz_habilidade(int matriz_habilidade[][TAMANHO_MATRIZ_HABILIDADE], int tamanho);
void gerar_matriz_cone(int matriz_habilidade[][TAMANHO_MATRIZ_HABILIDADE], int tamanho);
void gerar_matriz_cruz(int matriz_habilidade[][TAMANHO_MATRIZ_HABILIDADE], int tamanho);
void gerar_matriz_octaedro(int matriz_habilidade[][TAMANHO_MATRIZ_HABILIDADE], int tamanho);

// Função para aplicar o efeito da habilidade no tabuleiro de overlay
void aplicar_habilidade_ao_overlay(
    int tabuleiro_overlay[][TAMANHO_TABULEIRO],
    int origem_r_no_tabuleiro, int origem_c_no_tabuleiro,
    int matriz_habilidade_gerada[][TAMANHO_MATRIZ_HABILIDADE], int tamanho_matriz_hab
);

// Função de Exibição Final (combinando navios e overlay de habilidades)
void exibir_tabuleiro_combinado(
    int tabuleiro_com_navios[][TAMANHO_TABULEIRO],
    int tabuleiro_com_overlay_habilidades[][TAMANHO_TABULEIRO]
);


int main() {
    // Comentário: Declaração do tabuleiro principal do jogo.
    int tabuleiro_principal[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    // Comentário: Declaração do tabuleiro de overlay para marcar áreas de efeito das habilidades.
    int tabuleiro_overlay_habilidades[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    // Comentário: Matriz temporária para gerar os padrões de cada habilidade.
    int matriz_habilidade_atual[TAMANHO_MATRIZ_HABILIDADE][TAMANHO_MATRIZ_HABILIDADE];

    // 1. Inicializar ambos os tabuleiros (principal com água, overlay com não afetado).
    inicializar_tabuleiro(tabuleiro_principal); // Preenche com AGUA (0)
    inicializar_tabuleiro(tabuleiro_overlay_habilidades); // Preenche com 0 (significando não afetado por padrão)

    // Comentário: Posicionar os 4 navios (lógica do Nível Aventureiro).
    // Usando a função simplificada para este exemplo focar nas habilidades.
    // Em um projeto integrado, a função completa com validações seria usada.
    printf("Posicionando navios no tabuleiro principal...\n");
    tentar_posicionar_navio_simplificado(tabuleiro_principal, 1, 1, TAMANHO_NAVIO, HORIZONTAL);
    tentar_posicionar_navio_simplificado(tabuleiro_principal, 3, 5, TAMANHO_NAVIO, VERTICAL);
    tentar_posicionar_navio_simplificado(tabuleiro_principal, 5, 1, TAMANHO_NAVIO, DIAGONAL_PRINCIPAL);
    tentar_posicionar_navio_simplificado(tabuleiro_principal, 0, 8, TAMANHO_NAVIO, DIAGONAL_SECUNDARIA); // Ajustado para caber
    printf("Navios posicionados (ou tentativas feitas).\n");

    printf("\n--- Tabuleiro Inicial (Apenas com Navios) ---\n");
    exibir_tabuleiro_combinado(tabuleiro_principal, tabuleiro_overlay_habilidades); // Overlay está vazio (tudo 0)
    printf("\n");

    // 2. Gerar e Aplicar Habilidades no Tabuleiro de Overlay

    // Habilidade 1: Cone
    // Comentário: Define um ponto de origem no tabuleiro para o centro da habilidade Cone.
    int origem_r_cone = 4; 
    int origem_c_cone = 4;
    limpar_matriz_habilidade(matriz_habilidade_atual, TAMANHO_MATRIZ_HABILIDADE); // Limpa para novo padrão
    gerar_matriz_cone(matriz_habilidade_atual, TAMANHO_MATRIZ_HABILIDADE);
    printf("Aplicando Habilidade CONE com origem em L%d, C%d...\n", origem_r_cone, origem_c_cone);
    aplicar_habilidade_ao_overlay(tabuleiro_overlay_habilidades, origem_r_cone, origem_c_cone, matriz_habilidade_atual, TAMANHO_MATRIZ_HABILIDADE);

    // Habilidade 2: Cruz
    // Comentário: Define um ponto de origem diferente para a habilidade Cruz.
    int origem_r_cruz = 7; 
    int origem_c_cruz = 2;
    limpar_matriz_habilidade(matriz_habilidade_atual, TAMANHO_MATRIZ_HABILIDADE);
    gerar_matriz_cruz(matriz_habilidade_atual, TAMANHO_MATRIZ_HABILIDADE);
    printf("Aplicando Habilidade CRUZ com origem em L%d, C%d...\n", origem_r_cruz, origem_c_cruz);
    aplicar_habilidade_ao_overlay(tabuleiro_overlay_habilidades, origem_r_cruz, origem_c_cruz, matriz_habilidade_atual, TAMANHO_MATRIZ_HABILIDADE);

    // Habilidade 3: Octaedro (Losango)
    // Comentário: Define um ponto de origem para a habilidade Octaedro.
    int origem_r_octa = 1; 
    int origem_c_octa = 5;
    limpar_matriz_habilidade(matriz_habilidade_atual, TAMANHO_MATRIZ_HABILIDADE);
    gerar_matriz_octaedro(matriz_habilidade_atual, TAMANHO_MATRIZ_HABILIDADE);
    printf("Aplicando Habilidade OCTAEDRO com origem em L%d, C%d...\n", origem_r_octa, origem_c_octa);
    aplicar_habilidade_ao_overlay(tabuleiro_overlay_habilidades, origem_r_octa, origem_c_octa, matriz_habilidade_atual, TAMANHO_MATRIZ_HABILIDADE);

    // 3. Exibir o tabuleiro final com navios e todas as áreas de efeito das habilidades combinadas.
    printf("\n--- Tabuleiro Final com Navios e Áreas de Habilidade Ativadas ---\n");
    exibir_tabuleiro_combinado(tabuleiro_principal, tabuleiro_overlay_habilidades);

    return 0;
}

/**
 * @brief Inicializa um tabuleiro (principal ou de overlay) preenchendo com AGUA (0).
 */
void inicializar_tabuleiro(int tabuleiro[][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA; // AGUA também serve como "não afetado por overlay" inicialmente
        }
    }
}

/**
 * @brief Versão MUITO SIMPLIFICADA de posicionar_navio para popular o tabuleiro principal.
 * Em um projeto completo, a versão robusta do Nível Aventureiro (com todas as validações) seria usada.
 */
int tentar_posicionar_navio_simplificado(int tabuleiro[][TAMANHO_TABULEIRO], int linha_inicial, int coluna_inicial, int tamanho_navio, int orientacao) {
    for (int i = 0; i < tamanho_navio; i++) {
        int r = linha_inicial, c = coluna_inicial;
        switch (orientacao) {
            case HORIZONTAL: c += i; break;
            case VERTICAL: r += i; break;
            case DIAGONAL_PRINCIPAL: r += i; c += i; break;
            case DIAGONAL_SECUNDARIA: r += i; c -= i; break;
            default: return 0;
        }
        if (r >= 0 && r < TAMANHO_TABULEIRO && c >= 0 && c < TAMANHO_TABULEIRO) {
            if (tabuleiro[r][c] == AGUA) { // Verifica se não há sobreposição (simplificado)
                 tabuleiro[r][c] = NAVIO;
            } else {
                // printf("Debug: Sobreposição simplificada em L%d C%d para navio.\n", r,c);
                // return 0; // Falha simplificada por sobreposição
            }
        } else {
            // printf("Debug: Fora dos limites simplificado em L%d C%d para navio.\n", r,c);
            // return 0; // Falha simplificada por limites
        }
    }
    return 1; // Assume sucesso para simplificação
}


/**
 * @brief Limpa (zera) uma matriz de habilidade.
 */
void limpar_matriz_habilidade(int matriz_habilidade[][TAMANHO_MATRIZ_HABILIDADE], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            matriz_habilidade[i][j] = HABILIDADE_NAO_AFETA;
        }
    }
}

/**
 * @brief Gera o padrão de um Cone na matriz de habilidade.
 * O cone tem a ponta na linha 0, coluna central da matriz de habilidade,
 * e a base na linha central da matriz de habilidade.
 * Exemplo para 5x5 (centro_col=2):
 * Linha 0: 00100
 * Linha 1: 01110
 * Linha 2: 11111 (esta é a linha que se alinha com a origem da habilidade no tabuleiro)
 */
void gerar_matriz_cone(int matriz_habilidade[][TAMANHO_MATRIZ_HABILIDADE], int tamanho) {
    limpar_matriz_habilidade(matriz_habilidade, tamanho); // Garante que começa limpa
    int centro_col_matriz = tamanho / 2; // Ex: 2 para tamanho 5
    // O "topo" visual do cone está na linha 0 da matriz de habilidade.
    // A base do cone (parte mais larga) estará na linha 'centro_col_matriz' da matriz de habilidade.
    // A altura visual do cone dentro da matriz será 'centro_col_matriz + 1' linhas.

    // Comentário: Loop para cada linha da forma do cone dentro da matriz de habilidade.
    for (int r_skill = 0; r_skill <= centro_col_matriz; r_skill++) { // r_skill vai de 0 até a linha central
        int meia_largura_na_linha = r_skill; // Largura da base na linha 'r_skill' é 2*r_skill + 1
        // Comentário: Loop para preencher as colunas afetadas na linha atual do cone.
        for (int c_skill = centro_col_matriz - meia_largura_na_linha; c_skill <= centro_col_matriz + meia_largura_na_linha; c_skill++) {
            // Validação de segurança, embora a lógica de meia_largura deva manter dentro para r_skill <= centro_col_matriz
            if (c_skill >= 0 && c_skill < tamanho) {
                matriz_habilidade[r_skill][c_skill] = HABILIDADE_AFETA;
            }
        }
    }
}


/**
 * @brief Gera o padrão de uma Cruz na matriz de habilidade.
 * A cruz é formada por uma linha vertical e uma horizontal que se cruzam no centro da matriz.
 */
void gerar_matriz_cruz(int matriz_habilidade[][TAMANHO_MATRIZ_HABILIDADE], int tamanho) {
    limpar_matriz_habilidade(matriz_habilidade, tamanho);
    int centro_matriz = tamanho / 2; // Ex: 2 para tamanho 5

    // Comentário: Loop para desenhar a barra vertical da cruz.
    for (int r = 0; r < tamanho; r++) {
        matriz_habilidade[r][centro_matriz] = HABILIDADE_AFETA;
    }
    // Comentário: Loop para desenhar a barra horizontal da cruz.
    for (int c = 0; c < tamanho; c++) {
        matriz_habilidade[centro_matriz][c] = HABILIDADE_AFETA;
    }
}

/**
 * @brief Gera o padrão de um Octaedro (Losango/Diamante) na matriz de habilidade.
 * Usa a fórmula da distância de Manhattan: |r - centro| + |c - centro| <= raio.
 */
void gerar_matriz_octaedro(int matriz_habilidade[][TAMANHO_MATRIZ_HABILIDADE], int tamanho) {
    limpar_matriz_habilidade(matriz_habilidade, tamanho);
    int centro_matriz = tamanho / 2; // Ex: 2 para tamanho 5
    int raio_losango = tamanho / 2;  // Ex: 2 para tamanho 5, resultando em um losango completo

    // Comentário: Loop para percorrer cada célula da matriz de habilidade.
    for (int r = 0; r < tamanho; r++) {
        for (int c = 0; c < tamanho; c++) {
            // Comentário: Condicional que define a forma do losango.
            if (abs(r - centro_matriz) + abs(c - centro_matriz) <= raio_losango) {
                matriz_habilidade[r][c] = HABILIDADE_AFETA;
            }
        }
    }
}

/**
 * @brief Aplica o padrão de uma matriz de habilidade a um tabuleiro de overlay.
 * A matriz de habilidade é centrada no ponto (origem_r_tabuleiro, origem_c_tabuleiro) do overlay.
 * @param tabuleiro_overlay Tabuleiro 10x10 que armazena onde as habilidades afetam.
 * @param origem_r_tabuleiro Linha no tabuleiro principal onde o centro da habilidade será aplicado.
 * @param origem_c_tabuleiro Coluna no tabuleiro principal onde o centro da habilidade será aplicado.
 * @param matriz_habilidade_gerada Matriz (ex: 5x5) contendo o padrão da habilidade (0s e 1s).
 * @param tamanho_matriz_hab Dimensão da matriz_habilidade_gerada (ex: 5).
 */
void aplicar_habilidade_ao_overlay(
    int tabuleiro_overlay[][TAMANHO_TABULEIRO],
    int origem_r_no_tabuleiro, int origem_c_no_tabuleiro,
    int matriz_habilidade_gerada[][TAMANHO_MATRIZ_HABILIDADE], int tamanho_matriz_hab) {

    // Comentário: O centro da matriz de habilidade (ex: [2][2] para 5x5) é a referência.
    int centro_da_matriz_habilidade = tamanho_matriz_hab / 2;

    // Comentário: Itera sobre cada célula da matriz de habilidade (ex: 5x5).
    for (int r_skill = 0; r_skill < tamanho_matriz_hab; r_skill++) { // r_skill: linha na matriz de habilidade
        for (int c_skill = 0; c_skill < tamanho_matriz_hab; c_skill++) { // c_skill: coluna na matriz de habilidade
            
            // Comentário: Verifica se a célula atual da matriz de habilidade faz parte do efeito.
            if (matriz_habilidade_gerada[r_skill][c_skill] == HABILIDADE_AFETA) {
                // Comentário: Calcula a posição correspondente no tabuleiro principal (10x10).
                // O deslocamento (r_skill - centro_da_matriz_habilidade) determina a posição relativa
                // da célula da skill_matrix em relação ao seu próprio centro.
                // Este deslocamento é então aplicado à origem da habilidade no tabuleiro principal.
                int r_alvo_no_tabuleiro = origem_r_no_tabuleiro + (r_skill - centro_da_matriz_habilidade);
                int c_alvo_no_tabuleiro = origem_c_no_tabuleiro + (c_skill - centro_da_matriz_habilidade);

                // Comentário: Valida se a posição alvo está dentro dos limites do tabuleiro principal.
                // Esta é a condicional para garantir que a sobreposição respeite os limites.
                if (r_alvo_no_tabuleiro >= 0 && r_alvo_no_tabuleiro < TAMANHO_TABULEIRO &&
                    c_alvo_no_tabuleiro >= 0 && c_alvo_no_tabuleiro < TAMANHO_TABULEIRO) {
                    
                    // Comentário: Marca a célula no tabuleiro de overlay como afetada.
                    // Usamos HABILIDADE_AFETA (1) no overlay para indicar que uma habilidade atinge ali.
                    tabuleiro_overlay[r_alvo_no_tabuleiro][c_alvo_no_tabuleiro] = HABILIDADE_AFETA;
                }
            }
        }
    }
}

/**
 * @brief Exibe o tabuleiro final, combinando o tabuleiro de navios com o overlay de habilidades.
 * @param tabuleiro_com_navios Matriz 10x10 com ÁGUA e NAVIOs.
 * @param tabuleiro_com_overlay_habilidades Matriz 10x10 com HABILIDADE_AFETA (1) ou 0.
 */
void exibir_tabuleiro_combinado(
    int tabuleiro_com_navios[][TAMANHO_TABULEIRO],
    int tabuleiro_com_overlay_habilidades[][TAMANHO_TABULEIRO]) {

    // Comentário: Imprime cabeçalho das colunas.
    printf("   ");
    for (int k = 0; k < TAMANHO_TABULEIRO; k++) {
        printf("%d ", k);
    }
    printf("\n");
    printf("   ");
    for (int k = 0; k < TAMANHO_TABULEIRO; k++) {
        printf("--");
    }
    printf("\n");

    // Comentário: Itera sobre cada linha e coluna do tabuleiro para exibição.
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%2d| ", i); // Imprime o índice da linha.
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            // Comentário: Lógica de prioridade para exibição:
            // 1. Se a célula está no overlay de habilidades, mostra AREA_AFETADA_HABILIDADE (5).
            // 2. Senão, se a célula contém um NAVIO, mostra NAVIO (3).
            // 3. Senão, mostra AGUA (0).
            if (tabuleiro_com_overlay_habilidades != NULL && tabuleiro_com_overlay_habilidades[i][j] == HABILIDADE_AFETA) {
                printf("%d ", AREA_AFETADA_HABILIDADE);
            } else if (tabuleiro_com_navios[i][j] == NAVIO) {
                printf("%d ", NAVIO);
            } else {
                printf("%d ", AGUA);
            }
        }
        printf("\n");
    }
}
#include <stdio.h>

// --- Constantes do Jogo ---
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3         // Tamanho fixo para todos os navios neste nível
#define AGUA 0
#define NAVIO 3                 // Representação de parte de um navio no tabuleiro

// --- Orientações dos Navios ---
// Comentário: Definindo constantes para as diferentes orientações possíveis dos navios.
#define HORIZONTAL 0
#define VERTICAL 1
#define DIAGONAL_PRINCIPAL 2  // Navio se estende com linha e coluna aumentando (ex: \ )
#define DIAGONAL_SECUNDARIA 3 // Navio se estende com linha aumentando e coluna diminuindo (ex: / )

// --- Protótipos das Funções ---
void inicializar_tabuleiro(int tabuleiro[][TAMANHO_TABULEIRO]);
void exibir_tabuleiro(int tabuleiro[][TAMANHO_TABULEIRO]);
int tentar_posicionar_navio(int tabuleiro[][TAMANHO_TABULEIRO], int linha_inicial, int coluna_inicial, int tamanho_navio, int orientacao);

int main() {
    // Comentário: Declaração da matriz que representa o tabuleiro do jogo.
    int tabuleiro_principal[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    // Comentário: Inicializa todas as posições do tabuleiro com água (valor 0).
    inicializar_tabuleiro(tabuleiro_principal);
    printf("Tabuleiro Inicializado com Água:\n");
    exibir_tabuleiro(tabuleiro_principal);
    printf("\n");

    // --- Posicionamento dos Quatro Navios ---
    // Comentário: As coordenadas iniciais, tamanho e orientação são definidos diretamente no código.

    // Navio 1: Horizontal
    printf("Tentando posicionar Navio 1 (Horizontal, Tamanho %d) em L1, C1...\n", TAMANHO_NAVIO);
    if (tentar_posicionar_navio(tabuleiro_principal, 1, 1, TAMANHO_NAVIO, HORIZONTAL)) {
        printf("Navio 1 (Horizontal) posicionado com sucesso!\n");
    } else {
        printf("Falha ao posicionar Navio 1 (Horizontal).\n");
    }
    exibir_tabuleiro(tabuleiro_principal); // Mostra o tabuleiro após a tentativa
    printf("\n");

    // Navio 2: Vertical
    printf("Tentando posicionar Navio 2 (Vertical, Tamanho %d) em L3, C5...\n", TAMANHO_NAVIO);
    if (tentar_posicionar_navio(tabuleiro_principal, 3, 5, TAMANHO_NAVIO, VERTICAL)) {
        printf("Navio 2 (Vertical) posicionado com sucesso!\n");
    } else {
        printf("Falha ao posicionar Navio 2 (Vertical).\n");
    }
    exibir_tabuleiro(tabuleiro_principal);
    printf("\n");

    // Navio 3: Diagonal Principal (linha e coluna aumentam)
    // Ex: (5,1), (6,2), (7,3)
    printf("Tentando posicionar Navio 3 (Diagonal Principal, Tamanho %d) em L5, C1...\n", TAMANHO_NAVIO);
    if (tentar_posicionar_navio(tabuleiro_principal, 5, 1, TAMANHO_NAVIO, DIAGONAL_PRINCIPAL)) {
        printf("Navio 3 (Diagonal Principal) posicionado com sucesso!\n");
    } else {
        printf("Falha ao posicionar Navio 3 (Diagonal Principal).\n");
    }
    exibir_tabuleiro(tabuleiro_principal);
    printf("\n");

    // Navio 4: Diagonal Secundária (linha aumenta, coluna diminui)
    // Ex: (1,8), (2,7), (3,6)
    printf("Tentando posicionar Navio 4 (Diagonal Secundária, Tamanho %d) em L1, C8...\n", TAMANHO_NAVIO);
    if (tentar_posicionar_navio(tabuleiro_principal, 1, 8, TAMANHO_NAVIO, DIAGONAL_SECUNDARIA)) {
        printf("Navio 4 (Diagonal Secundária) posicionado com sucesso!\n");
    } else {
        printf("Falha ao posicionar Navio 4 (Diagonal Secundária).\n");
    }
    exibir_tabuleiro(tabuleiro_principal);
    printf("\n");
    
    // Comentário: Exibe o tabuleiro final após todas as tentativas de posicionamento.
    printf("--- Configuração Final do Tabuleiro ---\n");
    exibir_tabuleiro(tabuleiro_principal);

    return 0; // Indica que o programa terminou com sucesso
}

/**
 * @brief Inicializa o tabuleiro preenchendo todas as suas posições com o valor AGUA.
 * @param tabuleiro A matriz 2D representando o tabuleiro.
 */
void inicializar_tabuleiro(int tabuleiro[][TAMANHO_TABULEIRO]) {
    // Comentário: Loop para percorrer cada linha do tabuleiro.
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        // Comentário: Loop para percorrer cada coluna da linha atual.
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA; // Define a célula como AGUA
        }
    }
}

/**
 * @brief Exibe o estado atual do tabuleiro no console.
 * @param tabuleiro A matriz 2D representando o tabuleiro.
 */
void exibir_tabuleiro(int tabuleiro[][TAMANHO_TABULEIRO]) {
    // Comentário: Imprime cabeçalho das colunas para melhor visualização.
    printf("   "); // Espaçamento para alinhar com os números das linhas
    for (int k = 0; k < TAMANHO_TABULEIRO; k++) {
        printf("%d ", k); // Imprime o índice da coluna
    }
    printf("\n");
    printf("   ");
    for (int k = 0; k < TAMANHO_TABULEIRO; k++) {
        printf("--"); // Linha separadora
    }
    printf("\n");

    // Comentário: Loop para percorrer cada linha do tabuleiro.
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%2d| ", i); // Imprime o índice da linha formatado
        // Comentário: Loop para percorrer cada coluna da linha atual.
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]); // Imprime o conteúdo da célula
        }
        printf("\n"); // Pula para a próxima linha no console
    }
}

/**
 * @brief Tenta posicionar um navio no tabuleiro.
 * Valida limites e sobreposição para orientações horizontal, vertical e diagonal.
 * @param tabuleiro A matriz do jogo.
 * @param linha_inicial Linha da primeira parte do navio.
 * @param coluna_inicial Coluna da primeira parte do navio.
 * @param tamanho_navio Quantas células o navio ocupa.
 * @param orientacao HORIZONTAL, VERTICAL, DIAGONAL_PRINCIPAL ou DIAGONAL_SECUNDARIA.
 * @return 1 se posicionado com sucesso, 0 caso contrário.
 */
int tentar_posicionar_navio(int tabuleiro[][TAMANHO_TABULEIRO], int linha_inicial, int coluna_inicial, int tamanho_navio, int orientacao) {
    int r_atual, c_atual; // Coordenadas da célula atual sendo verificada/modificada

    // Comentário: Passo 1: Validar se todas as partes do navio estão dentro dos limites do tabuleiro.
    // Comentário: Este loop verifica cada segmento do navio.
    for (int i = 0; i < tamanho_navio; i++) {
        // Comentário: Calcula as coordenadas (r_atual, c_atual) para o segmento 'i' do navio,
        // de acordo com a orientação.
        switch (orientacao) {
            case HORIZONTAL:
                r_atual = linha_inicial;
                c_atual = coluna_inicial + i;
                break;
            case VERTICAL:
                r_atual = linha_inicial + i;
                c_atual = coluna_inicial;
                break;
            case DIAGONAL_PRINCIPAL: // linha e coluna aumentam
                r_atual = linha_inicial + i;
                c_atual = coluna_inicial + i;
                break;
            case DIAGONAL_SECUNDARIA: // linha aumenta, coluna diminui
                r_atual = linha_inicial + i;
                c_atual = coluna_inicial - i;
                break;
            default:
                printf("Erro interno: Orientação %d desconhecida para validação de limites.\n", orientacao);
                return 0; // Orientação inválida
        }

        // Comentário: Verifica se a coordenada calculada está fora do tabuleiro.
        if (r_atual < 0 || r_atual >= TAMANHO_TABULEIRO || c_atual < 0 || c_atual >= TAMANHO_TABULEIRO) {
            printf("Erro de posicionamento: Parte %d do navio (em L%d, C%d - calculado) ficaria fora dos limites para orientação %d.\n",
                   i + 1, r_atual, c_atual, orientacao);
            return 0; // Falha: Navio fora dos limites
        }
    }

    // Comentário: Passo 2: Validar se o navio se sobrepõe a outro já existente.
    // Comentário: Este loop verifica se alguma das células que o navio ocuparia já está marcada.
    for (int i = 0; i < tamanho_navio; i++) {
        // Comentário: Recalcula as coordenadas para o segmento 'i'.
        switch (orientacao) {
            case HORIZONTAL:
                r_atual = linha_inicial;
                c_atual = coluna_inicial + i;
                break;
            case VERTICAL:
                r_atual = linha_inicial + i;
                c_atual = coluna_inicial;
                break;
            case DIAGONAL_PRINCIPAL:
                r_atual = linha_inicial + i;
                c_atual = coluna_inicial + i;
                break;
            case DIAGONAL_SECUNDARIA:
                r_atual = linha_inicial + i;
                c_atual = coluna_inicial - i;
                break;
            default: /* Este caso já foi tratado no loop anterior, mas defensivamente: */ return 0;
        }

        // Comentário: Se a célula não for AGUA, há sobreposição.
        if (tabuleiro[r_atual][c_atual] != AGUA) {
            printf("Erro de posicionamento: Sobreposição de navio em L%d, C%d para orientação %d.\n",
                   r_atual, c_atual, orientacao);
            return 0; // Falha: Sobreposição
        }
    }

    // Comentário: Passo 3: Se todas as validações anteriores passaram, posicionar o navio.
    // Comentário: Marca as posições do navio no tabuleiro com o valor NAVIO.
    for (int i = 0; i < tamanho_navio; i++) {
        // Comentário: Recalcula as coordenadas para o segmento 'i' para fazer a marcação.
        switch (orientacao) {
            case HORIZONTAL:
                tabuleiro[linha_inicial][coluna_inicial + i] = NAVIO;
                break;
            case VERTICAL:
                tabuleiro[linha_inicial + i][coluna_inicial] = NAVIO;
                break;
            case DIAGONAL_PRINCIPAL:
                tabuleiro[linha_inicial + i][coluna_inicial + i] = NAVIO;
                break;
            case DIAGONAL_SECUNDARIA:
                tabuleiro[linha_inicial + i][coluna_inicial - i] = NAVIO;
                break;
            // default não é necessário aqui, pois orientações inválidas já retornariam 0.
        }
    }
    return 1; // Sucesso no posicionamento
}
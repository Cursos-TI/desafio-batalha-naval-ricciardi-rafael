#include <stdio.h>

// Desafio Batalha Naval - MateCheck
// Este código inicial serve como base para o desenvolvimento do sistema de Batalha Naval.
// Siga os comentários para implementar cada parte do desafio.

int main() {
    // Nível Novato - Posicionamento dos Navios
    // Sugestão: Declare uma matriz bidimensional para representar o tabuleiro (Ex: int tabuleiro[5][5];).
    // Sugestão: Posicione dois navios no tabuleiro, um verticalmente e outro horizontalmente.
    // Sugestão: Utilize `printf` para exibir as coordenadas de cada parte dos navios.

    // Nível Aventureiro - Expansão do Tabuleiro e Posicionamento Diagonal
    // Sugestão: Expanda o tabuleiro para uma matriz 10x10.
    // Sugestão: Posicione quatro navios no tabuleiro, incluindo dois na diagonal.
    // Sugestão: Exiba o tabuleiro completo no console, mostrando 0 para posições vazias e 3 para posições ocupadas.

    // Nível Mestre - Habilidades Especiais com Matrizes
    // Sugestão: Crie matrizes para representar habilidades especiais como cone, cruz, e octaedro.
    // Sugestão: Utilize estruturas de repetição aninhadas para preencher as áreas afetadas por essas habilidades no tabuleiro.
    // Sugestão: Exiba o tabuleiro com as áreas afetadas, utilizando 0 para áreas não afetadas e 1 para áreas atingidas.

    // Exemplos de exibição das habilidades:
    // Exemplo para habilidade em cone:
    // 0 0 1 0 0
    // 0 1 1 1 0
    // 1 1 1 1 1
    
    // Exemplo para habilidade em octaedro:
    // 0 0 1 0 0
    // 0 1 1 1 0
    // 0 0 1 0 0

    // Exemplo para habilidade em cruz:
    // 0 0 1 0 0
    // 1 1 1 1 1
    // 0 0 1 0 0

      // tamanhos fixos
    #define BOARD_SIZE 10
    #define SHIP_LEN   3

    // tabuleiro 10x10 com 0 (água)
    int board[BOARD_SIZE][BOARD_SIZE] = {0};

    // coordenadas escolhidas (edite se quiser testar)
    // 2 ortogonais
    int hRow = 2, hCol = 1;               // horizontal →
    int vRow = 0, vCol = 5;               // vertical ↓
    // 2 diagonais
    int d1Row = 5, d1Col = 0;             // diagonal \ (↓→)
    int d2Row = 3, d2Col = 9;             // diagonal / (↓←)

    int i; // auxiliar

    // --- valida horizontal (cabe no tabuleiro) ---
    if (hRow < 0 || hRow >= BOARD_SIZE || hCol < 0 || hCol + SHIP_LEN - 1 >= BOARD_SIZE) {
        printf("Coord invalidas: navio horizontal.\n");
        return 1;
    }
    // --- sobreposicao horizontal ---
    for (i = 0; i < SHIP_LEN; i++) {
        if (board[hRow][hCol + i] != 0) {
            printf("Sobreposicao: navio horizontal.\n");
            return 1;
        }
    }
    // --- coloca horizontal ---
    for (i = 0; i < SHIP_LEN; i++) board[hRow][hCol + i] = 3;

    // --- valida vertical (cabe no tabuleiro) ---
    if (vCol < 0 || vCol >= BOARD_SIZE || vRow < 0 || vRow + SHIP_LEN - 1 >= BOARD_SIZE) {
        printf("Coord invalidas: navio vertical.\n");
        return 1;
    }
    // --- sobreposicao vertical ---
    for (i = 0; i < SHIP_LEN; i++) {
        if (board[vRow + i][vCol] != 0) {
            printf("Sobreposicao: navio vertical.\n");
            return 1;
        }
    }
    // --- coloca vertical ---
    for (i = 0; i < SHIP_LEN; i++) board[vRow + i][vCol] = 3;

    // --- valida diagonal \ (↓→) ---
    if (d1Row < 0 || d1Col < 0 ||
        d1Row + SHIP_LEN - 1 >= BOARD_SIZE || d1Col + SHIP_LEN - 1 >= BOARD_SIZE) {
        printf("Coord invalidas: navio diagonal \\\n");
        return 1;
    }
    // --- sobreposicao diagonal \ ---
    for (i = 0; i < SHIP_LEN; i++) {
        int r = d1Row + i, c = d1Col + i;
        if (board[r][c] != 0) {
            printf("Sobreposicao: navio diagonal \\\n");
            return 1;
        }
    }
    // --- coloca diagonal \ ---
    for (i = 0; i < SHIP_LEN; i++) board[d1Row + i][d1Col + i] = 3;

    // --- valida diagonal / (↓←) ---
    if (d2Row < 0 || d2Col < 0 ||
        d2Row + SHIP_LEN - 1 >= BOARD_SIZE || d2Col - (SHIP_LEN - 1) < 0) {
        printf("Coord invalidas: navio diagonal /\n");
        return 1;
    }
    // --- sobreposicao diagonal / ---
    for (i = 0; i < SHIP_LEN; i++) {
        int r = d2Row + i, c = d2Col - i;
        if (board[r][c] != 0) {
            printf("Sobreposicao: navio diagonal /\n");
            return 1;
        }
    }
    // --- coloca diagonal / ---
    for (i = 0; i < SHIP_LEN; i++) board[d2Row + i][d2Col - i] = 3;

    // --- imprime tabuleiro ---
    printf("\nTabuleiro 10x10 (0=agua, 3=navio)\n\n");
    for (int r = 0; r < BOARD_SIZE; r++) {
        for (int c = 0; c < BOARD_SIZE; c++) {
            printf("%d ", board[r][c]);
        }
        printf("\n");
    }

    return 0;
}

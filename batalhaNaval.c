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

    // navios (valores 3)
    int shipH[SHIP_LEN] = {3, 3, 3};
    int shipV[SHIP_LEN] = {3, 3, 3};

    // coordenadas escolhidas no código
    int hRow = 2, hCol = 1; // navio horizontal
    int vRow = 0, vCol = 5; // navio vertical

    // valida limites do navio horizontal
    if (hRow < 0 || hRow >= BOARD_SIZE || hCol < 0 || (hCol + SHIP_LEN - 1) >= BOARD_SIZE) {
        printf("Coordenadas invalidas para navio horizontal.\n");
        return 1;
    }

    // verifica sobreposicao para horizontal
    for (int i = 0; i < SHIP_LEN; i++) {
        if (board[hRow][hCol + i] != 0) {
            printf("Sobreposicao ao colocar navio horizontal.\n");
            return 1;
        }
    }

    // posiciona horizontal
    for (int i = 0; i < SHIP_LEN; i++) {
        board[hRow][hCol + i] = shipH[i];
    }

    // valida limites do navio vertical
    if (vCol < 0 || vCol >= BOARD_SIZE || vRow < 0 || (vRow + SHIP_LEN - 1) >= BOARD_SIZE) {
        printf("Coordenadas invalidas para navio vertical.\n");
        return 1;
    }

    // verifica sobreposicao para vertical
    for (int i = 0; i < SHIP_LEN; i++) {
        if (board[vRow + i][vCol] != 0) {
            printf("Sobreposicao ao colocar navio vertical.\n");
            return 1;
        }
    }

    // posiciona vertical
    for (int i = 0; i < SHIP_LEN; i++) {
        board[vRow + i][vCol] = shipV[i];
    }

    // imprime tabuleiro
    printf("\nTabuleiro (0=agua, 3=navio)\n\n");
    for (int r = 0; r < BOARD_SIZE; r++) {
        for (int c = 0; c < BOARD_SIZE; c++) {
            printf("%d ", board[r][c]);
        }
        printf("\n");
    }

    return 0;
}

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
    #define SKILL_SIZE 7   // 7x7
    #define MID        (SKILL_SIZE/2)

    // tabuleiro
    int board[BOARD_SIZE][BOARD_SIZE] = {0};

    // --- NAVIOS (valor 3) ---
    // coords fixas e simples (sem sobreposição)
    int hRow=2,hCol=1;             // horizontal →
    int vRow=0,vCol=5;             // vertical ↓
    int d1Row=5,d1Col=0;           // diagonal \ (↓→)
    int d2Row=3,d2Col=9;           // diagonal / (↓←)

    // valida e coloca horizontal
    if (hRow>=0 && hRow<BOARD_SIZE && hCol>=0 && hCol+SHIP_LEN-1<BOARD_SIZE) {
        for (int i=0;i<SHIP_LEN;i++) {
            if (board[hRow][hCol+i]!=0){printf("Sobreposicao H\n");return 1;}
        }
        for (int i=0;i<SHIP_LEN;i++) board[hRow][hCol+i]=3;
    } else { printf("Coord H invalidas\n"); return 1; }

    // valida e coloca vertical
    if (vCol>=0 && vCol<BOARD_SIZE && vRow>=0 && vRow+SHIP_LEN-1<BOARD_SIZE) {
        for (int i=0;i<SHIP_LEN;i++) {
            if (board[vRow+i][vCol]!=0){printf("Sobreposicao V\n");return 1;}
        }
        for (int i=0;i<SHIP_LEN;i++) board[vRow+i][vCol]=3;
    } else { printf("Coord V invalidas\n"); return 1; }

    // valida e coloca diagonal
    if (d1Row>=0 && d1Col>=0 && d1Row+SHIP_LEN-1<BOARD_SIZE && d1Col+SHIP_LEN-1<BOARD_SIZE) {
        for (int i=0;i<SHIP_LEN;i++) {
            if (board[d1Row+i][d1Col+i]!=0){printf("Sobreposicao \\\n");return 1;}
        }
        for (int i=0;i<SHIP_LEN;i++) board[d1Row+i][d1Col+i]=3;
    } else { printf("Coord \\ invalidas\n"); return 1; }

    // valida e coloca diagonal /
    if (d2Row>=0 && d2Col>=0 && d2Row+SHIP_LEN-1<BOARD_SIZE && d2Col-(SHIP_LEN-1)>=0) {
        for (int i=0;i<SHIP_LEN;i++) {
            if (board[d2Row+i][d2Col-i]!=0){printf("Sobreposicao /\n");return 1;}
        }
        for (int i=0;i<SHIP_LEN;i++) board[d2Row+i][d2Col-i]=3;
    } else { printf("Coord / invalidas\n"); return 1; }

    // --- MATRIZES DE HABILIDADE (0/1) ---
    int cone[SKILL_SIZE][SKILL_SIZE];     // cone apontando para baixo (ápice na linha 0, centro)
    int cross[SKILL_SIZE][SKILL_SIZE];    // cruz centrada
    int octa[SKILL_SIZE][SKILL_SIZE];     // losango (|dr|+|dc|<=MID)

    // gera CONE
    for (int r=0;r<SKILL_SIZE;r++){
        for (int c=0;c<SKILL_SIZE;c++){
            int largura = r; // aumenta a cada linha
            cone[r][c] = ( (c>=MID-largura) && (c<=MID+largura) ) ? 1 : 0;
        }
    }
    // gera CRUZ
    for (int r=0;r<SKILL_SIZE;r++){
        for (int c=0;c<SKILL_SIZE;c++){
            cross[r][c] = (r==MID || c==MID) ? 1 : 0;
        }
    }
    // gera OCTAEDRO (losango)
    for (int r=0;r<SKILL_SIZE;r++){
        for (int c=0;c<SKILL_SIZE;c++){
            int dr = (r>MID)? r-MID : MID-r;
            int dc = (c>MID)? c-MID : MID-c;
            octa[r][c] = (dr+dc<=MID) ? 1 : 0;
        }
    }

    // --- ORIGENS DAS HABILIDADES NO TABULEIRO ---
    int coneR=3, coneC=4;   // centrado aqui
    int crossR=6, crossC=6;
    int octaR=4,  octaC=8;  // parte pode sair da borda; ignoramos fora

    // --- SOBREPOSIÇÃO: marca 5 onde habilidade==1 e board==0 ---
    // helper inline: aplica uma matriz 7x7 centrada em (oR,oC)
    // (sem funções, só repetimos o padrão)
    // aplica CONE
    for (int r=0;r<SKILL_SIZE;r++){
        for (int c=0;c<SKILL_SIZE;c++){
            if (cone[r][c]==1){
                int br = coneR + (r - MID);
                int bc = coneC + (c - MID);
                if (br>=0 && br<BOARD_SIZE && bc>=0 && bc<BOARD_SIZE){
                    if (board[br][bc]==0) board[br][bc]=5; // não sobrescreve navio
                }
            }
        }
    }
    // aplica CRUZ
    for (int r=0;r<SKILL_SIZE;r++){
        for (int c=0;c<SKILL_SIZE;c++){
            if (cross[r][c]==1){
                int br = crossR + (r - MID);
                int bc = crossC + (c - MID);
                if (br>=0 && br<BOARD_SIZE && bc>=0 && bc<BOARD_SIZE){
                    if (board[br][bc]==0) board[br][bc]=5;
                }
            }
        }
    }
    // aplica OCTAEDRO
    for (int r=0;r<SKILL_SIZE;r++){
        for (int c=0;c<SKILL_SIZE;c++){
            if (octa[r][c]==1){
                int br = octaR + (r - MID);
                int bc = octaC + (c - MID);
                if (br>=0 && br<BOARD_SIZE && bc>=0 && bc<BOARD_SIZE){
                    if (board[br][bc]==0) board[br][bc]=5;
                }
            }
        }
    }

    // --- SAÍDA ---
    // 0=agua, 3=navio, 5=area habilidade
    printf("\nTabuleiro 10x10 (0=agua, 3=navio, 5=habilidade)\n\n");
    for (int r=0;r<BOARD_SIZE;r++){
        for (int c=0;c<BOARD_SIZE;c++){
            printf("%d ", board[r][c]);
        }
        printf("\n");
    }

    return 0;
}

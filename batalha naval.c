#include <stdio.h>
#include <stdlib.h>

#define TAM 10              // Tamanho do tabuleiro
#define NAVIO 3             // Valor para representar navios
#define AGUA 0              // Valor para representar água
#define EF_HABILIDADE 5     // Valor para representar área afetada
#define H 5                 // Tamanho das matrizes de habilidade (5x5)

void exibirTabuleiro(int tabuleiro[TAM][TAM]) {
    printf("\n--- Tabuleiro Atual ---\n");
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Cone virado para baixo (tipo um triângulo isósceles)
void gerarCone(int matriz[H][H]) {
    int meio = H / 2;
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < H; j++) {
            if (j >= meio - i && j <= meio + i)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Cruz: linha e coluna central cheias
void gerarCruz(int matriz[H][H]) {
    int meio = H / 2;
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < H; j++) {
            if (i == meio || j == meio)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Octaedro (ou losango visto de frente)
void gerarOctaedro(int matriz[H][H]) {
    int meio = H / 2;
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < H; j++) {
            if (abs(i - meio) + abs(j - meio) <= meio)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Aplica matriz de habilidade no tabuleiro, respeitando limites
void aplicarHabilidade(int tabuleiro[TAM][TAM], int habilidade[H][H], int linhaOrigem, int colunaOrigem) {
    int offset = H / 2;
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < H; j++) {
            int linhaT = linhaOrigem - offset + i;
            int colunaT = colunaOrigem - offset + j;

            if (linhaT >= 0 && linhaT < TAM && colunaT >= 0 && colunaT < TAM) {
                if (habilidade[i][j] == 1 && tabuleiro[linhaT][colunaT] != NAVIO) {
                    tabuleiro[linhaT][colunaT] = EF_HABILIDADE;
                }
            }
        }
    }
}

int main() {
    int tabuleiro[TAM][TAM];
    int cone[H][H], cruz[H][H], octaedro[H][H];

    // Inicializa tudo com água
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            tabuleiro[i][j] = AGUA;

    // Posiciona navio horizontal na linha 2, coluna 1
    for (int i = 0; i < 3; i++)
        tabuleiro[2][1 + i] = NAVIO;

    // Posiciona navio vertical na linha 5, coluna 7
    for (int i = 0; i < 3; i++)
        tabuleiro[5 + i][7] = NAVIO;

    // Cria formas das habilidades
    gerarCone(cone);
    gerarCruz(cruz);
    gerarOctaedro(octaedro);

    // Aplica habilidades em posições fixas
    aplicarHabilidade(tabuleiro, cone, 1, 5);       // Cone no topo
    aplicarHabilidade(tabuleiro, cruz, 6, 2);       // Cruz no meio
    aplicarHabilidade(tabuleiro, octaedro, 7, 7);   // Octaedro mais abaixo

    // Exibe o resultado final
    exibirTabuleiro(tabuleiro);

    return 0;
}

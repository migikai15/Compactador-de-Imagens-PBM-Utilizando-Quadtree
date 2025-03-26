#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_X 1024
#define MAX_Y 768

int Uniforme(int cmcX, int fimX, int cmcY, int fimY, int imagem[MAX_X][MAX_Y]) {
    int primeiroPixel = imagem[cmcX][cmcY];
    for (int i = cmcX; i <= fimX; ++i) {
        for (int j = cmcY; j <= fimY; ++j) {
            if (imagem[i][j] != primeiroPixel) {
                return 0;
            }
        }
    }
    return 1;
}

void codificarImagem(int cmcX, int fimX, int cmcY, int fimY, int imagem[MAX_X][MAX_Y]) {
    if (cmcX > fimX || cmcY > fimY) {
        return;
    }

    if (Uniforme(cmcX, fimX, cmcY, fimY, imagem)) {
        printf("%c", imagem[cmcX][cmcY] == 1 ? 'P' : 'B');
    } else {
        printf("X");
        int meioX = (cmcX + fimX) / 2;
        int meioY = (cmcY + fimY) / 2;
        codificarImagem(cmcX, meioX, cmcY, meioY, imagem);
        codificarImagem(cmcX, meioX, meioY + 1, fimY, imagem);
        codificarImagem(meioX + 1, fimX, cmcY, meioY, imagem);
        codificarImagem(meioX + 1, fimX, meioY + 1, fimY, imagem);
    }
}

void processarArquivo(FILE *arquivo) {
    char tipo[3]; // Variável para armazenar o tipo do arquivo
    fscanf(arquivo, "%2s", tipo); // Lê os dois primeiros caracteres

    if (tipo[0] != 'P' || tipo[1] != '1') {
        printf("Tipo de arquivo inválido.\n");
        fclose(arquivo);
        exit(1);
    }

    char linha[256];
    fscanf(arquivo, "%255s", linha); // Lê a segunda linha

    if (linha[0] == '#') {
        printf("Segunda linha é um comentário. Ignorando...\n");
        fscanf(arquivo, "%255s", linha); // Avança para a terceira linha
    }

    int largura, altura;
    fscanf(arquivo, "%d %d", &largura, &altura); // Lê as dimensões da imagem

    if (largura > MAX_X || altura > MAX_Y) {
        printf("Tamanho da imagem excede o limite máximo de 1024x768.\n");
        fclose(arquivo);
        exit(1);
    }

    int imagem[MAX_X][MAX_Y];
    for (int i = 0; i < altura; ++i) {
        for (int j = 0; j < largura; ++j) {
            fscanf(arquivo, "%d", &imagem[i][j]); // Lê a matriz da imagem
        }
    }

    printf("Dimensões da imagem: %d x %d\n", largura, altura);
    printf("Matriz da imagem:\n");
    for (int i = 0; i < altura; ++i) {
        for (int j = 0; j < largura; ++j) {
            printf("%d ", imagem[i][j]); // Mostra a matriz da imagem
        }
        printf("\n");
    }

    printf("Código resultante: ");
    codificarImagem(0, largura - 1, 0, altura - 1, imagem);
    printf("\n");

    fclose(arquivo);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s [-f arquivo]\n", argv[0]);
        return 1;
    }

    char *nomeArquivo = argv[1];
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    processarArquivo(arquivo);

    return 0;
}

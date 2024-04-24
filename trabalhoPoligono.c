#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

struct vertices{
    float x;
    float y;
};

float areatriangulo(struct vertices v[], int tamanho);

int main(void) {
    FILE *arquivo;
    float n1, n2;
    int vertice;

    arquivo = fopen("trabalhoarea.txt", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1); 
    }

    fscanf(arquivo, "%d", &vertice);
    struct vertices v[vertice];
    
    /* // Ignorar a primeira linha
    fscanf(arquivo, "%*[^\n]"); */

    // Ler e armazenar os valores
    for (int i = 0; i < vertice; i++) {
        fscanf(arquivo, "%f %f", &n1, &n2);
        v[i].x = n1;
        v[i].y = n2;
        
    }


    float area = areatriangulo(v, vertice);

    printf("A area do poligono é: %.2f", area);
    fclose(arquivo);

    return 0;
}

float areatriangulo(struct vertices v[], int tamanho) {
    float area = 0;

    for (int i = 0; i < tamanho - 2; i++) {
        float M[3][3] = {
            {v[0].x, v[0].y, 1},
            {v[i + 1].x, v[i + 1].y, 1},
            {v[i + 2].x, v[i + 2].y, 1},
        };

        float det = 0;

        // Cálculo do determinante
        det = det + (M[0][0] * M[1][1] * M[2][2]);// 0 = 0 + 1*3*1 : 3      /// 0 = 0 + 1*6*1 : 6  
        det = det + (M[0][1] * M[1][2] * M[2][0]);// 3 = 3 + 2*1*5 : 13     /// 6 = 6 + 2*1*2 : 6 + 4 :10 
        det = det + (M[0][2] * M[1][0] * M[2][1]);// 13 = 13 + 1*4*6 : 37   ///10 = 10+ 1*5*5 : 10 + 25 : 35
        det = det - (M[2][0] * M[1][1] * M[0][2]);// 37 = 37 - 5*3*1 : 22   ///35 = 35- 2*6*1 : 35 - 12 : 23
        det = det - (M[2][1] * M[1][2] * M[0][0]);// 22 = 22 - 6*1*1 : 16   ///23 = 23- 5*1*1 : 23 - 5: 18
        det = det - (M[2][2] * M[1][0] * M[0][1]);// 16 = 16 - 1*4*2 : 8    ///18 = 18- 1*5*2 : 18 - 10: 8

        // Área do triângulo
        area += det / 2;// 0 = 8/2  /// 4 = 8/2
    }

    if (area < 0) {
        area = -area;
    }

    return area; // area = 8
}


// a area do primeiro triangulo é 4;
//a area do segundo triangulo é 4;

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

struct vertices{
    float x;
    float y;
};//struct que armazena os vertices;

//esboço das funções
float areatriangulo(struct vertices v[], int tamanho);

int main(void) {
    FILE *arquivo;
    float n1, n2;
    int vertice;

    arquivo = fopen("trabalhoarea.txt", "r");// abre o arquivo em modo de leitura

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1); 
    }

    fscanf(arquivo, "%d", &vertice); // armazena quantidade de vertices
    struct vertices v[vertice]; // cria struct com a qtd de vertices 
    

    // Ler e armazenar os valores
    for (int i = 0; i < vertice; i++) {
        fscanf(arquivo, "%f %f", &n1, &n2);
        v[i].x = n1;
        v[i].y = n2;
        
    }


    float area = areatriangulo(v, vertice); // chama a função 

    printf("A area do poligono é: %.2f", area); // imprime o valor na tela
    fclose(arquivo);

    return 0;
}

// Função que calcula a area do poligono de acordo com a soma da area dos triangulos, o calculo é feito por meio do determinante da matriz;
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
        det = det + (M[0][0] * M[1][1] * M[2][2]);
        det = det + (M[0][1] * M[1][2] * M[2][0]); 
        det = det + (M[0][2] * M[1][0] * M[2][1]);
        det = det - (M[2][0] * M[1][1] * M[0][2]);
        det = det - (M[2][1] * M[1][2] * M[0][0]);
        det = det - (M[2][2] * M[1][0] * M[0][1]);

        // Área do triângulo
        area += det / 2;
    }

    if (area < 0) {
        area = -area;
    }

    return area; 
}

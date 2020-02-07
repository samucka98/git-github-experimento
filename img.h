#ifndef IMG_H
#define IMG_H

// TAD-2: Imagem - Assinatura dos tipos
typedef struct pixel Pixel;
typedef struct imagem Imagem;

// Protótipos das funções da TAD-2
int linhaIMG(Imagem *img);
int colunaIMG(Imagem *img);
int **liberaMatriz(int linha, int coluna, int **mrt);
void createDirImg(char *nameDirImg); // Criar diretorio, somente professor pode criar diretorio
Pixel *alocapixel(int altura, int largura);
Imagem *alocaImagem(void);
Imagem *createImage(void);
void exibeImagem(Imagem *img);
int **alocaMatriz(int linha, int coluna);

int **matriz_recebe_Imagem(Imagem *im);
Imagem *imagem_recebe_matriz(int **m, int linha, int coluna);

void exibeMatriz(int **mrt, Imagem *img);
int *vetor_carrega_arquivo(int *tam, int id);
Imagem *loadImage(int id);
void saveImage(Imagem *img, int idDiscente); // Em arquivo txt
Imagem *copyImage(Imagem *img); // Em tempo de execução


// Funções de processamento de imagem
int valorMaximo(Imagem *img);
int valorMinimo(Imagem *img);
float distanciaEuclidiana(Imagem *img);
float distanciaManhattan(Imagem *img);

int devolveInt(int *v, int tam);
int recebeKernel(int *v, int tam);
int *pegaBordas(int **matKernel, int *tam, int kernel);
int **localBinary(int **mat, int n, int m, int kernel);

Imagem *matrizDeCoocorrencia(Imagem *img);
int **filtroDeMedia(Imagem *img);
void ordena(int *v, int tam);
int recebeKernelFMED(int *v, int tam);
int **filtrosDeMediana(Imagem *img);

#endif
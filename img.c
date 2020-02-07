#include "img.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>

struct pixel {
    int x, y, valor_pixel;
};

struct imagem {
    int altura, largura;
    Pixel *pixels_imagem; // Variar de 0 ate 255
};

int linhaIMG(Imagem *img) {
    return img->altura;
}

int colunaIMG(Imagem *img) {
    return img->largura;
}

// Funções da TAD-2
int **liberaMatriz(int linha, int coluna, int **mrt) {
    
    for(int i = 0; i < linha; i++)
        free(mrt[i]);
    
    free(mrt);
    return NULL;
}

void createDirImg(char *nameDirImg) {
	if(mkdir(nameDirImg, S_IRUSR | S_IWUSR | S_IXUSR) != 0);
}

Pixel *alocapixel(int altura, int largura) {
	
	Pixel *px = (Pixel *) malloc(sizeof(Pixel) * altura * largura);

	return px;
}

Imagem *alocaImagem(void) {
	
	Imagem *img = (Imagem *) malloc(sizeof(Imagem));

	return img;
}

// Função de criar imagem...
Imagem *createImage(void) { 
	
	Imagem *img = alocaImagem();

	printf("Informe a altura da imagem: ");
	scanf("%d", &img->altura);

	printf("Informe a largura da imagem: ");
	scanf("%d", &img->largura);

	img->pixels_imagem = alocapixel(img->altura, img->largura);

	int iPixel = 0;
	for(int i = 0; i < img->altura; ++i){
		for(int j = 0; j < img->largura; ++j){
			
			img->pixels_imagem[iPixel].x = i;
			img->pixels_imagem[iPixel].y = j;

			img->pixels_imagem[iPixel].valor_pixel = rand() % 256;
			
			iPixel++;
		}
	}

	return img;
}

// Exibe matriz do tipo imagem...
void exibeImagem(Imagem *img) { // 
	
	int iPixel = 0;
	for(int i = 0; i < img->altura; i++){
		for(int j = 0; j < img->largura; j++){
			printf("[%*d]", 3, img->pixels_imagem[iPixel++].valor_pixel);
		}
		printf("\n");
	}
}

// Aloca uma matriz int...
int **alocaMatriz(int linha, int coluna) {
	
	int **mrt = (int **) calloc(sizeof(int *), linha);

	for(int i = 0; i < linha; i++)
		mrt[i] = (int *) calloc(sizeof(int), coluna);

	return mrt;
}

// Converte uma matriz do Tipo imagem para uma matriz Int...
int **matriz_recebe_Imagem(Imagem *im) {
	int linha = im->altura;
	int coluna = im->largura;
	int **m;

	printf("Linha: %d\n",im->altura);
	printf("Coluna: %d\n", im->largura);

	printf("Valor pixel 0: %d\n", im->pixels_imagem[0].valor_pixel);

	m = alocaMatriz(linha, coluna);

	int iPixel = 0;
	for(int i = 0; i < linha; ++i)
		for(int j = 0; j < coluna; ++j) {
			m[i][j] = im->pixels_imagem[iPixel++].valor_pixel;
		}

	return m;
}

// Converte uma matriz Int para uma matriz do tipo Imagem...
Imagem *imagem_recebe_matriz(int **m, int linha, int coluna) {
	Imagem *im;
	im = alocaImagem();
	im->altura = linha;
	im->largura = coluna;
	im->pixels_imagem = alocapixel(linha, coluna);

	int iPixel = 0;

	for(int i = 0; i < linha; ++i){
		for(int j = 0; j < coluna; ++j){
			im->pixels_imagem[iPixel].valor_pixel = m[i][j];
			im->pixels_imagem[iPixel].x = i;
			im->pixels_imagem[iPixel].y = j;
			iPixel++;
		}
	}

	return im;
}

// Exibe uma matriz Int, extraindo de uma matriz do tipo imagem seus atributos largura e altura...
void exibeMatriz(int **mrt, Imagem *img) {
	
	for(int i = 0; i < img->altura; i++) {
		for(int j = 0; j < img->largura; j++) {
			printf("[%d]", mrt[i][j]);
		}
		printf("\n");
	}
}

Imagem *loadImage(int id) {

    char *nameFile = (char *) malloc(sizeof(char));
	char *prefix = (char *) malloc(sizeof(char));
    strcpy(prefix, ".img/");
	printf("Para facilitar na busca futura por imagens e recomendado que o nome seja sugestivo!\n");
	printf("Informe o nome da imagem para carregar: ");

	scanf("%s",nameFile);
    strcat(prefix, nameFile);
	FILE *fPtr; int **mrt, x, y;

    if((fPtr = fopen(prefix, "r")) == NULL) {
        printf("\n Erro na abertura do arquivo!");
        exit(1);
    } else {

        fscanf(fPtr, "%d %d", &x, &y);

        mrt = alocaMatriz(x, y);

        while(!feof(fPtr)) {

            for(int i = 0; i < x; i++)
                for(int j = 0; j < y; j++)
                    fscanf(fPtr, "%d ", &mrt[i][j]);
        }

        fclose(fPtr);
    }

	printf("\nMATRIZ SALVA...\n");

	for(int i = 0; i < x; i++) {
		for(int j = 0; j < y; j++) {
			printf("%d ", mrt[i][j]);
		}
		printf("\n");
	}

	printf("\n");

    Imagem *img = imagem_recebe_matriz(mrt, x, y);

    return img;
}

void saveImage(Imagem *img, int idDiscente) {
    	
    if(img != NULL) {

		//char *id = (char *) malloc(sizeof(char));

		/**
		 * @Nota:
		 * formatação do nome dos arquivos
		 * no final de cada arquivo leva a numeroação do id do usuario
		*/

		char *nameFile = (char *) malloc(sizeof(char));
		char *prefix = (char *) malloc(sizeof(char));
        strcpy(prefix, ".img/");
		printf("Para facilitar na busca futura por imagens e recomendado que o nome seja sugestivo!\n");
		printf("Informe o nome da imagem para salvar: ");

		scanf("%s",nameFile);
        strcat(prefix, nameFile);
	    FILE *fPtr = fopen(prefix, "w");

	    if(fPtr == NULL) {
	    	printf("Erro ao salvar imagem.\n");
            exit(1);
        }
		
		fprintf(fPtr, "%d %d\n", img->altura, img->largura);
        int indicie = 0;
		for(int i = 0; i < img->altura; i++) {
			for(int j = 0; j < img->largura; j++) {
				fprintf(fPtr, "%d ", img->pixels_imagem[indicie].valor_pixel);
                indicie++;
            }

			fprintf(fPtr, "\n");
		}


		printf("Imagem salva.\n\n");
		fclose(fPtr);

        free(nameFile);
        free(prefix);
	} else {
		printf("\nA imagem nao existe.\n");
	}
	
}

Imagem *copyImage(Imagem *img) {

	Imagem *new_img;

	new_img = alocaImagem();
	new_img->largura = img->largura;
	new_img->altura = img->altura;

	new_img->pixels_imagem = alocapixel(img->altura, img->largura);

	int iPixel = 0;

	for(int i = 0; i < img->altura; ++i){
		for(int j = 0; j < img->largura; ++j){
			new_img->pixels_imagem[iPixel].x = i;
			new_img->pixels_imagem[iPixel].y = j;
			new_img->pixels_imagem[iPixel].valor_pixel = img->pixels_imagem[iPixel].valor_pixel; //recebe valor do pixel da struct parâmetro
			iPixel++;
		}
	}

	return new_img;
}

int valorMaximo(Imagem *img) {

    int **mrt = alocaMatriz(img->altura, img->largura);

    mrt = matriz_recebe_Imagem(img);
	
	int valorMaximo = mrt[0][0];

	for(int i = 0; i < img->altura; ++i){
		for(int j = 0; j < img->largura; ++j){
			if(mrt[i][j] > valorMaximo){
				valorMaximo = mrt[i][j];
			}
		}
	}

	return valorMaximo;
}

int valorMinimo(Imagem *img) {

    int **mrt = alocaMatriz(img->altura, img->largura);

    mrt = matriz_recebe_Imagem(img);
	
	int menorElemento = mrt[0][0];

	for(int i = 0; i < img->altura; ++i){
		for(int j = 0; j < img->largura; ++j){
			if(mrt[i][j] < menorElemento){
				menorElemento = mrt[i][j];
			}
		}
	}

	return menorElemento;
}

float distanciaEuclidiana(Imagem *img) {

    int **mrt = alocaMatriz(img->altura, img->largura);

    int x1, x2, y1, y2; int flag = 1;
    mrt = matriz_recebe_Imagem(img);
    
    do {
        printf("Informe as coordenadas requeridas abaixo!\n");
        printf("X1: "); scanf("%d", &x1);
        printf("X2: "); scanf("%d", &x2);
        printf("Y1: "); scanf("%d", &y1);
        printf("Y2: "); scanf("%d", &y2);
        printf("\n");

    } while(x1 < 0 || x1 > img->altura || x2 < 0 || x2 > img->altura || y1 < 0 || y1 > img->largura || y2 < 0 || y2 > img->largura);

    return (float)sqrt(pow(x2 - x1, 2.0) + pow(y2 - y1, 2.0));
}

float distanciaManhattan(Imagem *img) {

    int **mrt = alocaMatriz(img->altura, img->largura);

    int x1, x2, y1, y2; int flag = 1;
    mrt = matriz_recebe_Imagem(img);
    
    do {
        printf("Informe as coordenadas requeridas abaixo!\n");
        printf("X1: "); scanf("%d", &x1);
        printf("X2: "); scanf("%d", &x2);
        printf("Y1: "); scanf("%d", &y1);
        printf("Y2: "); scanf("%d", &y2);
        printf("\n");

    } while(x1 < 0 || x1 > img->altura || x2 < 0 || x2 > img->altura || y1 < 0 || y1 > img->largura || y2 < 0 || y2 > img->largura);

    return (float)sqrt(pow(x2 - x1, 2.0) + pow(y2 - y1, 2.0));
}

int devolveInt(int *v, int tam) {

    int num = 0;
    int j = 0;
    for(int i = tam - 1; i >= 0; --i){
        float exp = i;
        num += (pow(2,exp) * v[j++]); //transforma o vetor de binários em um único valor inteiro
    }

    return num;
}

int recebeKernel(int *v, int tam) {

    int meio = v[tam-1]; //pega o valor central
   // printf("Meio = %d\n", meio);
    v[tam-1] = -1; //adiciona -1 ao centro do kernel, pois é impossível comparar com este valor, pois o pixels vão de 0 a 255
    int vBin[tam-1]; //vetor binário, tam-1 porquê o valor central foi descartado 
    int iBin = 0;//Indice do vetor que transforma números em binários
    for(int i = 0; i < tam-1; ++i){
        if(v[i] != -1 && meio > v[i]){
            vBin[iBin++] = 0; //se meio for maior que valor vetor recebe 0
        }else if(v[i] != -1 && meio < v[i])
            vBin[iBin++] = 1; //se meio vetor for menor que vetor recebe 1 
    }

    return devolveInt(vBin, iBin); // função que faz a conversão do vetor de binário para um inteiro
}

int *pegaBordas(int **matKernel, int *tam, int kernel) {
    int indiceKernel = 0;
    int *v = (int*)malloc(sizeof(int) * 9);
    
    //Borda de cima
    for(int a = 0; a < kernel; ++a){
        v[indiceKernel] = matKernel[0][a];
        ++indiceKernel;
    }
    
    //Borda direita
    for(int a = 1; a < kernel; a++){
        v[indiceKernel] = matKernel[a][kernel-1];
        ++indiceKernel;   
    }

    //Borda baixo
    for(int a = kernel-2; a >= 0; --a){
        v[indiceKernel] = matKernel[kernel-1][a];   
        ++indiceKernel;
    }

    //Borda esquerda
    for(int a = kernel-2; a >= 1; --a){
        v[indiceKernel] = matKernel[a][0];   
        ++indiceKernel;
    }

    //Valor do meio
    v[indiceKernel++] = matKernel[kernel/2][kernel/2];

    *tam = indiceKernel;
    return v;

    free(v);
}

int **localBinary(int **mat, int n, int m, int kernel) {
    
    int **newMat = alocaMatriz(n, m); //Matriz que vai retornar a foto alterada
    int **matKernel = alocaMatriz(3,3);
    int *v = (int*) malloc(sizeof(int) * 9);

    int indiceKernel = 0;
    int lk = 0;
    int ck = 0;


    for (int i = 0 ; i < n; i++) {
        for (int j = 0; j < m; j++) {
 
            for (int l = i; l < i+kernel; l++) {
                for (int c = j ; c < j+kernel; c++) {

                    matKernel[lk][ck] = mat[l%n][c%m];                
                    ck++;
                }
                ck = 0;
                lk++;
            }
            lk = 0;
            
            v = pegaBordas(matKernel, &indiceKernel, kernel);
            free(v);

            newMat[i][j] = recebeKernel(v, indiceKernel); //transforma valores do kernel em binários e retorna um valor inteiro convertido do binário
            indiceKernel = 0; //zera o indice do kernel para que este pegue novos grupos dentro da matriz
           
        }
    }

    return newMat;

    liberaMatriz(n, m, newMat);
}

Imagem *matrizDeCoocorrencia(Imagem *img) {

	int angulo, count = 0;
	int linha = img->altura;
	int coluna = img->largura;

	printf("Digite o Angulo(0°, 45°, 90°, 135°): ");
	scanf("%d",&angulo);

	int **matriz, **resultante;

	resultante = alocaMatriz(linha, coluna);//alocando a matriz que ira ser retornada.

	matriz = matriz_recebe_Imagem(img);//recebendo a struct e transformando em matriz.

	if(angulo == 0) {
		///for das coordenadas a serem buscadas.
        for(int x = 0;x < linha; x++) {
            for(int y = 0; y < coluna; y++) {
                //for para comparação de coordenadas
                for(int i = 0; i < linha; i++) {
                    for(int j = 0; j < coluna; j++) {

                        if(x == matriz[i][j]) {
                            if(y == matriz[i][j+1] && j+1 < coluna) {
                                count++;
                            }
                        }
                    }
                }

				resultante[x][y] = count;
                count = 0;
            }
        }

		Imagem *coocorrencia;
        coocorrencia = imagem_recebe_matriz(resultante, linha, coluna);
		
		return coocorrencia;
		
		liberaMatriz(linha, coluna, matriz);
		liberaMatriz(linha, coluna, resultante);

	} else if(angulo == 45) {
		//for das coordenadas a serem buscadas
		for(int x = 0;x < linha;x ++) {
            for(int y = 0; y < coluna; y++) {
                //for para comparação de coordenadas
                for(int i = 0; i < linha; i++) {
                    for(int j = 0; j < coluna; j++) {

                        if(x == matriz[i][j]) {
                            if(i-1 >= 0 && j+1 < coluna && y == matriz[i-1][j+1]) {
                                count++;
                            }
                        }
                    }
                }

                resultante[x][y] = count;
                count = 0;
            }
		}

		Imagem *coocorrencia;
		coocorrencia = imagem_recebe_matriz(resultante, linha, coluna);
		
		return coocorrencia;

        liberaMatriz(linha, coluna, matriz);
		liberaMatriz(linha, coluna, resultante);

	} else if(angulo == 90) {
		//for das coordenadas a serem buscadas.
		for(int x = 0;x < linha;x ++) {
            for(int y = 0; y < coluna; y++) {
                //for para comparação de coordenadas
                for(int i = 0; i < linha; i++) {
                    for(int j = 0; j < coluna; j++) {

                        if(x == matriz[i][j]) {
                            if(i-1 >= 0 && y == matriz[i-1][j]) {
                                count++;
                            }
                        }
                    }
                }

                resultante[x][y] = count;
                count = 0;
            }
        }

		Imagem *coocorrencia;
		coocorrencia = imagem_recebe_matriz(resultante, linha, coluna);
		
		return coocorrencia;
		
		liberaMatriz(linha, coluna, matriz);
		liberaMatriz(linha, coluna, resultante);

	} else if(angulo == 135) {
		//for das coordenadas a serem buscadas

		for(int x = 0;x < linha; x++) {
            for(int y = 0; y < coluna; y++) {
                //for para comparação de coordenadas
                for(int i = 0; i < linha; i++) {
                    for(int j = 0; j < coluna; j++) {
                        if(x == matriz[i][j]) {
                            if(i-1 >= 0 && j-1 >= 0 && y == matriz[i-1][j-1]) {
                                count++;
                            }
                        }
                    }
                }
                resultante[x][y] = count;
                count = 0;
            }
        }

		Imagem *coocorrencia;
        coocorrencia = imagem_recebe_matriz(resultante, linha, coluna);
		
        exibeMatriz(resultante, img);

		return coocorrencia;
		
		liberaMatriz(img->altura, img->largura, matriz);
		liberaMatriz(img->altura, img->largura, resultante);

	} else {
		liberaMatriz(img->altura, img->largura, matriz);
		liberaMatriz(img->altura, img->largura, resultante);
		printf("Ângulo Ivalido!\n");
		return NULL;
	}    
}

int **filtroDeMedia(Imagem *img) {
     
    int n = img->altura; 
    int m = img->largura;
    int **mrt = matriz_recebe_Imagem(img); 
    int kernel = 3;

	int **newMat = alocaMatriz(n, m); int soma;
    
	for (int i = 0 ; i < n; i++) {
        for (int j = 0; j < m; j++) {
            soma = 0;
            for (int l = i; l < i+kernel; l++) {
                for (int c = j ; c < j+kernel; c++) {
                    soma += mrt[l%n][c%m];
                }
            }
            newMat[i][j] = (int)soma / (kernel*kernel);
        }
    }
    return newMat;
}

void ordena(int *v, int tam) {

    int chave;

    for(int i = 1; i < tam; i++){
        chave = v[i];//Definição de valor para comparação
        int j = i - 1;
        
        while((j >= 0) && (chave < v[j])){
	        v[j+1] = v[j];//Segunda movimentação
            j--;
        }
        v[j+1] = chave;//Definição de valor para comparação
    }
}

int recebeKernelFMED(int *v, int tam) {
    
    int mediana;
    int meio = tam/2;

    ordena(v, tam);

    if(tam % 2 == 0){ // caso quantidade de amostras do vetor sejam pares
        return (v[meio-1] + v[meio]) / 2; // meio-1 pois vetor inicia do indice 0 --  3, [5], [7], 9
    }else //caso sejam ímpares
        return v[meio]; //3, [5], 9
}

int **filtrosDeMediana(Imagem *img) {

    int n = img->altura; 
    int m = img->largura;
    int **mrt = matriz_recebe_Imagem(img); 
    int kernel = 3;
    
    int **newMat = alocaMatriz(n, m);
    int **matKernel = alocaMatriz(kernel, kernel);
    int indiceKernel = 0;
    int vetor[kernel * kernel];

    for (int i = 0 ; i < n; i++) {
        for (int j = 0; j < m; j++) {
 
            for (int l = i; l < i+kernel; l++) {
                for (int c = j ; c < j+kernel; c++) {
                    vetor[indiceKernel++] = mrt[l%n][c%m];       
                }
            }
            newMat[i][j] = recebeKernelFMED(vetor, indiceKernel);
            indiceKernel = 0;
           
        }
    }

    return newMat;
}
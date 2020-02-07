/**
 * Disciplina: Estruturas de dados 1
 * Atividade: Trabalho avaliativo TAD
 * Data: 28.10.2019 finalizado
 * Integrantes:
 * 
 * Josean mário moreira rodrigues
 * Rafael Ramos
 * Samuel Ibiapino Lima
*/

#include "menu.h"
#include "user.h"
#include "img.h"
#include <stdio.h>
#include <stdlib.h>

#define ROOT_KEY 5000 // Somente esta matricula entra no modo gerenciamento usuario

void main() {

    /**
     * @Nota:
     * Variavel: sizeDoc e sizeDis - controlam o tamanho do vetor.
     * Variavel: iDoc e iDis - indicies dos vetores.
    */

    Docente *ArrayDocente = NULL; int sizeDoc = 0, iDoc = 0;
    Discente *ArrayDiscente = NULL; int sizeDis = 0, iDis = 0;
    
    Imagem *img = NULL;
    Imagem *imgCopy = NULL;

    int init = verifySystem(&sizeDoc, &sizeDis);

    if(init == 0) {

        createDirUser(".user"); // Criação de diretorio usuarios.
        createDirImg(".img"); // Criação de diretorio de imagens.

        printf("BEM VINDO AO SAG(Sistema de gerenciamento academico)\n\n");
        printf("Sistema inicializado pela primeira vez com sucesso!\n");
        printf("\n Pressione ENTER para continuar");
        getchar(); scanf("c\n");
    }

    if(init == 1) {
        
        ArrayDocente = loadDocente(ArrayDocente, sizeDoc, &iDoc);
        ArrayDiscente = loadDiscente(ArrayDiscente, sizeDis, &iDis);

        printf("%d docentes cadastrados recuperados | %d discentes cadastrados recuperados\n", sizeDoc, sizeDis);
        printf("\n Pressione ENTER para continuar");
        getchar(); scanf("c\n");
    }

    int selectPrincipal, Matricula;

    do {
        system("clear");

        menuPrincipal();
        scanf("%d", &selectPrincipal);

        if(selectPrincipal == 1) {
            system("clear");
            // Alunos matricula a partir de 1000
            // Professores de 1 a 999
            
            login();
            scanf("%d", &Matricula);

            if(Matricula >= 0 && Matricula < 1000) {
                system("clear");

                printf("Area do professor!\n");

                printf("Pressione ENTER\n");
                getchar(); scanf("c\n");
            
            } else if(Matricula >= 1000) {
                system("clear");

                int password; int idKey; // idKey recebe o retiorno da função password 0 acesso negado 1 permitido

                printf("Informe a senha para acessar as funcionalidades do sistema!\n");
                printf("Digite aqui: ");
                scanf("%d", &password);

                idKey = passwordVerify(ArrayDiscente, sizeDis, Matricula, password);

                if(idKey) {

                    int selectFuncionalidades;
                    
                    do {
                        system("clear");

                        menuFuncionalidades();
                        scanf("%d", &selectFuncionalidades);

                        if(selectFuncionalidades == 1) {
                            
                            int selectImagem;
                            
                            do {
                                system("clear");

                                menuImagem();
                                scanf("%d", &selectImagem);

                                if(selectImagem == 1) {

                                    int selectAqruivo;

                                    do {
                                        system("clear");

                                        arquivoIMG();
                                        scanf("%d", &selectAqruivo);

                                        if(selectAqruivo == 1) {
                                            system("clear");

                                            printf("Nova imagem...\n");
                                            img = createImage();

                                            printf("Pressione ENTER\n");
                                            getchar(); scanf("c\n");
                                        
                                        } else if(selectAqruivo == 2) {
                                            system("clear");

                                            printf("Funcao Carregar imagem...\n");
                                            
                                            int id = retornaIdPorMatriculaDiscente(ArrayDiscente, sizeDis, Matricula);
                                            img = loadImage(id);

                                            printf("Pressione ENTER\n");
                                            getchar(); scanf("c\n");

                                        } else if(selectAqruivo == 3) {
                                            system("clear");

                                            printf("Funcao Salvar Imagem...\n");
                                            
                                            int id = retornaIdPorMatriculaDiscente(ArrayDiscente, sizeDis, Matricula);
                                            saveImage(img, id);

                                            printf("Pressione ENTER\n");
                                            getchar(); scanf("c\n");

                                        } else if(selectAqruivo == 4) {
                                            system("clear");

                                            printf("Funcao Copiar Imagem...\n");
                                            imgCopy = copyImage(img);

                                            printf("Pressione ENTER\n");
                                            getchar(); scanf("c\n");

                                        } else if(selectAqruivo == 5) {
                                            system("clear");

                                            printf("Salvar Copia de Imagem...\n");
                                            int id = retornaIdPorMatriculaDiscente(ArrayDiscente, sizeDis, Matricula);
                                            saveImage(imgCopy, id);

                                            printf("Pressione ENTER\n");
                                            getchar(); scanf("c\n");
                                        }

                                    } while(selectAqruivo != 0);

                                } else if(selectImagem == 2) {
                                    
                                    int selectFuncionalidadesImagem;
                                    
                                    do {
                                        system("clear");

                                        funcoesImagem();
                                        scanf("%d", &selectFuncionalidadesImagem);

                                        if(selectFuncionalidadesImagem == 1) {
                                            system("clear");
                                            printf("Funcao Valor maximo.\n");
                                            
                                            int id = retornaIdPorMatriculaDiscente(ArrayDiscente, sizeDis, Matricula);
                                            img = loadImage(id);
                                            
                                            int maxValue = valorMaximo(img);

                                            printf("Valor maximo da imagem: %d\n", maxValue);

                                            printf("Pressione ENTER\n");
                                            getchar(); scanf("c\n");

                                        } else if(selectFuncionalidadesImagem == 2) {
                                            system("clear");
                                            printf("Funcao Valor minimo.\n");

                                            int id = retornaIdPorMatriculaDiscente(ArrayDiscente, sizeDis, Matricula);
                                            img = loadImage(id);
                                            
                                            int minValue = valorMinimo(img);

                                            printf("Valor minimo da imagem: %d\n", minValue);

                                            printf("Pressione ENTER\n");
                                            getchar(); scanf("c\n");

                                        } else if(selectFuncionalidadesImagem == 3) {
                                            system("clear");
                                            printf("Funcao Distancia euclidiana.\n");

                                            int id = retornaIdPorMatriculaDiscente(ArrayDiscente, sizeDis, Matricula);
                                            img = loadImage(id);

                                            float euclidiana = distanciaEuclidiana(img);

                                            printf("Distancia eucclidiana: %f", euclidiana);

                                            printf("Pressione ENTER\n");
                                            getchar(); scanf("c\n");

                                        } else if(selectFuncionalidadesImagem == 4) {
                                            system("clear");
                                            printf("Funcao Distancia manhattan.\n");

                                            int id = retornaIdPorMatriculaDiscente(ArrayDiscente, sizeDis, Matricula);
                                            img = loadImage(id);

                                            float manhattan = distanciaManhattan(img);

                                            printf("Distancia manhattan: %f", manhattan);

                                            printf("Pressione ENTER\n");
                                            getchar(); scanf("c\n");

                                        } else if(selectFuncionalidadesImagem == 5) {
                                            system("clear");
                                            printf("Funcao Local binary pattern.\n");

                                            int id = retornaIdPorMatriculaDiscente(ArrayDiscente, sizeDis, Matricula);
                                            img = loadImage(id);

                                            int linha = linhaIMG(img);
                                            int coluna = colunaIMG(img);
                                            int **mrt = alocaMatriz(linha, coluna);

                                            mrt = matriz_recebe_Imagem(img);

                                            int **mrtBinary;
                                            int kernel = 3;

                                            mrtBinary = localBinary(mrt, linha, coluna, kernel);
                                            liberaMatriz(linha, coluna, mrt);

                                            printf("\nDeseja salvar?\n");
                                            printf("1 - sim.\n");
                                            int saveFilter;
                                            scanf("%d", &saveFilter);
                                            printf("ok");

                                            if(saveFilter == 1) {
                                                img = imagem_recebe_matriz(mrtBinary, linha, coluna);
                                                saveImage(img, id);
                                            }

                                            printf("Pressione ENTER\n");
                                            getchar(); scanf("c\n");

                                        } else if(selectFuncionalidadesImagem == 6) {
                                            system("clear");
                                            printf("Funcao Matriz de coocorrencia.\n");

                                            int id = retornaIdPorMatriculaDiscente(ArrayDiscente, sizeDis, Matricula);
                                            img = loadImage(id);

                                            img = matrizDeCoocorrencia(img);

                                            printf("\nDeseja salvar?\n");
                                            printf("1 - sim.\n");
                                            int saveFilter;
                                            scanf("%d", &saveFilter);

                                            if(saveFilter == 1) saveImage(img, id);

                                            printf("Pressione ENTER\n");
                                            getchar(); scanf("c\n");

                                        } else if(selectFuncionalidadesImagem == 7) {
                                            system("clear");
                                            printf("Funcao Filtro de media.\n");

                                            int id = retornaIdPorMatriculaDiscente(ArrayDiscente, sizeDis, Matricula);
                                            img = loadImage(id);

                                            int linha = linhaIMG(img);
                                            int coluna = colunaIMG(img);
                                            int **mrt = alocaMatriz(linha, coluna);

                                            mrt = filtroDeMedia(img);

                                            printf("\nDeseja salvar?\n");
                                            printf("1 - sim.\n");
                                            int saveFilter;
                                            scanf("%d", &saveFilter);

                                            if(saveFilter == 1) {
                                                img = imagem_recebe_matriz(mrt, linha, coluna);
                                                saveImage(img, id);
                                            }

                                            printf("Pressione ENTER\n");
                                            getchar(); scanf("c\n");

                                        } else if(selectFuncionalidadesImagem == 8) {
                                            system("clear");
                                            printf("Funcao Filtro de mediana.\n");

                                            int id = retornaIdPorMatriculaDiscente(ArrayDiscente, sizeDis, Matricula);
                                            img = loadImage(id);

                                            int linha = linhaIMG(img);
                                            int coluna = colunaIMG(img);
                                            int **mrt = alocaMatriz(linha, coluna);

                                            mrt = filtrosDeMediana(img);

                                            printf("\nDeseja salvar?\n");
                                            printf("1 - sim.\n");
                                            int saveFilter;
                                            scanf("%d", &saveFilter);

                                            if(saveFilter == 1) {
                                                img = imagem_recebe_matriz(mrt, linha, coluna);
                                                saveImage(img, id);
                                            }

                                            printf("Pressione ENTER\n");
                                            getchar(); scanf("c\n");

                                        }

                                    } while(selectFuncionalidadesImagem != 0);
                                }

                            } while(selectImagem != 0);
                        }
                        
                    } while(selectFuncionalidades != 0);
                }
            }

        } else if(selectPrincipal == 2) {
            system("clear");

            login();
            scanf("%d", &Matricula);

            if(Matricula == ROOT_KEY) {

                printf("Area do Root\n");

                int selectUsuario;

                do {
                    system("clear");
                    
                    menuUsuario();
                    scanf("%d", &selectUsuario);

                    if(selectUsuario == 1) {
                        system("clear");
                        printf("Cadastrar Docente.\n");
                        
                        ArrayDocente = createDocente(ArrayDocente, sizeDoc);
                        ArrayDocente = cadastroDocente(ArrayDocente, sizeDoc, iDoc);
                        ++sizeDoc;
                        ++iDoc;

                        addInfoSys(sizeDoc, sizeDis);

                    } else if(selectUsuario == 2) {
                        system("clear");
                        printf("Remover Docente.\n");
                        
                        ArrayDocente = removerDocente(ArrayDocente, sizeDoc, ArrayDiscente, sizeDis);
                        --sizeDoc;

                        addInfoSys(sizeDoc, sizeDis);

                    } else if(selectUsuario == 3) {
                        system("clear");
                        printf("Alterar Docente.\n");

                        ArrayDocente = alterarDocente(ArrayDocente, sizeDoc);

                    } else if(selectUsuario == 4) {
                        system("clear");
                        printf("Buscar Docente.\n");

                        buscarDocente(ArrayDocente);

                    } else if(selectUsuario == 5) {
                        system("clear");
                        printf("Docentes Cadastrados.\n");

                        mostrarDocente(ArrayDocente, sizeDoc);

                        printf("Pressione ENTER\n");
                        getchar(); scanf("c\n");

                    } else if(selectUsuario == 6) {
                        system("clear");
                        printf("Cadastrar Discente.\n");

                        ArrayDiscente = createDiscente(ArrayDiscente, sizeDis);
                        ArrayDiscente = cadastroDiscente(ArrayDiscente, sizeDis, iDis);
                        ++sizeDis;
                        ++iDis;

                        addInfoSys(sizeDoc, sizeDis);

                    } else if(selectUsuario == 7) {
                        system("clear");
                        printf("Remover Discente.\n");

                        ArrayDiscente = removerDiscente(ArrayDiscente, sizeDis, ArrayDocente, sizeDoc);
                        --sizeDis;

                        addInfoSys(sizeDoc, sizeDis);

                    } else if(selectUsuario == 8) {
                        system("clear");
                        printf("Funcao Alterar Discente.\n");

                        ArrayDiscente = alterarDiscente(ArrayDiscente, sizeDis);

                    } else if(selectUsuario == 9) {
                        system("clear");
                        printf("Buscar Discente.\n");

                        buscarDiscente(ArrayDiscente);

                    } else if(selectUsuario == 10) {
                        system("clear");
                        printf("Discentes Cadastrados.\n");

                        mostrarDiscente(ArrayDiscente, sizeDis);

                        printf("Pressione ENTER\n");
                        getchar(); scanf("c\n");

                    } else if(selectUsuario == 11) {
                        system("clear");
                        printf("Listar Alunos de Orientador.\n");

                        listarAlunoDeOrientador(ArrayDocente, sizeDoc, ArrayDiscente, sizeDis);

                    } else if(selectUsuario == 12) {
                        system("clear");
                        printf("Alunos sem Orientador.\n");

                        listarAlunosSemOrientador(ArrayDiscente, sizeDis);

                    } else if(selectUsuario == 13) {
                        system("clear");
                        printf("Mudar Orientador de Aluno.\n");

                        mudarOrientadorDeAluno(ArrayDocente, sizeDoc, ArrayDiscente, sizeDis);

                    } else if(selectUsuario == 14) {
                        system("clear");
                        printf("Associar Docente a Discente...\n");

                        associarDocenteADiscente(ArrayDiscente, sizeDis, ArrayDocente, sizeDoc);
                    }

                } while(selectUsuario != 0);
            }
        }

    } while(selectPrincipal != 0);
}
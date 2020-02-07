#include "user.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>

struct pessoa {
    char *nome;
    int idade, ID;
    int matricula;
};

struct docente {
    Pessoa info_docente;
    int qtd_orientacoes_graduacao, qtd_orientacoes_pos_graduacao;
};

struct discente {
    Pessoa info_discente;
    int nivel; // 1 - graduação ou 2 - pos-gradução
    char *nome_curso;
    int senha, ID_orientador, ID_coorientador;
};

void createDirUser(char *nameDirUser) {
	if(mkdir(nameDirUser, S_IRUSR | S_IWUSR | S_IXUSR) != 0);
}

// verifica no arquivo info se o sistema ja foi iniciado alguma vez neste arquivo contem a quantidade de usuarios cadastrados
int verifySystem(int *doc, int *dis) {

    int infoDoc, infoDis;

    FILE *fPtr = fopen(".sys/info.txt", "r");
	
	if(fPtr == NULL)
		printf("\nFalha ao abrir o arquivo de inicializacao [info]\n");
	else
        fscanf(fPtr, "%d %d", &infoDoc, &infoDis);

    *doc = infoDoc;
    *dis = infoDis;

    int init = 0;

    if(infoDoc > 0) init = 1;
    if(infoDis > 0) init = 1;

    return init;
}

void addInfoSys(int doc, int dis) { // atualiza a quantidade de usuarios cadastrados

    FILE *fPtr = fopen(".sys/info.txt", "w");

    if(fPtr == NULL)
		printf("\nFalha ao abrir o arquivo de inicializacao [info]\n");
	else
        fprintf(fPtr, "%d %d", doc, dis);

    fclose(fPtr);
}

void saveDocente(Docente *doc, int totalDocentes, int idDocente) {
    	
    if(doc != NULL) {

        int iDoc;

        for(int i = 0; i < totalDocentes; i++)
            if(doc[i].info_docente.ID == idDocente) {
                iDoc = i; break;
            }

		char *nameFile = (char *) malloc(sizeof(char));

		char prefix[4] = "doc";

		snprintf(nameFile, 20, ".user/%s%d.txt", prefix, idDocente);
	    
	    FILE *fPtr = fopen(nameFile, "w");
		
		fprintf(fPtr, "%d\n", doc[iDoc].info_docente.ID);
        fprintf(fPtr, "%d\n", doc[iDoc].info_docente.idade);
        fprintf(fPtr, "%d\n", doc[iDoc].info_docente.matricula);
        fprintf(fPtr, "%s\n", doc[iDoc].info_docente.nome);
        fprintf(fPtr, "%d\n", doc[iDoc].qtd_orientacoes_graduacao);
        fprintf(fPtr, "%d\n", doc[iDoc].qtd_orientacoes_pos_graduacao);

		fclose(fPtr);

		printf("Usuario salvo.\n\n");
	} else {
		printf("\nUsuario nao existe.\n");
	}
}

void saveDiscente(Discente *dis, int totalDiscentes, int idDiscente) {
    	
    if(dis != NULL) {

        int iDis;

        for(int i = 0; i < totalDiscentes; i++)
            if(dis[i].info_discente.ID == idDiscente) {
                iDis = i; break;
            }

		char *nameFile = (char *) malloc(sizeof(char));

		char prefix[4] = "dis";

		snprintf(nameFile, 20, ".user/%s%d.txt", prefix, idDiscente);
	    
	    FILE *fPtr = fopen(nameFile, "w");
		
		fprintf(fPtr, "%d\n", dis[iDis].info_discente.ID);
        fprintf(fPtr, "%d\n", dis[iDis].info_discente.idade);
        fprintf(fPtr, "%d\n", dis[iDis].info_discente.matricula);
        fprintf(fPtr, "%s\n", dis[iDis].info_discente.nome);
        fprintf(fPtr, "%d\n", dis[iDis].nivel);
        fprintf(fPtr, "%s\n", dis[iDis].nome_curso);
        fprintf(fPtr, "%d\n", dis[iDis].senha);
        fprintf(fPtr, "%d\n", dis[iDis].ID_orientador);
        fprintf(fPtr, "%d\n", dis[iDis].ID_coorientador);

		fclose(fPtr);

		printf("Usuario salvo.\n\n");
	} else {
		printf("\nUsuario nao existe.\n");
	}
}

void removerUser(int idUser, int mode) {

    char *prefix = (char *) malloc(sizeof(char));

    if(mode == 1)
        prefix = "doc";
    
    else if(mode == 2)
        prefix = "dis";


	char *nameFile = (char *) malloc(sizeof(char));

	snprintf(nameFile, 20, ".user/%s%d.txt", prefix, idUser);

    remove(nameFile);
}

Docente *loadDocente(Docente *doc, int totalDocentes, int *id) {


    char **nameFile = (char **) malloc(sizeof(char *));

	for(int i = 0; i < totalDocentes; i++)
		nameFile[i] = (char *) malloc(sizeof(char));

	//char nameFile = [ totalDocentes ][20];
	char prefix[4] = "doc";

    for(int i = 0; i < totalDocentes; i++)
	    snprintf(nameFile[i], 20, ".user/%s%d.txt", prefix, i +1);

    
    for(int i = 0; i < totalDocentes; i++) {
        
        FILE *fPtr;
        
        if((fPtr = fopen(nameFile[i], "r")) == NULL)
            printf("\nErro na abertura do arquivo de dados do %d discente!\n", i +1);

        else {

            int ID = 0;
            int idade = 0;
            int matricula = 0;
            char *nome = (char *) malloc(sizeof(char));
            int qtd_orientacoes_graduacao = 0;
            int qtd_orientacoes_pos_graduacao = 0;

            fscanf(fPtr, "%d", &ID);
            fscanf(fPtr, "%d", &idade);
            fscanf(fPtr, "%d", &matricula);
            fscanf(fPtr, "%s", nome);
            fscanf(fPtr, "%d", &qtd_orientacoes_graduacao);
            fscanf(fPtr, "%d", &qtd_orientacoes_pos_graduacao);

            doc = createDocente(doc, i);
            
            doc[i].info_docente.ID = ID;
            doc[i].info_docente.idade = idade;
            doc[i].info_docente.matricula = matricula;
            strcpy(doc[i].info_docente.nome, nome);
            doc[i].qtd_orientacoes_graduacao = qtd_orientacoes_graduacao;
            doc[i].qtd_orientacoes_pos_graduacao = qtd_orientacoes_pos_graduacao;
            
            *id = i +1;
        }  
    }

    return doc;
}

Discente *loadDiscente(Discente *dis, int totalDiscentes, int *id) {


    char **nameFile = (char **) malloc(sizeof(char *));

	for(int i = 0; i < totalDiscentes; i++)
		nameFile[i] = (char *) malloc(sizeof(char));

	//char nameFile = [ totalDiscentes ][20];
	char prefix[4] = "dis";

    for(int i = 0; i < totalDiscentes; i++)
	    snprintf(nameFile[i], 20, ".user/%s%d.txt", prefix, i +1);

    
    for(int i = 0; i < totalDiscentes; i++) {
        
        FILE *fPtr;
        
        if((fPtr = fopen(nameFile[i], "r")) == NULL)
            printf("\nErro na abertura do arquivo de dados do %d discente!\n", i +1);

        else {

            int ID = 0;
            int idade = 0;
            int matricula = 0;
            char *nome = (char *) malloc(sizeof(char));
            int nivel = 0;
            char *nome_curso = (char *) malloc(sizeof(char));
            int senha = 0;
            int ID_orientador = 0;
            int ID_coorientador = 0;

            fscanf(fPtr, "%d", &ID);
            fscanf(fPtr, "%d", &idade);
            fscanf(fPtr, "%d", &matricula);
            fscanf(fPtr, "%s", nome);
            fscanf(fPtr, "%d", &nivel);
            fscanf(fPtr, "%s", nome_curso);
            fscanf(fPtr, "%d", &senha);
            fscanf(fPtr, "%d", &ID_orientador);
            fscanf(fPtr, "%d", &ID_coorientador);

            dis = createDiscente(dis, i);

            dis[i].info_discente.ID = ID;
            dis[i].info_discente.idade = idade;
            dis[i].info_discente.matricula = matricula;
            strcpy(dis[i].info_discente.nome, nome);
            dis[i].nivel = nivel;
            strcpy(dis[i].nome_curso, nome_curso);
            dis[i].senha = senha;
            dis[i].ID_orientador = ID_orientador;
            dis[i].ID_coorientador = ID_coorientador;

            *id = i +1;
        }  
    }

    return dis;
}

// Funções da TAD-1
Pessoa *createUser() {
    Pessoa *p = (Pessoa *) malloc(sizeof(Pessoa));
    return p;
}

int retornaIdPorMatriculaDiscente(Discente *dis, int totalDiscentes, int mat) {

    /**
     * @Nota: 
     * Retorna o id do aluno atravez da matricula.
    */
    
    int id = 0;

    for(int i = 0; i < totalDiscentes; i++) {
        if(dis[i].info_discente.matricula == mat) id = dis[i].info_discente.ID;
    }

    return id;
}

int passwordVerify(Discente *dis, int totalDiscentes, int matricula, int password) {

    int pass = 0;

    for(int i = 0; i < totalDiscentes; i++) {
        
        if(dis[i].info_discente.matricula == matricula) {
            
            if(dis[i].ID_orientador == 0) {
                printf("\n Para ter acesso ao sistema voce deve ter um orientador...\n");
                printf(" Pressione ENTER\n");
                getchar(); scanf("c\n");

            }
            
            if(dis[i].senha == password && dis[i].ID_orientador != 0) pass = 1;

            break;
        }
    }

    return pass;
}

void associarDocenteADiscente(Discente *dis, int totalDiscentes, Docente *doc, int totalDocentes) {

    /**
     * @Nota:
     * Um orientador pode ter no máximo 10 alunos
     *  40% de graduação.
     *  60% de pos-graduação.
     * 
     * Para o caso de coorientador não existe limite.
    */

    int matriculaDis; int flag = 0;
    mostrarDiscente(dis, totalDiscentes);
    printf("Informe a matricula do Discente:");
    scanf("%d", &matriculaDis);
    system("clear");

    int iDoc;
    for(int i = 0; i < totalDiscentes; i++) {
        if(dis[i].info_discente.matricula == matriculaDis) {
            
            mostrarDocente(doc, totalDocentes);

            while(1) {
                printf("Informe o id do Docente que deseja associar: ");
                scanf("%d", &iDoc);

                if(iDoc <= totalDiscentes && iDoc > 0) break;
            };

            for(int j = 0; j < totalDocentes; j++) {
                if(doc[j].info_docente.ID == iDoc && doc[j].info_docente.ID != dis[i].ID_orientador) {
                    
                    int opOrientacao; 
                    
                    do {
                        system("clear");
                        printf("Digite 1 para associar o Docente: %s como Orientador ao Discente: %s.\n", doc[j].info_docente.nome, dis[i].info_discente.nome);
                        printf("Digite 2 para associar o Docente: %s como Coorientador ao Discente: %s.\n", doc[j].info_docente.nome, dis[i].info_discente.nome);
                        printf("Digite aqui: ");
                        scanf("%d", &opOrientacao);
                        
                    } while(opOrientacao != 1 && opOrientacao != 2);

                    if(opOrientacao == 1) { // Orientador
                        
                        if(dis[i].nivel == 1 && doc[j].qtd_orientacoes_graduacao <= 4) { // Graduação
                            dis[i].ID_orientador = iDoc;
                            doc[j].qtd_orientacoes_graduacao++;
                            break;
                            flag = 1;

                        } else if(dis[i].nivel == 2 && doc[j].qtd_orientacoes_pos_graduacao <= 6) { // Pos graduação
                            dis[i].ID_orientador = iDoc;
                            doc[i].qtd_orientacoes_pos_graduacao++;
                            break;
                            flag = 1;
                        }
                    }
                

                    if(opOrientacao == 2) { // Coorientador
                        
                        if(dis[i].nivel == 1) { // Graduação
                            dis[i].ID_coorientador = iDoc;
                            doc[j].qtd_orientacoes_graduacao++;
                            break;
                            flag = 1;

                        } else if(dis[i].nivel == 2) { // Pos graduação
                            dis[i].ID_coorientador = iDoc;
                            doc[i].qtd_orientacoes_pos_graduacao++;
                            break;
                            flag = 1;
                        }
                    }
                }
            }
        }

        saveDocente(doc, totalDocentes, iDoc);
        saveDiscente(dis, totalDiscentes, i +1);

        if(flag == 1) break;
    }
}

void listarAlunoDeOrientador(Docente *doc, int totalDocentes, Discente *dis, int totalDiscentes) {

    int iDoc;
    mostrarDocente(doc, totalDocentes);
    printf("Informe o ID do orientador para Listar seus alunos: ");
    scanf("%d", &iDoc);
    system("clear");

    char nvl[2][20] = {"Graduacao", "PosGraduacao"};

    for(int i = 0; i < totalDiscentes; i++) {
        if(dis[i].ID_orientador == iDoc) {
            printf("Informacoes de Discente...\n");
            printf("Nome: %s\n", dis[i].info_discente.nome);
            printf("Idade: %d\n", dis[i].info_discente.idade);
            printf("ID: %d\n", dis[i].info_discente.ID);
            printf("Matricula: %d\n", dis[i].info_discente.matricula);
            printf("Nivel de %s.\n", nvl[dis[i].nivel - 1]);
            printf("Curso: %s.\n\n", dis[i].nome_curso);
        }
    }

    printf("Pressione ENTER\n");
    getchar(); scanf("c\n");
}

void listarAlunosSemOrientador(Discente *dis, int totalDiscentes) {

    char nvl[2][20] = {"Graduacao", "PosGraduacao"};

    for(int i = 0; i < totalDiscentes; i++) {
        if(dis[i].ID_orientador == 0) {
            printf("Informacoes de Discente...\n");
            printf("Nome: %s\n", dis[i].info_discente.nome);
            printf("Idade: %d\n", dis[i].info_discente.idade);
            printf("ID: %d\n", dis[i].info_discente.ID);
            printf("Matricula: %d\n", dis[i].info_discente.matricula);
            printf("Nivel de %s.\n", nvl[dis[i].nivel - 1]);
            printf("Curso: %s.\n\n", dis[i].nome_curso);
        }
    }

    printf("Pressione ENTER\n");
    getchar(); scanf("c\n");
}

void mudarOrientadorDeAluno(Docente *doc, int totalDocentes, Discente *dis, int totalDiscentes) { 
    
    int Matricula;
    mostrarDiscente(dis, totalDiscentes);

    printf("Informe a matricula do Discente para alterar o seu Orientador: ");
    scanf("%d", &Matricula);

    int opOrientacao;

    for(int i = 0; i < totalDiscentes; i++) {

        if(dis[i].info_discente.matricula == Matricula) {

            if(dis[i].ID_coorientador > 0 || dis[i].ID_orientador > 0) {

                do{
                    printf("Para voltar Digite 0.\n");
                    if(dis[i].ID_orientador != 0) printf("Digite 1 para dessassociar o Orientaddor!\n");
                    if(dis[i].ID_coorientador != 0) printf("Digite 2 para dessassociar o Coorientaddor!\n");

                    printf("Digite aqui: ");
                    scanf("%d", &opOrientacao);

                    if(opOrientacao == 1) {

                        for(int j = 0; j < totalDocentes; j++) {
                            if(doc[j].info_docente.ID == dis[i].ID_orientador) {
                                
                                if(dis[i].nivel == 1) doc[j].qtd_orientacoes_graduacao--;
                                if(dis[i].nivel == 2) doc[j].qtd_orientacoes_pos_graduacao--;
                            }

                            break;
                        }

                        dis[i].ID_orientador = 0;
                    }

                    if(opOrientacao == 2) {
                        dis[i].ID_coorientador = 0;
                        
                        for(int j = 0; j < totalDocentes; j++) {
                            if(doc[j].info_docente.ID == dis[i].ID_coorientador) doc[j].qtd_orientacoes_graduacao--;

                            if(dis[i].nivel == 1) doc[j].qtd_orientacoes_graduacao--;
                            if(dis[i].nivel == 2) doc[j].qtd_orientacoes_pos_graduacao--;

                            break;
                        }

                        dis[i].ID_coorientador = 0;
                    }

                } while(opOrientacao != 1 && opOrientacao != 2 && opOrientacao != 0);
            }
        }

        break;
    }

    if(opOrientacao != 0)
        associarDocenteADiscente(dis, totalDiscentes, doc, totalDocentes);
}

Docente *createDocente(Docente *doc, int size) {

    Pessoa *p = createUser();

    doc = (Docente *) realloc(doc, sizeof(Docente) * (size + 1));

    doc[size].info_docente.ID = 0;
    doc[size].info_docente.idade = 0;
    doc[size].info_docente.matricula = 0;
    doc[size].info_docente.nome = (char *) malloc(sizeof(char));
    doc[size].qtd_orientacoes_graduacao = 0;
    doc[size].qtd_orientacoes_pos_graduacao = 0;
    
    return doc;
}

Docente *cadastroDocente(Docente *doc, int size, int iDoc) {
    
    printf("Informe o nome: "); 
    scanf(" %[^\n]s", doc[iDoc].info_docente.nome);
    
    printf("Informe a idade: "); 
    scanf("%d", &doc[iDoc].info_docente.idade);
    
    doc[iDoc].info_docente.ID = iDoc + 1;

    int valid = 0, matricula = 1;

    srand(time(NULL));

    do {
        matricula = 1 + rand() % 999;

        for(int i = 0; i < size; i++) {
            if(matricula == doc[i].info_docente.matricula) {
                valid = 1; 
            }
        }

    } while(valid != 0);

    doc[iDoc].info_docente.matricula = matricula;
    doc[iDoc].qtd_orientacoes_graduacao = 0;
    doc[iDoc].qtd_orientacoes_pos_graduacao = 0;

    saveDocente(doc, size +1, doc[iDoc].info_docente.ID);

    return doc;
}

Docente *removerDocente(Docente *doc, int totalDocentes, Discente *dis, int totalDiscentes) {

    int matriculaRemover;
    printf("Temos %d docente(s) cadastrado(s)\n", totalDocentes);
    mostrarDocente(doc, totalDocentes);
    printf("Informe a matricula para remover: ");
    scanf("%d", &matriculaRemover);

    
    for(int i = 0; i < totalDocentes; i++) {
        if(doc[i].info_docente.matricula == matriculaRemover) {

            removerUser(doc[i].info_docente.ID, 1);

            /**
            * @Nota: 
            * Verificação: Se existe algum vinculo entre o Docente e alunos
            */

            if(doc[i].qtd_orientacoes_graduacao > 0) {

            
                for(int j = 0; j < totalDiscentes; j++) {
                    
                    if(doc[i].info_docente.ID == dis[j].ID_orientador) dis[j].ID_orientador = 0;
                    if(doc[i].info_docente.ID == dis[j].ID_coorientador) dis[j].ID_coorientador = 0;
                }

            }

            if(doc[i].qtd_orientacoes_pos_graduacao > 0) {

                for(int j = 0; j < totalDiscentes; j++) {
                    
                    if(doc[i].info_docente.ID == dis[j].ID_orientador) dis[j].ID_orientador = 0;
                    if(doc[i].info_docente.ID == dis[j].ID_coorientador) dis[j].ID_coorientador = 0;
                }

            }
            
            strcpy(doc[i].info_docente.nome, doc[totalDocentes - 1].info_docente.nome);
            doc[i].info_docente.ID = doc[totalDocentes - 1].info_docente.ID;
            doc[i].info_docente.idade = doc[totalDocentes - 1].info_docente.idade;
            doc[i].info_docente.matricula = doc[totalDocentes - 1].info_docente.matricula;
            doc[i].qtd_orientacoes_graduacao = doc[totalDocentes - 1].qtd_orientacoes_graduacao;
            doc[i].qtd_orientacoes_pos_graduacao = doc[totalDocentes - 1].qtd_orientacoes_pos_graduacao;

            break;
        }
    }

    doc = (Docente *) realloc(doc, sizeof(Docente) * (totalDocentes - 1));

    return doc;
}

Docente *alterarDocente(Docente *doc, int totalDocentes) {

    int matriculaAlterar;
    printf("Temos %d docente(s) cadastrado(s)\n", totalDocentes);
    mostrarDocente(doc, totalDocentes);
    printf("Informe a matricula para alterar: ");
    scanf("%d", &matriculaAlterar);
   
    for(int i = 0; i < totalDocentes; i++) {

        if(doc[i].info_docente.matricula == matriculaAlterar){
            
            doc[i].info_docente.nome[0] = '\0';
            doc[i].info_docente.idade = 0;
            doc[i].info_docente.matricula = 0;

            printf("Informe o novo nome: "); 
            scanf(" %[^\n]s", doc[i].info_docente.nome);
            
            printf("Informe a nova idade: "); 
            scanf("%d", &doc[i].info_docente.idade);

            int valid = 0, matricula = 1;

            srand(time(NULL));

            do {
                matricula = 1 + rand() % 999;

                for(int i = 0; i < totalDocentes; i++) {
                    if(matricula == doc[i].info_docente.matricula) {
                        valid = 1; 
                    }
                }

            } while(valid != 0);

            doc[i].info_docente.matricula = matricula;

            saveDocente(doc, totalDocentes +1, doc[i].info_docente.ID);

            break;
        }
    }

    return doc;
}

void buscarDocente(Docente *doc) {

    int iDoc;
    printf("Informe o ID do dcoente que deseja procurar: ");
    scanf("%d", &iDoc);

    printf("Informacoes de Docente...\n");
    printf("Nome: %s\n", doc[iDoc].info_docente.nome);
    printf("Idade: %d\n", doc[iDoc].info_docente.idade);
    printf("ID: %d\n", doc[iDoc].info_docente.ID);
    printf("Matricula: %d\n", doc[iDoc].info_docente.matricula);
    printf("Quantidade de orientandos de graduacao: %d\n", doc[iDoc].qtd_orientacoes_graduacao);
    printf("Quantidade de orientandos de pos-graduacao: %d\n\n", doc[iDoc].qtd_orientacoes_pos_graduacao);

    printf("Pressione ENTER\n");
    getchar(); scanf("c\n");
}

void mostrarDocente(Docente *doc, int totalDocentes) {

    for(int i = 0; i < totalDocentes; i++) {
        printf("Informacoes de Docente...\n");
        printf("Nome: %s\n", doc[i].info_docente.nome);
        printf("Idade: %d\n", doc[i].info_docente.idade);
        printf("ID: %d\n", doc[i].info_docente.ID);
        printf("Matricula: %d\n", doc[i].info_docente.matricula);
        printf("Quantidade de orientandos de graduacao: %d\n", doc[i].qtd_orientacoes_graduacao);
        printf("Quantidade de orientandos de pos-graduacao: %d\n\n", doc[i].qtd_orientacoes_pos_graduacao);
    }
}

Discente *createDiscente(Discente *dis, int size) {

    Pessoa *p = createUser();

    dis = (Discente *) realloc(dis, sizeof(Discente) * (size + 1));

    dis[size].info_discente.ID = 0;
    dis[size].info_discente.idade = 0;
    dis[size].info_discente.matricula = 0;
    dis[size].info_discente.nome = (char *) malloc(sizeof(char));
    dis[size].nivel = 0;
    dis[size].nome_curso = (char *) malloc(sizeof(char));
    dis[size].senha = 0;
    dis[size].ID_orientador = 0;
    dis[size].ID_coorientador = 0;
    
    return dis;
}

Discente *cadastroDiscente(Discente *dis, int size, int iDis) {

    printf("Informe o nome: ");
    scanf(" %[^\n]s", dis[iDis].info_discente.nome);

    printf("Informe a idade: ");
    scanf("%d", &dis[iDis].info_discente.idade);

    printf("Nivel - 1 para Graduacao | 2 para Pos-Graduacao.\n");
    printf("Digite aqui: ");
    scanf("%d", &dis[iDis].nivel);

    printf("Informe o curso do Discente: ");
    scanf(" %[^\n]s", dis[iDis].nome_curso);

    int flag = 0;
    
    do {
        printf("Defina uma senha numerica: ");
        scanf("%d", &dis[iDis].senha);
        
        if(dis[iDis].senha != 0) flag = 1;
    
    } while(flag != 1);

    dis[iDis].ID_orientador = 0;
    dis[iDis].ID_coorientador = 0;
    dis[iDis].info_discente.ID = iDis + 1;

    int valid = 0, matricula = 1000;

    srand(time(NULL));
    do {
        matricula = 1000 + rand() % 2000;

        for(int i = 0; i < size; i++) {
            if(matricula == dis[i].info_discente.matricula) {
                valid = 1; 
            }
        }

    } while(valid != 0);

    dis[iDis].info_discente.matricula = matricula;

    saveDiscente(dis, size +1, dis[iDis].info_discente.ID);

    return dis;
}

Discente *removerDiscente(Discente *dis, int totalDiscentes, Docente *doc, int totalDocentes) {
    
    int matriculaRemover = 0, flag = 0;

    do {
        system("clear");
        printf("Temos %d discente(s) cadastrado(s)\n", totalDiscentes);
        mostrarDiscente(dis, totalDiscentes);
        printf("Informe a matricula para remover: ");
        scanf("%d", &matriculaRemover);

        for(int i = 0; i < totalDiscentes; i++) { 
            if(dis[i].info_discente.matricula == matriculaRemover) flag = 1;
        }

    } while(flag != 1);
   
    for(int i = 0; i < totalDiscentes; i++) {
        if(dis[i].info_discente.matricula == matriculaRemover){

            removerUser(dis[i].info_discente.ID, 2);
            
            if(dis[i].ID_orientador != 0) { // Desvincular Orientador.
                for(int j = 0; j < totalDocentes; j++) {
                    
                    if(doc[j].info_docente.ID == dis[i].ID_orientador && dis[i].nivel == 1) doc[j].qtd_orientacoes_graduacao--;
                    if(doc[j].info_docente.ID == dis[i].ID_orientador && dis[i].nivel == 2) doc[j].qtd_orientacoes_pos_graduacao--;
                }
            }

            if(dis[i].ID_coorientador != 0) { // Desvincular Coorientador
                for(int j = 0; j < totalDocentes; j++) {
                    
                    if(doc[j].info_docente.ID == dis[i].ID_coorientador && dis[i].nivel == 1) doc[j].qtd_orientacoes_graduacao--;
                    if(doc[j].info_docente.ID == dis[i].ID_coorientador && dis[i].nivel == 2) doc[j].qtd_orientacoes_pos_graduacao--;
                }
            }
            
            strcpy(dis[i].info_discente.nome, dis[totalDiscentes - 1].info_discente.nome);
            dis[i].info_discente.ID = dis[totalDiscentes - 1].info_discente.ID;
            dis[i].info_discente.idade = dis[totalDiscentes - 1].info_discente.idade;
            dis[i].nivel = dis[totalDiscentes - 1].nivel;
            strcpy(dis[i].nome_curso, dis[totalDiscentes - 1].nome_curso);
            dis[i].senha = dis[totalDiscentes - 1].senha;
            dis[i].ID_orientador = dis[totalDiscentes - 1].ID_orientador;
            dis[i].ID_coorientador = dis[totalDiscentes - 1].ID_coorientador;
            dis[i].info_discente.matricula = dis[totalDiscentes - 1].info_discente.matricula;

            break;
        }
    }

    dis = (Discente *) realloc(dis, sizeof(Discente) * (totalDiscentes - 1));

    return dis;
}

Discente *alterarDiscente(Discente *dis, int totalDiscentes) {
    
    int matriculaAlterar;
    printf("Temos %d discente(s) cadastrado(s)\n", totalDiscentes);
    mostrarDiscente(dis, totalDiscentes);
    printf("Informe a matricula para alterar: ");
    scanf("%d", &matriculaAlterar);
   
    for(int i = 0; i < totalDiscentes; i++) {

        if(dis[i].info_discente.matricula == matriculaAlterar){
            
            dis[i].info_discente.nome[0] = '\0';
            dis[i].info_discente.idade = 0;
            dis[i].info_discente.matricula = 0;
            dis[i].nivel = 0;
            dis[i].nome_curso[0] = '\0';
            dis[i].senha = 0;

            printf("Informe o novo nome: ");
            scanf(" %[^\n]s", dis[i].info_discente.nome);

            printf("Informe a nova idade: ");
            scanf("%d", &dis[i].info_discente.idade);

            printf("Nivel - 1 para Graduacao | 2 para Pos-Graduacao.\n");
            printf("Digite aqui: ");
            scanf("%d", &dis[i].nivel);

            printf("Informe o curso do Discente: ");
            scanf(" %[^\n]s", dis[i].nome_curso);
            
            int flag = 0;
    
            do {
                printf("Defina uma senha numerica: ");
                scanf("%d", &dis[i].senha);
            
                if(dis[i].senha != 0) flag = 1;
        
            } while(flag != 1);

            int valid = 0, matricula = 1000;

            srand(time(NULL));
            do {
                matricula = 1000 + rand() % 2000;

                for(int i = 0; i < totalDiscentes; i++) {
                    if(matricula == dis[i].info_discente.matricula) {
                        valid = 1; 
                    }
                }

            } while(valid != 0);

            dis[i].info_discente.matricula = matricula;

            saveDiscente(dis, totalDiscentes +1, dis[i].info_discente.ID);

            break;
        }
    }

    return dis;
}

void buscarDiscente(Discente *dis) {

    char nvl[2][20] = {"Graduacao", "PosGraduacao"};

    int iDis;
    printf("Informe o ID do dcoente que deseja procurar: ");
    scanf("%d", &iDis);

    printf("Informacoes de Disccente...\n");
    printf("Nome: %s\n", dis[iDis].info_discente.nome);
    printf("Idade: %d\n", dis[iDis].info_discente.idade);
    printf("ID: %d\n", dis[iDis].info_discente.ID);
    printf("Matricula: %d\n", dis[iDis].info_discente.matricula);
    printf("Nivel de %s.\n", nvl[dis[iDis].nivel - 1]);
    printf("Curso: %s.\n", dis[iDis].nome_curso);
    if(dis[iDis].ID_orientador != 0)
        printf("ID do orientador: %d.\n", dis[iDis].ID_orientador);
    if(dis[iDis].ID_coorientador != 0)
        printf("ID do coorientador: %d.\n", dis[iDis].ID_coorientador);

    printf("\n");

    printf("Pressione ENTER\n");
    getchar(); scanf("c\n");
}

void mostrarDiscente(Discente *dis, int totalDiscentes) {
    
    char nvl[2][20] = {"Graduacao", "PosGraduacao"};

    for(int i = 0; i < totalDiscentes; i++) {
        printf("Informacoes de Discente...\n");
        printf("Nome: %s\n", dis[i].info_discente.nome);
        printf("Idade: %d\n", dis[i].info_discente.idade);
        printf("ID: %d\n", dis[i].info_discente.ID);
        printf("Matricula: %d\n", dis[i].info_discente.matricula);
        printf("Nivel de %s.\n", nvl[dis[i].nivel - 1]);
        printf("Curso: %s.\n", dis[i].nome_curso);
        if(dis[i].ID_orientador != 0)
            printf("ID do orientador: %d.\n", dis[i].ID_orientador);
        if(dis[i].ID_coorientador != 0)
            printf("ID do coorientador: %d.\n", dis[i].ID_coorientador);

        printf("\n");
    }
}
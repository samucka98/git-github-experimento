#ifndef USER_H
#define USER_H

// TAD-1: Cadastro - Assinatura dos tipos
typedef struct pessoa Pessoa;
typedef struct docente Docente;
typedef struct discente Discente;

// Protótipos das funções da TAD-1
void createDirUser(char *nameDirUser);
int verifySystem(int *doc, int *dis);
void addInfoSys(int doc, int dis);
void saveDocente(Docente *doc, int totalDocentes, int idDocente);
void saveDiscente(Discente *dis, int totalDiscentes, int idDiscente);
void removerUser(int idUser, int mode); // modo 1 docente modo 2 discente

Docente *loadDocente(Docente *doc, int totalDocentes, int *id);
Discente *loadDiscente(Discente *dis, int totalDiscentes, int *id);
void loadUsers();

Pessoa *createUser();
int retornaIdPorMatriculaDiscente(Discente *dis, int totalDiscentes, int mat);
int passwordVerify(Discente *dis, int totalDiscentes, int matricula, int password);
void associarDocenteADiscente(Discente *dis, int totalDiscentes, Docente *doc, int totalDocentes);
void listarAlunoDeOrientador(Docente *doc, int totalDocentes, Discente *dis, int totalDiscentes);
void listarAlunosSemOrientador(Discente *dis, int totalDiscentes);
void mudarOrientadorDeAluno(Docente *doc, int totalDocentes, Discente *dis, int totalDiscentes);

Docente *createDocente(Docente *doc, int size);
Docente *cadastroDocente(Docente *doc, int size, int iDoc);
Docente *removerDocente(Docente *doc, int totalDocentes, Discente *dis, int totalDiscentes);
Docente *alterarDocente(Docente *doc, int totalDocentes);
void buscarDocente(Docente *doc);
void mostrarDocente(Docente *doc, int totalDocentes);

Discente *createDiscente(Discente *dis, int size);
Discente *cadastroDiscente(Discente *dis, int size, int iDis);
Discente *removerDiscente(Discente *dis, int totalDiscentes, Docente *doc, int totalDocentes);
Discente *alterarDiscente(Discente *dis, int totalDiscentes);
void buscarDiscente(Discente *dis);
void mostrarDiscente(Discente *dis, int totalDiscentes);

#endif
#include "menu.h"
#include <stdio.h>

// 1 - Acessar, 2 - Cad
void menuPrincipal() {
    printf("MENU PRINCIPAL\n");
    printf("0 - Sair.\n");
    printf("1 - Acessar sistema.\n");
    printf("2 - Gerenciamento de Usuarios.\n");
    printf("Digite aqui: ");
}

// informar o ID para acessar o sistema
void login() {
    printf("ENTRAR\n");
    printf("Para voltar digite 0.\n");
    printf("Digite aqui sua matricula: ");
}

// 1 - 
void menuUsuario() {
    // So permitir entrar com cadastro root(coordenador)
    printf("MENU USUARIO\n");

    printf("\n---DOCENTE---\n");
    printf(" 0 - Voltar.\n");
    printf(" 1 - Cadastrar Docente.\n");
    printf(" 2 - Remover Docente.\n");
    printf(" 3 - Alterar Docente.\n");
    printf(" 4 - Buscar Docente.\n");
    printf(" 5 - Mostrar Docente.\n");

    printf("\n---DISCENTE---\n");
    printf(" 6 - Cadastrar Discente.\n");
    printf(" 7 - Remover Discente.\n");
    printf(" 8 - Alterar Discente.\n");
    printf(" 9 - Buscar Discente.\n");
    printf("10 - Mostrar Discente.\n");

    printf("\n---OUTROS---\n");
    printf("11 - Listar Alunos de Orientador.\n");
    printf("12 - Listar Alunos sem Orientador.\n");
    printf("13 - Mudar Orientador de Aluno.\n");
    printf("14 - Associar Docente a Discente.\n");

    printf("-----------\n");
    printf("Digite aqui: ");
}

// 1 - processamento imagem
void menuFuncionalidades() {
    printf("FUNCIONALIDADES DO SISTEMA\n");
    printf("0 - Voltar.\n");
    printf("1 - Processamento de imagens.\n");
    printf("Digite aqui: ");
}

void menuImagem() {
    printf("PROCESSAMENTO DE IMAGEM\n");
    printf("0 - voltar.\n");
    printf("1 - Arquivo.\n");
    printf("2 - Funcionalidades.\n");
    printf("Digite aqui: ");
}

void arquivoIMG() {
    printf("PROCESSAMENTOD E IMAGEM ARQUIVO\n");
    printf("0 - Voltar.\n");
    printf("1 - Nova imagem.\n");
    printf("2 - Carregar imagem.\n");
    printf("3 - Salvar imagem.\n");
    printf("4 - Copiar imagem.\n");
    printf("5 - Salvar copia de imagem.\n");
    printf("Digite aqui: ");
}

void funcoesImagem() {
    printf("PROCESSAMENTOD E IMAGEM FUNCIONALIDADES\n");
    printf("0 - Voltar.\n");
    printf("1 - Valor maximo.\n");
    printf("2 - Valor minimo.\n");
    printf("3 - Distancia euclidiana.\n");
    printf("4 - Distancia manhattan.\n");
    printf("5 - Local binary pattern.\n");
    printf("6 - Matriz de coocorrencia.\n");
    printf("7 - Filtro de media.\n");
    printf("8 - Filtro de mediana.\n");
    printf("Digite aqui: ");
}
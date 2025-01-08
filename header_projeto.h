#ifndef PROJETO_HEADER_PROJETO_H
#define PROJETO_HEADER_PROJETO_H
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#define TAM 1024


struct data{
    int dia;
    int mes;
    int ano;
};

struct stock {
    int stock_papel;
    int stock_cadernos;
    int stock_material;
    int stock_estojo;
    int stock_carregador;
    int stock_pendrive;
    int stock_croissant;
    int stock_queijo;
    int stock_refri;
    int stock_cafe;
    int stock_torrada;
    int stock_bolos;
    int stock_baguete;
};

struct aluno {
    char nome[TAM];
    struct data data1;
    int ano;
    char turma[TAM];
    int numero_estudante;
    float saldo;
};

typedef struct no_lista { //lista ligada
    struct aluno a;
    struct no_lista * proximo;
} no_lista;

typedef no_lista * lista;


void menu_opcoes();
void menu_outros();
void menu_altera_dados();
void menu_stock();
void outros(bool verifico, lista lista_al, struct stock s);
struct data lerData(char *token);
void ler_ficheiro(lista listal_al);
void escrever_ficheiro(lista lista_al);
struct stock ler_ficheiro_stock();
void escrever_ficheiro_stock(struct stock s);
void escreve_ficheiro_historico(int num, char tipo[], float preco);
void ler_ficheiro_historico(lista lista_al);
int numero_aluno ();
lista cria ();
int procurar_aluno(int num_estudante, lista lista_al);
lista procura_num_estudante (lista lista_al, int num_estudante);
void procura(lista lista_al, char *nome, lista *ant, lista *atual);
void procura_num(lista lista_al, int num_estudante, lista *ant, lista *atual);
int verifica_data(int dia, int mes, int ano);
void insere_al (lista lista_al, struct aluno a);
void imprime (lista lista_al);
void add_aluno(lista lista_al, int num_estudante);
void elimina_aluno (lista lista_al, int num_estudante);
void carrega_conta (lista lista_al, int num_estudante);
void consulta_saldo (lista lista_al, int num_estudante);
void informacao_aluno (lista lista_al, int num_estudante);
void transferencia (lista lista_al, int num_estudante1, int num_estudante2);
void menu_compra();
void menu_bar();
float preco_bar(int opcao, bool verifico);
void menu_repografia();
float preco_repografia(int opcao, bool verifico);
void menu_cantina();
float preco_cantina(int opcao, bool verifico);
void efetua_compra (lista lista_al, int num_estudante, bool verifico, struct stock s);
void alunos_inf_saldo(lista lista_al);
void encher_stock(bool verifico, struct stock s);
void imprimir_stock(struct stock s);
int verificar_stock(int opcao, struct stock s);
void altera_dados_utilizador(bool verifico, lista lista_al);


#endif //PROJETO_HEADER_PROJETO_H
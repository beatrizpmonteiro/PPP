#include "header_projeto.h"

int main() {

    lista lista_al;
    lista_al = cria();
    ler_ficheiro(lista_al);
    struct stock s = ler_ficheiro_stock();

    int total_alunos = 0;
    struct aluno a;
    int opcao;
    bool verifico = true;

    while (verifico) {
        menu_opcoes();
        scanf("%d", &opcao);
        if (opcao == 0) {
            escrever_ficheiro(lista_al);
            escrever_ficheiro_stock(s);
            verifico = false;
        } else if (opcao > 0 && opcao <= 7) {
            int num_estudante = numero_aluno();
            int procura= procurar_aluno(num_estudante, lista_al);
            if (opcao == 1) {
                if (procura == 0) {
                    add_aluno(lista_al,num_estudante);
                    total_alunos++;
                } else {
                    printf("O numero de estudante ja existe, tente outra vez.\n\n");
                }
            } else if (opcao == 2) {
                if (procura == 1) {
                    elimina_aluno(lista_al, num_estudante);
                    total_alunos--;
                } else {
                    printf("Numero de estudante invalido.");
                }
            } else if (opcao == 3) {
                if (procura == 1) {
                    consulta_saldo (lista_al, num_estudante);
                } else {
                    printf("Numero de estudante invalido.");
                }
            } else if (opcao == 4) {
                if (procura == 1) {
                    efetua_compra (lista_al, num_estudante, verifico, s);
                } else {
                    printf("Numero de estudante invalido.");
                }
            } else if (opcao == 5) {
                if (procura == 1) {
                    informacao_aluno (lista_al, num_estudante);
                } else {
                    printf("Numero de estudante invalido.");
                }
            } else if (opcao == 6) {
                if (procura == 1) {
                    int num_estudante2;
                    printf ("Escreva o numero de estudante para o qual pretende enviar dinheiro:");
                    scanf ("%d", &num_estudante2);

                    if ((procurar_aluno(num_estudante2, lista_al) == 1)) {
                        transferencia(lista_al, num_estudante, num_estudante2);
                    } else {
                        printf("Numero de estudante invalido.");
                    }
                }
            } else if (opcao == 7) {
                if (procura == 1) {
                    carrega_conta(lista_al, num_estudante);
                } else {
                    printf("Numero de estudante invalido.");
                }
            }
        } else if (opcao == 8){
            outros(verifico, lista_al, s);
        } else {
            printf("Opcao invalida. Tente outra vez\n");
        }
    }
}
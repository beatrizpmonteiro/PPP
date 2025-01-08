#include "header_projeto.h"

void menu_opcoes() {
    printf("\nInsira o numero correspondente a operacao que pretende realizar:\n"
           "\t\t\t1 : 'Adicionar um aluno novo'\n"
           "\t\t\t2 : 'Eliminar um aluno existente'\n"//ver
           "\t\t\t3 : 'Consultas de saldo'\n"
           "\t\t\t4 : 'Efetuar uma compra'\n"//ver
           "\t\t\t5 : 'Informacao de um aluno'\n"
           "\t\t\t6 : 'Transferencias'\n"//ver
           "\t\t\t7 : 'Carregar a conta'\n"
           "\t\t\t8 : 'Outros'\n" // falta
           "\t\t\t0 : 'Sair'\n"
           "Opcao:");
}

void menu_outros(){
    printf("\nInsira o numero correspondente a operacao que pretende realizar\n"
           "\t\t\t1 : 'Lista dos alunos por ordem alfabetica'\n"
           "\t\t\t2 : 'Lista dos alunos com saldo inferior a um valor'\n"
           "\t\t\t3 : 'Encher stock'\n"
           "\t\t\t4 : 'Imprimir stock'\n"
           "\t\t\t5 : 'Alterar dados do utilizador devido a possiveis erros'\n"
           "\t\t\t6 : 'Imprimir historico'\n"
           "\t\t\t0 : 'Sair'\n"
           "Opcao:");
}

void menu_altera_dados(){
    printf("\nInsira o numero correspondente a operacao que pretende realizar\n"
           "\t\t\t1 : 'Alterar nome'\n"
           "\t\t\t2 : 'Alterar ano'\n"
           "\t\t\t3 : 'Alterar turma'\n"
           "\t\t\t4 : 'Alterar numero de estudante'\n"
           "\t\t\t5 : 'Alterar data de nascimento'\n"
           "\t\t\t0 : 'Sair'\n"
           "Opcao:");
}

void menu_stock(){
    printf("\nInsira a opcao para a qual quer adicionar o stock\n"
           "\t\t\t1 : Papel para fotocopia\n"
           "\t\t\t2 : Cadernos\n"
           "\t\t\t3 : Material de escrita\n"
           "\t\t\t4 : Estojo\n"
           "\t\t\t5 : Carregador para PC\n"
           "\t\t\t6 : Pen Drive\n"
           "\t\t\t7 : Croissant\n"
           "\t\t\t8 : Fiambre/Queijo\n"
           "\t\t\t9 : Refrigerante\n"
           "\t\t\t10 : Cafe\n"
           "\t\t\t11 : Torrada \n"
           "\t\t\t12 : Bolos\n"
           "\t\t\t13 : Baguete\n"
           "\t\t\t0 : Sair\n"
           "Opcao:");
}

void outros(bool verifico, lista lista_al, struct stock s){
    int opcao;
    menu_outros();
    scanf("%d", &opcao);

    if (opcao == 0){
        verifico = false;
    } else if (opcao == 1){
        imprime(lista_al);
    } else if (opcao == 2){
        alunos_inf_saldo(lista_al);
    } else if (opcao == 3){
        encher_stock(verifico, s);
    } else if (opcao == 4){
        imprimir_stock(s);
    } else if (opcao == 5){
        altera_dados_utilizador(verifico, lista_al);
    } else if (opcao == 6) {
        ler_ficheiro_historico(lista_al);
    } else {
        printf("Opcao invalida. Tente outra vez\n");
    }
}

struct data lerData(char *token) {

    struct data data1;

    char *tokenAux;
    int dataAux = 0;

    tokenAux = strtok(token, "-");
    while (tokenAux != NULL) {
        if (dataAux == 0)
            data1.dia = atoi(tokenAux);
        else if (dataAux == 1)
            data1.mes = atoi(tokenAux);
        else
            data1.ano = atoi(tokenAux);

        dataAux++;
        tokenAux = strtok(NULL, "-");
    }

    return data1;
}

void ler_ficheiro(lista listal_al) {
    char *token;
    char line[TAM];

    FILE *file = fopen("Alunos.txt", "r");

    if (file == NULL) {
        printf("Erro ao abrir o ficheiro.\n");
    }

    struct aluno a;
    while (!feof(file)) {
        fgets(line, TAM, file);
        token = strtok(line, ";");

        int aux = 0;
        while (token != NULL) {
            if (aux == 0) {
                strcpy(a.nome, token);
            } else if (aux == 1) {
                a.ano = atoi(token);
            } else if (aux == 2) {
                strcpy(a.turma, token);
            } else if (aux == 3) {
                a.numero_estudante = atoi(token);
            } else if (aux == 4) {
                a.saldo = atof(token);
            } else if (aux == 5) {
                a.data1.dia = lerData(token).dia;
                a.data1.mes = lerData(token).mes;
                a.data1.ano = lerData(token).ano;
                insere_al(listal_al, a);
            }
            aux++;
            token = strtok(NULL, ";");
        }
    }

    fclose(file);
}


void escrever_ficheiro(lista lista_al) {
    FILE *file;

    file = fopen("Alunos.txt", "w");

    if (file == NULL) {
        printf("Ocorreu um erro ao abrir o ficheiro de texto.\n");
        exit(1);   //A execução do programa termina com erros.
    }

    lista aux = lista_al -> proximo;

    while(aux) {
        fprintf(file, "%s;", aux -> a.nome);
        fprintf(file, "%d;", aux -> a.ano);
        fprintf(file, "%s;", aux -> a.turma);
        fprintf(file, "%d;", aux -> a.numero_estudante);
        fprintf(file, "%.2f;", aux -> a.saldo);
        fprintf(file, "%d-", aux -> a.data1.dia);
        fprintf(file, "%d-", aux -> a.data1.mes);
        fprintf(file, "%d\n", aux -> a.data1.ano);

        aux = aux -> proximo;
    }

    fclose(file);
}

void escrever_ficheiro_stock(struct stock s) {
    FILE *file;

    file = fopen("Stock.txt", "w");

    if (file == NULL) {
        printf("Ocorreu um erro ao abrir o ficheiro de texto.\n");
        exit(1);   //A execução do programa termina com erros.
    }

    fprintf(file, "%d\n", s.stock_papel);
    fprintf(file, "%d\n", s.stock_cadernos);
    fprintf(file, "%d\n", s.stock_material);
    fprintf(file, "%d\n", s.stock_estojo);
    fprintf(file, "%d\n", s.stock_carregador);
    fprintf(file, "%d\n", s.stock_pendrive);
    fprintf(file, "%d\n", s.stock_croissant);
    fprintf(file, "%d\n", s.stock_queijo);
    fprintf(file, "%d\n", s.stock_refri);
    fprintf(file, "%d\n", s.stock_cafe);
    fprintf(file, "%d\n", s.stock_torrada);
    fprintf(file, "%d\n", s.stock_bolos);
    fprintf(file, "%d", s.stock_baguete);

    fclose(file);
}

struct stock ler_ficheiro_stock() {
    char *token;
    char line[TAM];
    struct stock s;
    FILE *file = fopen("Stock.txt", "r");

    if (file == NULL) {
        printf("Nao ha stock\n");
    }

    int aux = 0;
    for (int i = 0; fgets(line, sizeof(line) - 1, file) != NULL; i++) {
        token = strtok(line, "\n\r");
        while (token != NULL) {
            if (aux == 0) {
                s.stock_papel = atoi(token);
            } else if (aux == 1) {
                s.stock_cadernos = atoi(token);
            } else if (aux == 2) {
                s.stock_material = atoi(token);
            } else if (aux == 3) {
                s.stock_estojo = atoi(token);
            } else if (aux == 4) {
                s.stock_carregador = atoi(token);
            } else if (aux == 5) {
                s.stock_pendrive = atoi(token);
            } else if (aux == 6){
                s.stock_croissant = atoi(token);
            } else if (aux == 7){
                s.stock_queijo = atoi(token);
            } else if (aux == 8){
                s.stock_refri = atoi(token);
            } else if (aux == 9){
                s.stock_cafe = atoi(token);
            } else if (aux == 10){
                s.stock_torrada = atoi(token);
            } else if (aux == 11){
                s.stock_bolos = atoi(token);
            } else if (aux == 12) {
                s.stock_baguete = atoi(token);
            }
            aux++;
            token = strtok(NULL, "\n\r");
        }
    }

    fclose(file);
    return s;
}

void ler_ficheiro_historico(lista lista_al){
    FILE *file = fopen("Historico.txt", "r");
    char line[TAM];
    char *token;
    int num;
    float saldo;
    char tipo[TAM];

    int num_estudante;
    printf ("Escreva o numero de estudante: ");
    scanf ("%d", &num_estudante);

    while(!feof(file)){
        fgets(line, TAM, file);
        token = strtok(line, "-");
        num = atoi(token);
        if(procurar_aluno(num_estudante, lista_al)==1 && num_estudante == num) {
            token = strtok(NULL, ":");
            strcpy(tipo, token);
            token = strtok(NULL, "\r\n");
            saldo = atof(token);
            printf("%s: %.2f\n", tipo, saldo);
        }
    }
    fclose(file);
}

void escreve_ficheiro_historico(int num, char tipo[], float preco){
    FILE *file = fopen("Historico.txt", "a+b");
    fprintf(file, "%d-%s:%.2f\n", num, tipo, preco);
    fclose(file);
}

int numero_aluno (){
    int numero_aluno;

    printf("Escreva o numero de estudante do aluno:");
    scanf("%d", &numero_aluno);

    return numero_aluno;
}

lista cria (){
    lista aux;
    struct aluno a1= {"", {0, 0, 0}, 0, "", 0, 0};
    aux = (lista)malloc(sizeof (no_lista));
    if (aux != NULL) {
        aux->a = a1;
        aux->proximo = NULL;
    }
    return aux;
}

int procurar_aluno(int num_estudante, lista lista_al){  //verifica se o numero de estudante existe na struct
    lista atual = lista_al->proximo;
    while (atual) {
        if (atual->a.numero_estudante == num_estudante) {
            return 1;
        }
        atual = atual->proximo;
    }
    return 0;
}

lista procura_num_estudante (lista lista_al, int num_estudante) {
    lista atual = lista_al->proximo;
    while (atual) {
        if (atual->a.numero_estudante == num_estudante) {
            return atual;
        }
        atual = atual->proximo;
    }
    return 0;
}


void procura(lista lista_al, char *nome, lista *ant, lista *atual){ //Procura o nome na lista por ordem alfabetica
    *ant = lista_al; *atual = lista_al->proximo;
    while ((*atual) != NULL && strcmp((*atual)->a.nome, nome) < 0) {
        *ant = *atual;
        *atual = (*atual)->proximo;
    }
    if ((*atual) != NULL && strcmp((*atual)->a.nome, nome) != 0)
        *atual = NULL; /* elemento não encontrado*/
}

void procura_num(lista lista_al, int num_estudante, lista *ant, lista *atual){
    *ant = lista_al; *atual = lista_al->proximo;
    while (((*atual) != NULL) && ((*atual)->a.numero_estudante != num_estudante)) {
        *ant = *atual;
        *atual = (*atual)->proximo;
    }
}

int verifica_data(int dia, int mes, int ano){
    int count;
    if(ano < 1950 || ano > 2003) {
        printf("Ano invalido!!\n");
        count = 1;
    } else if(dia < 1 || dia > 31){
        printf("Dia invalido!!\n");
        count = 1;
    } else if(mes < 1 || mes > 12){
        printf("Mes invalido!!\n");
        count = 1;
    } else if((mes == 4 || mes == 6 || mes == 9 || mes == 11) && dia == 31){
        printf("O mes %d não tem 31 dias!!\n", mes);
        count = 1;
    } else if(mes == 2 && ((ano % 4 != 0 && dia == 29) || dia > 28)){
        printf("O mes %d so tem 28 dias, a menos que seja bixesto!!\n", mes);
        count = 1;
    } else {
        count = 0;
    }
    return count;
}


void insere_al (lista lista_al, struct aluno a) {
    lista no, ant, inutil;
    no = (lista) malloc (sizeof (no_lista));
    if (no != NULL) {
        no->a = a;
        procura (lista_al, a.nome, &ant, &inutil);
        no->proximo = ant->proximo;
        ant->proximo = no;
    }
}

void add_aluno(lista lista_al, int num_estudante){
    struct aluno a;
    char s[TAM];
    char t[TAM];
    int ano, dia, mes, ano_nascimento;
    char str;
    char *nome;
    char * turma;

    printf("Escreva o nome do aluno:\n");
    scanf("%c", &str);

    fgets(s, TAM, stdin);
    nome = strtok(s, "\n");

    printf("Escreva a turma do aluno:\n");
    fgets(t, TAM, stdin);
    turma = strtok(t, "\n");

    printf("Escreva o ano do aluno:\n");
    scanf("%d", &ano);
    printf("Escreva a data de nascimento:\n");
    scanf("%d-%d-%d", &dia, &mes, &ano_nascimento);

    if (verifica_data(dia, mes, ano_nascimento) == 0) {
        strcpy(a.nome, nome);
        strcpy(a.turma, turma);
        a.numero_estudante = num_estudante;
        a.saldo = 0;
        a.ano = ano;
        a.data1.dia = dia;
        a.data1.mes = mes;
        a.data1.ano = ano_nascimento;

        insere_al(lista_al, a);
    } else {
        printf("Ocorreu um erro.\n");
    }

}

void imprime (lista lista_al) {
    lista aux = lista_al->proximo; //Salta o header
    while (aux) {
        printf("\nNome: %s\n"
               "Data de nascimento: %d-%d-%d\n"
               "Ano de escolaridade: %d\n"
               "Turma: %s\n"
               "Numero de estudante: %d\n"
               "Saldo: %.2f\n\n", aux->a.nome, aux->a.data1.dia, aux->a.data1.mes, aux->a.data1.ano, aux->a.ano, aux->a.turma, aux->a.numero_estudante, aux->a.saldo);
        aux = aux->proximo;
    }
}

void elimina_aluno (lista lista_al, int num_estudante){
    lista ant, atual;
    procura_num(lista_al, num_estudante, &ant, &atual);
    if (atual != NULL) {
        ant->proximo = atual->proximo;
        free (atual);
    }
}


void carrega_conta (lista lista_al, int num_estudante) {

    lista atual= procura_num_estudante(lista_al, num_estudante);

    float valor;
    printf("Indique a quantia que quer fazer o carregamento:");
    scanf("%f", &valor);

    atual->a.saldo += valor;
    printf("Saldo corrente do aluno numero %d: %.2f euros.\n", atual->a.numero_estudante, atual->a.saldo);
    escreve_ficheiro_historico(num_estudante, "Carregamento", valor);
}

void consulta_saldo (lista lista_al, int num_estudante) {
    lista atual = procura_num_estudante(lista_al, num_estudante);
    printf("Saldo corrente do aluno numero %d: %.2f euros.\n", atual->a.numero_estudante, atual->a.saldo);
}

void informacao_aluno (lista lista_al, int num_estudante) {
    lista atual = procura_num_estudante(lista_al, num_estudante);
    printf("\nNome: %s\n"
           "Data de nascimento: %d-%d-%d\n"
           "Ano de escolaridade: %d\n"
           "Turma: %s\n"
           "Numero de estudante: %d\n"
           "Saldo: %.2f\n\n", atual->a.nome, atual->a.data1.dia, atual->a.data1.mes, atual->a.data1.ano, atual->a.ano, atual->a.turma, atual->a.numero_estudante, atual->a.saldo);
}

void transferencia (lista lista_al, int num_estudante1, int num_estudante2){
    lista atual1 = procura_num_estudante(lista_al, num_estudante1);
    lista atual2 = procura_num_estudante(lista_al, num_estudante2);

    float valor;
    printf ("Indique o valor que quer transferir: ");
    scanf ("%f", &valor);
    if (atual1->a.saldo >= valor){
        atual1->a.saldo -= valor;
        atual2->a.saldo += valor;
        printf("Saldo apos a transicao: %.2f.\n", atual1->a.saldo);
        escreve_ficheiro_historico(num_estudante1, "Transferencia Efetuada", valor);
        escreve_ficheiro_historico(num_estudante2, "Transferencia Recebida", valor);
    } else {
        printf("Saldo insuficiente, tente introduzir outra quantia.\n");
    }
}

void menu_compra(){
    printf("\nInsira o numero correspondente a operacao que pretende realizar\n"
           "\t\t\t1 : 'Compra Bar'\n"
           "\t\t\t2 : 'Compra Repografia'\n"
           "\t\t\t3 : 'Compra Cantina'\n"
           "\t\t\t0 : 'Sair'\n"
           "Opcao:");
}

void menu_bar(){
    printf("\nInsira o numero correspondente a operacao que pretende realizar\n"
           "\t\t\t1 : 'Croissant - 0.65'\n"
           "\t\t\t2 : 'Croissant misto - 1.00'\n"
           "\t\t\t3 : 'Refrigerante - 1.00'\n"
           "\t\t\t4 : 'Cafe - 0.60'\n"
           "\t\t\t5 : 'Torrada - 0.85'\n"
           "\t\t\t6 : 'Bolos - 0.60'\n"
           "\t\t\t7 : 'Baguete' - 1.60'\n"
           "\t\t\t0 : 'Sair'\n"
           "Opcao:");
}

float preco_bar(int opcao, bool verifico){
    float preco;
    if (opcao == 1){
        preco = (float)0.65;
    } else if (opcao == 2 || opcao == 3){
        preco = (float)1.00;
    } else if (opcao == 4 || opcao == 6){
        preco = (float)1.30;
    } else if (opcao == 5){
        preco = (float)0.85;
    } else if (opcao == 7){
        preco = (float)1.60;
    } else if (opcao == 0){
        verifico = false;
    } else {
        printf("Opcao invalida. Tente outra vez\n");
    }

    return preco;
}

void menu_repografia(){
    printf("\nInsira o numero correspondente a operacao que pretende realizar\n"
           "\t\t\t1 : 'Fotocopia - 0.15'\n"
           "\t\t\t2 : 'Cadernos - 0.50'\n"
           "\t\t\t3 : 'Material de escrita - 1.00'\n"
           "\t\t\t4 : 'Estojo - 1.00'\n"
           "\t\t\t5 : 'Carregador para PC - 15.00'\n"
           "\t\t\t6 : 'Pen Drive - 7.00'\n"
           "\t\t\t0 : 'Sair'\n"
           "Opcao:");
}

float preco_repografia(int opcao, bool verifico){
    float preco;
    if (opcao == 1) {
        preco = (float) 0.15;
    } else if (opcao == 2) {
        preco = (float) 0.50;
    } else if (opcao == 3 || opcao == 4) {
        preco = (float) 1.00;
    } else if (opcao == 5) {
        preco = (float) 15.00;
    } else if (opcao == 6) {
        preco = (float) 7.00;
    } else if (opcao == 0) {
        verifico = false;
    } else {
        printf("Opcao invalida. Tente outra vez\n");
    }

    return preco;
}

void menu_cantina(){
    printf("\nInsira o numero correspondente a operacao que pretende realizar\n"
           "\t\t\t1 : 'Almoco (Carne) - 2.50'\n"
           "\t\t\t2 : 'Almoco (Peixe) - 2.50'\n"
           "\t\t\t3 : 'Almoco (Vegetariano) - 2.50'\n"
           "\t\t\t4 : 'Jantar (Carne) - 2.50'\n"
           "\t\t\t5 : 'Jantar (Peixe) - 2.50'\n"
           "\t\t\t6 : 'Jantar (Vegetariano) - 2.50'\n"
           "\t\t\t0 : 'Sair'\n"
           "Opcao:");
}

float preco_cantina(int opcao, bool verifico) {
    float preco;
    if (opcao >= 1  && opcao <= 6) {
        preco = (float )2.50;
    } else if (opcao == 0) {
        verifico = false;
    } else {
        printf("Opcao invalida. Tente outra vez\n");
    }

    return preco;
}

void efetua_compra (lista lista_al, int num_estudante, bool verifico, struct stock s){

    lista atual = procura_num_estudante(lista_al, num_estudante);
    int opcao;
    menu_compra();
    scanf("%d", &opcao);
    printf("\n");

    if (opcao == 1) {
        int opcao_bar;
        menu_bar();
        scanf("%d", &opcao_bar);
        int opcao_stock = opcao_bar + 6;
        float preco = preco_bar(opcao_bar, verifico);

        if (atual->a.saldo >= preco){
            if (verificar_stock(opcao_stock, s) == 1) {
                atual->a.saldo -= preco;
                printf("Saldo corrente do aluno numero %d: %.2f euros.\n", atual->a.numero_estudante, atual->a.saldo);
                escreve_ficheiro_historico(num_estudante, "Compra Bar", preco);
            }

        } else {
            printf("Saldo insuficiente");
        }
    } else if (opcao == 2) {
        int opcao_repografia;
        menu_repografia();
        scanf("%d", &opcao_repografia);
        float preco = preco_repografia(opcao_repografia, verifico);

        if (atual->a.saldo >= preco){
            if (verificar_stock(opcao_repografia, s) == 1) {
                atual->a.saldo -= preco;
                printf("\nSaldo corrente do aluno numero %d: %.2f euros.\n", atual->a.numero_estudante, atual->a.saldo);

                escreve_ficheiro_historico(num_estudante, "Compra Repografia", preco);
            }
        } else {
            printf("Saldo insuficiente");
        }
    } else if (opcao == 3) {
        int opcao_cantina;
        menu_cantina();
        scanf("%d", &opcao_cantina);
        float preco = preco_cantina(opcao_cantina, verifico);

        if (atual->a.saldo >= preco){
            atual->a.saldo -= preco;
            printf("Saldo corrente do aluno numero %d: %.2f euros.\n", atual->a.numero_estudante, atual->a.saldo);
            escreve_ficheiro_historico(num_estudante, "Compra Cantina", preco);
        } else {
            printf("Saldo insuficiente");
        }
    } else if (opcao == 0) {
        verifico = false;
    } else {
        printf("Opcao invalida. Tente outra vez\n");
    }
}

int verifica_saldo(float saldo[], float sal, int tam){
    for(int i = 0; i < tam; i++){
        if(saldo[i] == sal){
            return 1;
        }
    }
    return 0;
}

void alunos_inf_saldo(lista lista_al) {
    lista atual = lista_al->proximo;

    float valor;
    printf("Indique o limite de saldo que pretende: ");
    scanf("%f", &valor);

    float saldo[TAM];
    int i = 0;

    while (atual) {
        if (atual->a.saldo < valor && verifica_saldo(saldo, atual->a.saldo, i) == 0) {
            saldo[i] = atual->a.saldo;
            i++;
        }
        atual = atual->proximo;
    }

    if (i == 0){
        printf ("Nao existe nenhum aluno com saldo inferior a esse valor.\n");
    }


    float auxiliar;

    for (int y = 0; y < i; y++) {
        for (int j = y + 1; j < i; j++) {
            if (saldo[y] > saldo[j]) {
                auxiliar = saldo[j];
                saldo[j] = saldo[y];
                saldo[y] = auxiliar;
            }
        }
    }


    lista aux = lista_al->proximo;
    while (aux) {
        for (int z = 0; z < i; z++) {
            if (aux->a.saldo == saldo[z]) {
                printf("Aluno: %s \nSaldo: %.2f\n", aux->a.nome, aux->a.saldo);
            }
        }
        aux = aux->proximo;
    }
}


void encher_stock(bool verifico, struct stock s){

    int opcao_encher_stock;
    menu_stock();
    scanf("%d", &opcao_encher_stock);

    if (opcao_encher_stock == 0){
        verifico = false;
    } else if (opcao_encher_stock > 0 && opcao_encher_stock <= 13){

        int quantidade;
        printf("\nEscreva a quantia que quer adicionar a sua opcao:");
        scanf("%d", &quantidade);

        if (opcao_encher_stock == 1){
            s.stock_papel += quantidade;
        } else if (opcao_encher_stock == 2){
            s.stock_cadernos += quantidade;
        } else if (opcao_encher_stock == 3){
            s.stock_material += quantidade;
        } else if (opcao_encher_stock == 4){
            s.stock_estojo += quantidade;
        } else if (opcao_encher_stock == 5){
            s.stock_carregador += quantidade;
        } else if (opcao_encher_stock == 6){
            s.stock_pendrive += quantidade;
        } else if (opcao_encher_stock == 7){
            s.stock_croissant += quantidade;
        } else if (opcao_encher_stock == 8){
            s.stock_queijo += quantidade;
        } else if (opcao_encher_stock == 9){
            s.stock_refri += quantidade;
        } else if (opcao_encher_stock == 10){
            s.stock_cafe += quantidade;
        } else if (opcao_encher_stock == 11){
            s.stock_torrada += quantidade;
        } else if (opcao_encher_stock == 12){
            s.stock_bolos += quantidade;
        } else {
            s.stock_baguete += quantidade;
        }
        printf ("Operacao efetuada com sucesso\n");
    } else {
        printf("Opcao invalida, tente outra vez.\n");
    }
}

void imprimir_stock(struct stock s){
    printf("Papel para fotocopia: %d\n"
           "Cadernos: %d\n"
           "Material de escrita: %d\n"
           "Estojo: %d\n"
           "Carregador para PC: %d\n"
           "Pen Drive: %d\n"
           "Croissant: %d\n"
           "Fiambre/Queijo: %d\n"
           "Refrigerante: %d\n"
           "Cafe: %d\n"
           "Torrada: %d\n"
           "Bolos: %d\n"
           "Baguete: %d\n", s.stock_papel, s.stock_cadernos, s.stock_material, s.stock_estojo, s.stock_carregador, s.stock_pendrive, s.stock_croissant, s.stock_queijo, s.stock_refri, s.stock_cafe, s.stock_torrada, s.stock_bolos, s.stock_baguete);
}

int verificar_stock(int opcao, struct stock s){
    if (opcao == 1){
        if (s.stock_papel - 1 >= 0){
            s.stock_papel -= 1;
            return 1;
        }
    } else if (opcao == 2){
        if (s.stock_cadernos - 1 >= 0){
            s.stock_cadernos -= 1;
            return 1;
        }
    } else if (opcao == 3){
        if (s.stock_material - 1 >= 0){
            s.stock_material -= 1;
            return 1;
        }
    } else if (opcao == 4){
        if (s.stock_estojo - 1 >= 0){
            s.stock_estojo -= 1;
            return 1;
        }
    } else if (opcao == 5){
        if (s.stock_carregador - 1 >= 0){
            s.stock_carregador -= 1;
            return 1;
        }
    } else if (opcao == 6){
        if (s.stock_pendrive - 1 >= 0){
            s.stock_pendrive -= 1;
            return 1;
        }
    } else if (opcao == 7){
        if (s.stock_croissant - 1 >= 0){
            s.stock_croissant -= 1;
            return 1;
        }
    } else if (opcao == 8){
        if (s.stock_queijo - 1 >= 0){
            s.stock_queijo -= 1;
            return 1;
        }
    } else if (opcao == 9){
        if (s.stock_refri - 1 >= 0){
            s.stock_refri -= 1;
            return 1;
        }
    } else if (opcao == 10){
        if (s.stock_cafe - 1 >= 0){
            s.stock_cafe -= 1;
            return 1;
        }
    } else if (opcao == 11){
        if (s.stock_torrada - 1 >= 0){
            s.stock_torrada -= 1;
            return 1;
        }
    } else if (opcao == 12){
        if (s.stock_bolos - 1 >= 0){
            s.stock_bolos -= 1;
            return 1;
        }
    } else if (opcao == 13){
        if (s.stock_baguete - 1 >= 0){
            s.stock_baguete -= 1;
            return 1;
        }
    }
    return 0;
}

void altera_dados_utilizador(bool verifico, lista lista_al){
    int opcao;
    menu_altera_dados();
    scanf("%d", &opcao);

    char s[TAM];
    char t[TAM];
    int ano, dia, mes, ano_nascimento;
    char str;
    char * nome;
    char * turma;

    if (opcao == 0){
        verifico = false;
    } else if (opcao >= 1 && opcao <= 5){
        int num_estudante = numero_aluno();
        int procura= procurar_aluno(num_estudante, lista_al);

        lista ant, atual;
        procura_num(lista_al, num_estudante, &ant, &atual);
        if (opcao == 1) {
            if (procura == 1) {
                printf ("Escreva o novo nome:");
                scanf("%c", &str);
                fgets(s, TAM, stdin);
                nome = strtok(s, "\n");

                strcpy(atual->a.nome, nome);
                printf ("\nAlteracao efetuada com sucesso.\n");
            } else {
                printf("Numero de estudante invalido.");
            }
        } else if (opcao == 2) {
            if (procura == 1) {
                printf ("Escreva o ano:");
                scanf ("%d", &ano);

                atual->a.ano = ano;
                printf ("\nAlteracao efetuada com sucesso.\n");
            } else {
                printf("Numero de estudante invalido.");
            }
        } else if (opcao == 3) {
            if (procura == 1) {
                printf ("Escreva a nova turma:");
                scanf("%c", &str);
                fgets(t, TAM, stdin);
                turma = strtok(t, "\n");

                strcpy(atual->a.turma, turma);
                printf ("\nAlteracao efetuada com sucesso.\n");
            } else {
                printf("Numero de estudante invalido.");
            }
        } else if (opcao == 4) {
            if (procura == 1) {
                printf ("Escreva o novo numero de estudante:");
                scanf ("%d", &num_estudante);

                if (procurar_aluno(num_estudante, lista_al) == 0) {
                    atual->a.numero_estudante = num_estudante;
                    printf("\nAlteracao efetuada com sucesso.\n");
                } else{
                    printf ("O numero de estudante ja existe, tente outra vez.\n\n");
                }
            } else {
                printf("Numero de estudante invalido.");
            }
        } else if (opcao == 5) {
            if (procura == 1) {
                printf ("Escreva a nova data:");
                scanf ("%d-%d-%d", &dia, &mes, &ano_nascimento);

                if (verifica_data(dia, mes, ano_nascimento) == 0){
                    atual->a.data1.dia = dia;
                    atual->a.data1.mes = mes;
                    atual->a.data1.ano = ano_nascimento;
                    printf ("\nAlteracao efetuada com sucesso.\n");
                }else{
                    printf ("Ocorreu um erro.\n");
                }
            } else {
                printf("Numero de estudante invalido.");
            }
        }

    } else {
        printf("Opcao invalida. Tente outra vez\n");
    }
}



/**
 * Ficheiro principal do projeto. Lê todos os comandos e executa-os.
 * @file Projeto.c
 * @author ist1109886
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "Parques.h"
#include "Veiculos.h"
#include "Projeto.h"

/**
 * Lê todos os comandos no início de cada linha e chama a 
 * função correspondente para ler o resto dos argumentos.
 * @param N_Parques número de parques existentes no sistema.
 * @param last_data último registo de entradas ou saídas no sistema.
*/
void input(int *N_Parques, Data *last_data){

    int c;

    // lê os comandos até encontrar o comando 'q'.
    while((c = getchar()) != 'q'){
       if (c == 'p'){
            le_p(N_Parques);
       }
       if (c == 'e'){
            le_e(last_data);
       }
       if (c == 's'){
            le_s(last_data);
       }
       if (c == 'v'){
            le_v();
       }
       if (c == 'f'){
            le_f(last_data);
       }
       if (c == 'r'){
            le_r(N_Parques);
       }
       if (c == 't'){
            le_t();
       }
    }

    apaga_memoria(*N_Parques);
}


/**
 * Lê um nome de um parque do input.
 * @param nome variável para onde o nome do parque é guardado.
 * @return ARGS caso consiga ler um nome ou NO_ARGS caso não existam argumentos
 * nessa linha.
*/
int le_nome(char nome[]){
    int c, i;

    // Lê o comando até encontrar um \n.
    while((c = getchar()) != '\n'){
        // Caso o nome esteja entre aspas.
        if (c == '"'){
            for(i = 0; (c = getchar()) != '"'; i++){
                nome[i] = c;
            }
            nome[i] = '\0';
            return ARGS;
        }

        // Caso o nome esteja entre espaços.
        else if (!isspace(c)){
            nome[0] = c;
            for(i = 1; !isspace(c = getchar()); i++){
                nome[i] = c;
            }
            nome[i] = '\0';
            if (c == '\n'){
                return NO_ARGS;
            }
            return ARGS;
        }
    }
    return NO_ARGS;
}


/**
 * Lê o comando p e chama executa_p com os argumentos certos ou chama lista_p 
 * caso não existam argumentos.
 * @param N_Parques número de parques existentes no sistema.
*/
void le_p(int *N_Parques){

    int capacidade, args;
    float valorX, valorY, valorZ;
    char arg_nome[BUFFER];

    args = le_nome(arg_nome);

    if(args == NO_ARGS){
        lista_p();
    }

    // Input dos restantes valores do Parque.
    else{
        scanf("%d%f%f%f", &capacidade, &valorX, &valorY, &valorZ);
        executa_p(arg_nome, capacidade, valorX, valorY, valorZ, N_Parques);
    }
}


/**
 * Executa o comando p.
 * @param nome nome do parque.
 * @param capacidade capacidade do parque.
 * @param valorX valor cobrado a cada 15 minutos na primeira hora.
 * @param valorY valor cobrado a cada 15 minutos depois da primeira hora.
 * @param valorZ valor máximo diário (24h).
 * @param N_Parques número de parques existentes no sistema.
*/
void executa_p(char nome[], int capacidade, float valorX, float valorY,
float valorZ, int *N_Parques){
    Parque new_parque;

    if (procura_p(nome) != NULL){
        printf("%s: parking already exists.\n", nome);
        return;
    }
    if (strlen(nome) > 100){
        printf("invalid parking name.\n");
        return;
    }   
    if (capacidade <= 0){
        printf("%d: invalid capacity.\n", capacidade);
        return;
    }
    if (valorX <= 0 || valorY <= 0 || valorX <= 0 || valorX >= valorY ||
    valorY >= valorZ){
        printf("invalid cost.\n");
        return;
    }
    if (*N_Parques >= MAX_PARQUES){
        printf("too many parks.\n");
        return;
    }
    
    new_parque = init_P(nome, capacidade, valorX, valorY, valorZ);

    // Guarda o parque na lista de parques.
    push_P(new_parque);
    *N_Parques += 1;
}


/**
 * Lê todos os argumentos do comando e e depois chama a 
 * função executa_e com os argumentos corretos.
 * @param last_data último registo de entradas ou saídas no sistema.
*/
void le_e(Data *last_data){
    char arg_nome[BUFFER], matricula[TAMANHO_MATRICULA];
    Data data;

    le_nome(arg_nome);
    scanf("%s", matricula);
    data = le_data();

    executa_e(arg_nome, matricula, data, last_data);
}


/**
 * Confirma possíveis erros no comando e.
 * @param nome nome do parque.
 * @param matricula matricula do veículo.
 * @param linkP ponteiro para o parque na lista
 * @param linkV ponteiro para o veículo na hash_table
 * @param data data de entrada.
 * @param last_data último registo de entradas ou saídas no sistema.
 * @param comando comando a ser checkado.
 * @return verdadeiro ou falso (1 ou 0).
*/
int e_and_s_check(char nome[], char matricula[], link_P linkP, 
HashNode linkV, Data data, Data *last_data, char comando){
    if (linkP == NULL){
        printf("%s: no such parking.\n", nome);
        return FALSE;
    }

    if (linkP->parque.capacidade == linkP->parque.N_veiculos && comando == 'e'){
        printf("%s: parking is full.\n", nome);
        return FALSE;
    }

    if (! matricula_check(matricula)){
        printf("%s: invalid licence plate.\n", matricula);
        return FALSE;
    }

    if (comando == 'e' && linkV != NULL && linkV->veiculo.local != NULL){
        printf("%s: invalid vehicle entry.\n", matricula);
        return FALSE;
        }
    if (comando == 's' && (linkV == NULL || linkV->veiculo.local == NULL ||
    strcmp(linkV->veiculo.local->nome, nome))){
        printf("%s: invalid vehicle exit.\n", matricula);
        return FALSE;
    }

    if (!data_check(data) || cmp_data(data, last_data) < 0){
        printf("invalid date.\n");
        return FALSE;
    }

    return TRUE;
}


/**
 * Executa o comando e.
 * @param nome nome do parque onde entra o veículo.
 * @param matricula matricula do veículo.
 * @param Data data de entrada do veículo.
 * @param last_data último registo de entradas ou saídas no sistema.
*/
void executa_e(char nome[], char matricula[], Data data, Data *last_data){
    link_P linkP;
    HashNode linkV;
    Entrada entrada;
    Veiculo novo_V;

    linkP = procura_p(nome);
    linkV = procura_v(matricula);

    // Erros
    if (!e_and_s_check(nome, matricula, linkP, linkV, data, last_data, 'e'))
        return;

    // Atualiza a última data, inicializa a variável entrada e aumenta 
    // o número de veículos no parque.
    *last_data = data;
    entrada.data_e = data;
    entrada.nome = linkP->parque.nome;
    linkP->parque.N_veiculos += 1;

    // Caso o veículo não seja novo, então o local é atualizado.
    if (linkV != NULL){
    linkV->veiculo.local = (Entrada *)malloc(sizeof(entrada));
    *linkV->veiculo.local = entrada;
    }
    // Caso o veículo seja novo, todas as variáveis são inicializadas e 
    // é adicionado um novo veículo à pilha de veículos.
    else if (linkV == NULL){
        novo_V.local = (Entrada *)malloc(sizeof(entrada));
        *novo_V.local = entrada;
        strcpy(novo_V.matricula, matricula);
        novo_V.historico = NULL;
        push_V(novo_V);
    }

    printf("%s %d\n", linkP->parque.nome, 
    linkP->parque.capacidade - linkP->parque.N_veiculos);
}


/**
 * Lê o comando s e chama a função executa_s com os argumentos corretos.
 * @param last_data último registo de entradas ou saídas no sistema.
*/
void le_s(Data *last_data){
    char arg_nome[BUFFER], matricula[TAMANHO_MATRICULA];
    Data data;

    le_nome(arg_nome);
    scanf("%s", matricula);
    scanf("%d-%d-%d", &data.dia, &data.mes, &data.ano);
    scanf("%d:%d", &data.hora, &data.min);

    executa_s(arg_nome, matricula, data, last_data);
}


/**
 * Executa o comando s.
 * @param nome nome do parque onde sai o veículo.
 * @param matricula matricula do veículo.
 * @param Data data de saída do veículo.
 * @param last_data último registo de entradas ou saídas no sistema.
*/
void executa_s(char nome[], char matricula[], Data data, Data *last_data){
    HashNode linkV;
    link_P linkP;
    Registo novo_R;
    Registo_P novo_RP;
    link_D linkD;
    float faturacao;

    linkP = procura_p(nome);
    linkV = procura_v(matricula);

    // Erros.
    if (!e_and_s_check(nome, matricula, linkP, linkV, data, last_data, 's'))
        return;

    // Calcula a faturação do veículo.
    faturacao = fatura(linkV->veiculo.local->data_e, data,
    linkP->parque.valorX, linkP->parque.valorY, linkP->parque.valorZ);

    // Inicializa as variáveis do novo registo.
    novo_R = init_R(linkV->veiculo.local->data_e, data,
    linkV->veiculo.local->nome);

    // Adiciona o registo ao histórico do veículo.
    linkV->veiculo.historico = push_RV(novo_R, linkV->veiculo.historico);

    // Atualiza o local do veículo e o número de veículos dentro do parque.
    free(linkV->veiculo.local);
    linkV->veiculo.local = NULL;
    linkP->parque.N_veiculos -= 1;

    // Procura o dia correspondente à saída do parque e caso não encontre,
    // cria um novo dia, incializando as variáveis e guarda o dia dentro 
    // da lista no parque. Caso encontre, aumenta a faturação diária 
    // desse parque.
    linkD = procura_d(data, linkP->parque.head_D);
    if (linkD == NULL){
        linkD = init_D(data, faturacao, linkP);
    }
    else{
        linkD->dia.faturacao += faturacao;
    }

    // Adiciona o novo registo de parques ao parque, no dia correspondente.
    novo_RP = init_RP(novo_R.data_s, matricula, faturacao);
    push_RP(novo_RP, &linkD->dia);

    print_s(matricula, novo_R, faturacao);
}


/**
 * Lê a matrícula do comando v e chama executa_v com a matrícula lida.
*/
void le_v(){
    char matricula[TAMANHO_MATRICULA];

    scanf("%s", matricula);
    executa_v(matricula);
}

/**
 * Executa o comando v.
 * @param matricula matrícula do veículo.
*/
void executa_v(char matricula[]){
    HashNode linkV;

    // Erros.
    if (! matricula_check(matricula)){
        printf("%s: invalid licence plate.\n", matricula);
        return;
    }

    linkV = procura_v(matricula);

    if(linkV == NULL || (linkV->veiculo.historico == NULL && 
    linkV->veiculo.local == NULL)){
        printf("%s: no entries found in any parking.\n", matricula);
        return;
    }

    lista_R(linkV->veiculo.historico, linkV->veiculo.local);
}


/**
 * Lê o comando f e chama a função executa_f_1 ou executa_f_2 
 * dependendo do número de argumentos.
 * @param last_data último registo de entradas ou saídas no sistema.
*/
void le_f(Data *last_data){
    char arg_nome[BUFFER], buffer[BUFFER];
    int arg, i, n;
    Data data = {0, 0, 0, 0, 0};

    arg = le_nome(arg_nome);

    // Caso possam existir mais argumentos confirma se existem.
    if (arg){
        arg = FALSE;
        fgets(buffer, BUFFER, stdin);
        n = strlen(buffer);

        for(i = 0; i < n; i++){
            if (!isspace(buffer[i])){
                arg = TRUE;
            }
        }
    }

    if (!arg){
        executa_f_1(arg_nome);
    }

    else if (arg){
        sscanf(buffer, "%d-%d-%d", &data.dia, &data.mes, &data.ano);
        executa_f_2(arg_nome, data, last_data);
    }
}


/**
 * Executa o comando f com apenas 1 argumento.
 * @param nome nome do parque.
*/
void executa_f_1(char nome[]){
    link_P linkP;
    int found = FALSE;

    linkP = procura_p(nome);
    if (linkP != NULL){
        found = TRUE;
    }

    // Erro.
    if (!found){
        printf("%s: no such parking.\n", nome);
        return;
    }

    lista_f(linkP->parque.head_D);
}


/**
 * Executa o comando f com apenas 2 argumentos.
 * @param nome nome do parque.
 * @param data dia a listar a faturação.
 * @param last_data último registo de entradas ou saídas no sistema. 
*/

void executa_f_2(char nome[], Data data, Data *last_data){
    link_P linkP;
    link_D linkD;
    int found = FALSE;

    linkP = procura_p(nome);
    if (linkP != NULL){
        found = TRUE;
    }

    // Erros.
    if (!found){
        printf("%s: no such parking.\n", nome);
        return;
    }

    if (!data_check(data) || cmp_data(data, last_data) > 0){
        printf("invalid date.\n");
        return;
    }

    linkD = procura_d(data, linkP->parque.head_D);
    if (linkD == NULL){
        return;
    }
    else{
        lista_f_data(linkD->dia.head_RP);
    }
}
/**
 * Lê os argumentos do comando r e chama a função executa_r com os 
 * argumentos corretos.
 * @param N_Parques número de parques existentes no sistema.
*/

void le_r(int *N_Parques){
    char arg_nome[BUFFER];

    le_nome(arg_nome);

    executa_r(arg_nome, N_Parques);
}


/**
 * Executa o comando r.
 * @param nome nome do parque.
 * @param N_Parques número de parques existentes no sistema.
*/

void executa_r(char nome[], int *N_Parques){
    link_P linkP;
    char parques[MAX_PARQUES][BUFFER];
    int i;

    linkP = procura_p(nome);

    // Erro.
    if (linkP == NULL){
        printf("%s: no such parking.\n", nome);
        return;
    }

    // Apaga o histórico do parque, apaga o parque da lista e atualiza
    // o número de parques.
    apaga_historico(nome);
    pop_P(nome);
    *N_Parques -= 1;

    // Ordena os parques por ordem alfabética para os imprimir.
    vetor_p_ord(parques, *N_Parques);

    for (i = 0; i < *N_Parques; i++){
        printf("%s\n", parques[i]);
    }
}


/**
 * Lê do input o argumento do comando t e chama a função executa_t.
*/
void le_t(){
    char nome[BUFFER];

    le_nome(nome);

    executa_t(nome);
}


/**
 * Executa o comando t. Procura pelo parque correspondente 
 * e calcula a sua faturação.
 * @param nome nome do parque.
*/
void executa_t(char nome[]){
    link_P linkP;
    float faturacao;

    linkP = procura_p(nome);

    if (linkP == NULL){
        printf("%s: no such parking.\n", nome);
        return;
    }

    faturacao = calcula_faturacao(linkP);

    printf("%.2f\n", faturacao);
}


/**
 * Apaga toda a memória alocada antes de fechar o programa.
 * @param N_Parques número de parques.
*/
void apaga_memoria(int N_Parques){
    char parques[MAX_PARQUES][BUFFER];
    int i;

    vetor_p_ord(parques, N_Parques);
    for (i = 0; i < N_Parques; i++){
        apaga_historico(parques[i]);
        pop_P(parques[i]);
    }
    apaga_veiculos();
}
/**
 * Função main. Inicializa as variáveis e chama a função input.
 * @return retorna sempre 0.
*/
int main(){
    Data last_data = {0, 0, 0, 0, 0};
    int N_Parques = 0;

    input(&N_Parques, &last_data);

    return 0;
}
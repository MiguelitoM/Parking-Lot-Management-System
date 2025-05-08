/**
 * Ficheiro relativo aos veículos.
 * @file Veiculos.c
 * @author ist1109886
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "Veiculos.h"

// Hash_table para guardar os veículos.
static HashNode hash_table[HASH_TABLE_SIZE];

/**
 * Recebe uma string e devolve uma chave para a hash_table.
 * @param str matrícula.
 * @return chave para a hash_table.
*/
unsigned long hash_djb2(char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    return hash % HASH_TABLE_SIZE;
}


/**
 * Procura um veículo na hash_table.
 * @param matricula matrícula do veículo.
 * @return ponteiro para o veículo.
*/
HashNode procura_v(char matricula[]) {
    HashNode current;
    // Encontra a chave.
    unsigned long index = hash_djb2(matricula);

    // Procura o veículo na lista correspondente à chave.
    current = hash_table[index];
    while (current != NULL) {
        if (!strcmp(current->veiculo.matricula, matricula)) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}


/**
 * Insere um veículo na hash_table.
 * @param veiculo veículo.
*/
void push_V(Veiculo veiculo) {
    HashNode new_node;
    // Encontra a chave.
    unsigned long index = hash_djb2(veiculo.matricula);
    // Aloca a memória necessária e insere o veículo na lista dentro da tabela.
    new_node = (HashNode )malloc(sizeof(struct hash_node));

    new_node->veiculo = veiculo;
    new_node->next = hash_table[index];
    hash_table[index] = new_node;
}


/**
 * Inicializa um registo com as variáveis recebidas.
 * @param data_e data de entrada.
 * @param data_s data de saída.
 * @param nome nome do parque.
 * @return registo inicializado.
*/
Registo init_R(Data data_e, Data data_s, char *nome){
    Registo registo;

    registo.data_e = data_e;
    registo.data_s = data_s;
    registo.nome = nome;

    return registo;
}


/**
 * Insere um registo de veículos na sua lista de forma alfabética.
 * @param registo registo a inserir.
 * @param head cabeça da lista.
 * @return a cabeça da lista possivelmente alterada.
*/
link_R push_RV(Registo registo, link_R head){
    link_R new, x, previous = NULL;

    // Aloca a memória necessária e inicializa new.
    new = (link_R) malloc(sizeof(struct node_R));
    new -> registo = registo;
    new -> next = NULL;

    if (head == NULL){
        head = new;
        return head;
    }

    // Encontra o sítio onde inserir o registo e insere-o na lista.
    for (x = head; x != NULL; x = x->next){
        if (strcmp(x->registo.nome, new->registo.nome) > 0){
            if(previous == NULL){
                head = new;
                new -> next = x;
            }
            else{
                previous -> next = new;
                new -> next = x;
            }
            return head;
        }
        previous = x;
    }

    previous->next = new;
    return head;
}


/**
 * Remove todos os registos de veículos de um dado parque.
 * @param nome nome do parque.
 * @param head cabeça da lista do registo.
 * @return a cabeça da lista possivelmente alterada.
*/
link_R pop_RV(char nome[], link_R head){
    link_R current = head, temp, previous = NULL;

    // Percorre a lista toda e quando encontra um registo com o nome do parque,
    // apaga esse registo e liberta a memória.
    while (current != NULL){
        if (!strcmp(nome, current->registo.nome)){
            if (previous == NULL){
                head = current->next;
            }
            else{
                previous->next = current->next;
            }
            temp = current;
            current = current ->next;
            free(temp);
        }
        else{
            previous = current;
            current = current -> next;
        }
    }
    return head;
}


/**
 * Imprime o output do comando s.
 * @param matricula matrícula do veículo
 * @param registo registo a imprimir.
 * @param faturacao faturação do registo.
*/
void print_s(char matricula[], Registo registo, float faturacao){

    printf("%s %02d-%02d-%04d %02d:%02d %02d-%02d-%04d %02d:%02d %.2f\n",
    matricula, registo.data_e.dia, 
    registo.data_e.mes, registo.data_e.ano, registo.data_e.hora, registo.data_e.min,
    registo.data_s.dia, registo.data_s.mes, registo.data_s.ano, registo.data_s.hora,
    registo.data_s.min, faturacao);
}


/**
 * Lista o registo de um veículo, incluindo o sítio onde está.
 * @param head cabeça da lista do registo.
 * @param local local onde se encontra o veículo. Pode ser NULL.
*/
void lista_R(link_R head, Entrada *local){
    link_R x;
    Registo registo;

    for (x = head; x != NULL; x = x->next){
        registo = x->registo;

        // Entrada.
        if (local != NULL && strcmp(registo.nome, local->nome) > 0){
            printf("%s %02d-%02d-%04d %02d:%02d\n", local->nome, 
            local->data_e.dia, local->data_e.mes, local->data_e.ano, 
            local->data_e.hora, local->data_e.min);

            local = NULL;
        }

        // Resto.
        printf("%s %02d-%02d-%04d %02d:%02d %02d-%02d-%04d %02d:%02d\n",
        registo.nome, 
        registo.data_e.dia, registo.data_e.mes, registo.data_e.ano, 
        registo.data_e.hora, registo.data_e.min, registo.data_s.dia,
        registo.data_s.mes, registo.data_s.ano, registo.data_s.hora,
        registo.data_s.min);
    }

    // Caso a entrada seja impressa no fim.
    if (local != NULL){
        printf("%s %02d-%02d-%04d %02d:%02d\n", local->nome, 
        local->data_e.dia, local->data_e.mes, local->data_e.ano, 
        local->data_e.hora, local->data_e.min);

        local = NULL;
    }
}


/**
 * Confirma se uma dada matrícula é válida.
 * @param matricula matrícula.
 * @return Verdadeiro ou Falso (1 ou 0). 
*/

int matricula_check(char matricula[]){
    int i;
    for (i = 0; i < TAMANHO_MATRICULA-1; i++){
        if (i!=2 && i!= 5 && !(isupper(matricula[i]) || isdigit(matricula[i]))){
            return 0;
        }
    }

    if (isupper(matricula[0]) != isupper(matricula[1]) ||
    isupper(matricula[3]) != isupper(matricula[4]) ||
    isupper(matricula[6]) != isupper(matricula[7])){
        return 0;
    }
    if (!isupper(matricula[0]) && !isupper(matricula[3])
    && !isupper(matricula[6])){
        return 0;
    }
    return 1;
}


/**
 * Remove todos os registos de veículos de um dado parque.
 * @param nome nome do parque.
*/
void apaga_historico(char nome[]){
    int i;
    HashNode current;

    // Percorre a hash_table e apaga o registo de veículos 
    // quando encontra o nome do parque a apagar.
    for(i = 0; i < HASH_TABLE_SIZE; i++){
        current = hash_table[i];
        while (current != NULL){
            if (current->veiculo.local != NULL && 
            !strcmp(nome, current->veiculo.local->nome)){
                free(current->veiculo.local);
                current->veiculo.local = NULL;
            }
            current->veiculo.historico = pop_RV(nome, current->veiculo.historico);

            current = current -> next;
        }
    }
}


/**
 * Apaga e liberta a memória de todos os veículos da hash_table.
*/
void apaga_veiculos(){
    int i;
    HashNode current, temp;

    for (i = 0; i < HASH_TABLE_SIZE; i++) {
        current = hash_table[i];
        while (current != NULL) {
            temp = current -> next;
            free(current->veiculo.local);
            free(current);
            current = temp;
        }
    }
}
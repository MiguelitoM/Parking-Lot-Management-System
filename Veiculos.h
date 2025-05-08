/**
 * Ficheiro com algumas constantes e com o protótipo das funções do Veiculos.c.
 * @file Veiculos.h
 * @author ist1109886
*/

#ifndef Veiculos

#include "Datas.h"
#define TAMANHO_MATRICULA 9
#define HASH_TABLE_SIZE 5000

typedef struct {
    char *nome;
    Data data_e;
} Entrada;

typedef struct {
    char *nome;
    Data data_e;
    Data data_s;
} Registo;

typedef struct node_R{
    Registo registo;
    struct node_R *next;
} * link_R;

typedef struct {
    char matricula[TAMANHO_MATRICULA];
    Entrada *local;
    link_R historico;
} Veiculo;


typedef struct hash_node {
    Veiculo veiculo;
    struct hash_node *next;
} * HashNode;


void push_V(Veiculo veiculo);
int matricula_check(char matricula[]);
HashNode procura_v(char matricula[]);
link_R push_RV(Registo registo, link_R head);
void lista_R(link_R head, Entrada *local);
link_R pop_RV(char nome[], link_R head);
void apaga_historico(char nome[]);
void apaga_veiculos();
void print_s(char matricula[], Registo registo, float faturacao);
Registo init_R(Data data_e, Data data_s, char *nome);

#endif
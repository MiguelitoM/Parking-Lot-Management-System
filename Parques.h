/**
 * Ficheiro com algumas constantes e com o protótipo das funções do Parques.c.
 * @file Parques.h
 * @author ist1109886
*/

#ifndef PARQUES
#define PARQUES

#define MAX_PARQUES 20
#define TAMANHO_MATRICULA 9
#define FALSE 0
#define TRUE 1
#define BUFFER 8192
#include "Datas.h"

typedef struct {
    char matricula[TAMANHO_MATRICULA];
    float faturacao;
    Data data_s;
} Registo_P;

typedef struct node_RP{
    Registo_P registo_p;
    struct node_RP *next;
} * link_RP;

typedef struct {
    SoData data;
    float faturacao;
    link_RP head_RP;
    link_RP tail_RP;
} Dia;

typedef struct node_D{
    Dia dia;
    struct node_D *next;
} * link_D;

typedef struct {
    char *nome;
    int capacidade;
    float valorX;
    float valorY;
    float valorZ;
    int N_veiculos;
    link_D head_D;
    link_D tail_D;
}   Parque;


typedef struct node_P{
    Parque parque;
    struct node_P *next;
} * link_P;

void push_P(Parque parque);
link_P procura_p(char nome[]);
void lista_p();
void push_RP(Registo_P registo, Dia *dia);
void push_D(Dia dia, Parque *parque);
link_D procura_d(Data data, link_D head);
void lista_f(link_D head);
void lista_f_data(link_RP head);
void pop_P(char nome[]);
link_RP limpa_RP_aux(link_RP link);
void limpa_RP(Dia *dia);
void limpa_d(link_D link);
link_D limpa_d_aux(link_D link);
void vetor_p_ord(char parques[][BUFFER], int N);
void bubble_sort(char parques[][BUFFER], int N);
Parque init_P(char nome[], int capacidade, float valorX,
float valorY, float valorZ);
link_D init_D(Data data, float faturacao, link_P linkP);
Registo_P init_RP(Data data_s, char matricula[], float faturacao);
float calcula_faturacao(link_P linkP);

#endif
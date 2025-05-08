/**
 * Ficheiro com algumas constantes e com o protótipo das funções do Projeto.c.
 * @file Projeto.h
 * @author ist1109886
*/

#ifndef PROJETO
#define PROJETO

#include "Datas.h"

#define NO_ARGS 0
#define ARGS 1
#define FALSE 0
#define TRUE 1
#define BUFFER 8192
#define TAMANHO_MATRICULA 9


void input(int *N_Parques, Data *last_data);
void le_p(int *N_Parques);
void executa_p(char nome[], int capacidade, float  valorX,
float  valorY, float  valorZ, int *N_Parques);
void lista_p();
void le_e(Data *last_data);
void executa_e(char nome[], char matricula[], Data data, Data *last_data);
void le_s(Data *last_data);
void executa_s(char nome[], char matricula[], Data data, Data *last_data);
void le_v();
void executa_v(char matricula[]);
void le_f(Data *last_data);
void executa_f_1(char nome[]);
void executa_f_2(char nome[], Data data, Data *last_data);
void le_r(int *N_Parques);
void executa_r(char nome[], int *N_Parques);
void apaga_memoria(int N_Parques);
int e_and_s_check(char nome[], char matricula[], link_P linkP, 
HashNode linkV, Data data, Data *last_data, char comando);
void le_t();
void executa_t(char nome[]);

#endif
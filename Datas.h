/**
 * Ficheiro com algumas constantes e com o protótipo das funções do Datas.c.
 * @file Datas.h
 * @author ist1109886
*/

#ifndef Datas
#define Datas

#define DIAS_ANO 365
#define MINS_DIA 1440
#define MINS_HORA 60
#define PERIODO 15
#define PERIODO_HORA 4

typedef struct{
    int ano;
    int mes;
    int dia;
    int hora;
    int min;
} Data;


typedef struct{
    int ano;
    int mes;
    int dia;
} SoData;

SoData le_sodata();
Data le_data();
int cmp_data(Data data1, Data *data2);
int data_check(Data data);
float fatura(Data data_e, Data data_s, float valorX, float valorY, float valorZ);

#endif
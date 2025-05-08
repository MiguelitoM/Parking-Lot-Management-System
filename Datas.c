/**
 * Ficheiro relativo às datas.
 * @file Datas.c
 * @author ist1109886
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "Datas.h"

// vetor com os dias de todos os meses.
const int meses[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};


/**
 * Calcula a fatura com base na data de entrada e saída e os valores do parque.
 * @param data_e Data de entrada.
 * @param data_s Data de saída.
 * @param valorX valor cobrado a cada 15 minutos na primeira hora.
 * @param valorY valor cobrado a cada 15 minutos depois da primeira hora.
 * @param valorZ valor máximo diário (24h).
 * @return fatura.
*/
float fatura(Data data_e, Data data_s, float valorX, float valorY, float valorZ){
    float fatura = 0;
    int i;
    int diff_mins = 0;

    // Calcula a diferença de minutos.
    diff_mins += (data_s.ano -data_e.ano)*DIAS_ANO*MINS_DIA;
    for (i = data_e.mes; i < data_s.mes; i++){
            diff_mins += meses[i-1]*MINS_DIA;
    }
    diff_mins += (data_s.dia - data_e.dia)*MINS_DIA;
    diff_mins += (data_s.hora - data_e.hora)*MINS_HORA;
    diff_mins += (data_s.min - data_e.min);

    // Calcula a fatura com base na diferença de minutos.
    if (diff_mins > MINS_DIA){
        fatura += diff_mins/MINS_DIA*valorZ;
        diff_mins = diff_mins % MINS_DIA;
    }
    if (diff_mins > MINS_HORA){
        if ((PERIODO_HORA*valorX + ((diff_mins-MINS_HORA)/PERIODO + 
        ((diff_mins-MINS_HORA) % PERIODO != 0)) * valorY) >= valorZ){
            fatura += valorZ;
        }
        else{
            fatura += PERIODO_HORA*valorX + ((diff_mins-MINS_HORA)/PERIODO + 
            ((diff_mins-MINS_HORA) % PERIODO != 0)) * valorY;
        }  
    } 
    else if(diff_mins <= MINS_HORA){
        fatura += (diff_mins/PERIODO + (diff_mins % PERIODO != 0)) * valorX;
    }

    return fatura;
}


/**
 * Confirma se uma dada data é válida.
 * @param data data.
 * @return Verdadeiro ou Falso (0 ou 1).
*/
int data_check(Data data){

    if (data.mes <= 0 || data.mes > 12){
        return 0;
    }
    if (data.dia > meses[data.mes-1]){
        return 0;
    }
    if (data.hora >= 24){
        return 0;
    }
    if (data.min >= 60){
        return 0;
    }
    return 1;
}


/**
 * Compara duas datas para saber qual é maior.
 * @param data1 data1.
 * @param data2 data2.
 * @return 1 caso data1>data2. -1 caso data1<data2.
*/
int cmp_data(Data data1, Data *data2){
    if (data1.ano > data2->ano)
        return 1;

    else if (data1.ano < data2->ano)
        return -1;

    else if (data1.mes > data2->mes)
        return 1;

    else if (data1.mes < data2->mes)
        return -1;

    else if (data1.dia > data2->dia)
        return 1;

    else if (data1.dia < data2->dia)
        return -1;

    else if (data1.hora > data2->hora)
        return 1;

    else if (data1.hora < data2->hora)
        return -1;

    else if (data1.min > data2->min)
        return 1;

    else if (data1.min < data2->min)
        return -1;
        
    return 0;
}


/**
 * Lê uma data do input
 * @return data lida.
*/
Data le_data(){
    Data data;
    scanf("%d-%d-%d", &data.dia, &data.mes, &data.ano);
    scanf("%d:%d", &data.hora, &data.min);
    
    return data;
}


/**
 * Lê uma data sem as horas.
 * @return data lida.
*/
SoData le_sodata(){
    SoData data;
    scanf("%d-%d-%d", &data.dia, &data.mes, &data.ano);
    
    return data;
}
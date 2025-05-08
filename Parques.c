/**
 * Ficheiro relativo aos parques.
 * @file Parques.c
 * @author ist1109886
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "Parques.h"

// Cabeça e cauda da lista de parques.
static link_P head_P = NULL;
static link_P tail_P = NULL;


/**
 * Bubble sort usado para ordenar os parques por ordem alfabética.
 * @param parques vector de nomes dos parques ordenados.
 * @param N número de parques.
*/
void bubble_sort(char parques[][BUFFER], int N){
    int changed = TRUE, i;
    char temp[BUFFER];

    while(changed){
        changed = FALSE;
        for(i = 0; i < N - 1; i++){
            if (strcmp(parques[i], parques[i + 1]) > 0){
                changed = TRUE;
                strcpy(temp, parques[i]);
                strcpy(parques[i], parques[i + 1]);
                strcpy(parques[i + 1], temp);
            }
        }
    }
}


/**
 * Inicializa as variáveis de um novo parque.
 * @param nome nome do parque.
 * @param capacidade capacidade do parque.
 * @param valorX valor cobrado a cada 15 minutos na primeira hora.
 * @param valorY valor cobrado a cada 15 minutos depois da primeira hora.
 * @param valorZ valor máximo diário (24h).
 * @return o parque inicializado.
*/
Parque init_P(char nome[], int capacidade, float valorX, float valorY, float valorZ){
    Parque new_parque;

    // Aloca a memória necessária para o nome do parque e atribui todos 
    // os valores corretos do parque (ou inicializa variáveis).
    new_parque.nome = (char *)malloc(sizeof(char)*(strlen(nome)+1));
    strcpy(new_parque.nome, nome);
    new_parque.capacidade = capacidade;
    new_parque.valorX = valorX;
    new_parque.valorY = valorY;
    new_parque.valorZ = valorZ;
    new_parque.N_veiculos = 0;
    new_parque.head_D = NULL;
    new_parque.tail_D = NULL;

    return new_parque;
}


/**
 * Adiciona um parque à lista de parques.
 * @param parque parque a adicionar.
*/
void push_P(Parque parque){
    link_P new;

    // Aloca a memória necessária e atribui os valores para new.
    new = (link_P) malloc(sizeof(struct node_P));
    new -> parque = parque;
    new -> next = NULL;

    // Insere o elemento na lista.
    if (head_P == NULL){
        head_P = new;
    }
    if (tail_P != NULL){
        tail_P -> next = new;
    }
    tail_P = new;
}


/**
 * Apaga um parque da lista.
 * @param nome nome do parque.
*/
void pop_P(char nome[]){
    link_P current, previous = NULL;

    // Percorre a lista de parques até encontrar o parque a apagar e apaga-o
    for (current = head_P; current != NULL; previous = current,
    current = current -> next){
        if (!strcmp(current->parque.nome, nome)){
            if (current == head_P){
                head_P = current->next;
            }
            if (current == tail_P){
                tail_P = previous;
            }
            if (previous != NULL){
                previous->next = current->next;
            }
            // Liberta a memória.
            free(current->parque.nome);
            limpa_d(current->parque.head_D);
            free(current);
            break;
        }
    }
}


/**
 * Lista os parques existentes no sistema.
*/
void lista_p(){
    link_P x;

    for(x = head_P; x != NULL; x = x->next){
        printf("%s %d %d\n", x->parque.nome, x->parque.capacidade,
        x->parque.capacidade - x->parque.N_veiculos);
    }
}


/**
 * Guarda todos os nomes dos parques num vetor e depois ordena-o.
 * @param parques onde ficam guardados os nomes ordenados.
 * @param N número de parques.
*/
void vetor_p_ord(char parques[][BUFFER], int N){
    link_P x;
    int i = 0;

    for(x = head_P; x != NULL; x = x->next, i++){
        strcpy(parques[i], x->parque.nome);
    }
    bubble_sort(parques, N);
}


/**
 * Procura um parque na lista.
 * @param nome nome do parques.
 * @return ponteiro para o parque encontrado (NULL caso não encontre).
*/
link_P procura_p(char nome[]){
    link_P link_p;

    for(link_p = head_P; link_p != NULL; link_p = link_p->next){
        if (! strcmp (link_p->parque.nome, nome)){
            return link_p;
        }
    }
    return NULL;
}


/**
 * Inicializa um registo de parques com as variáveis que recebe
 * @param data_s data de saída.
 * @param matricula matrícula do veículo.
 * @param faturacao faturacao do parque com aquela saída.
 * @return registo inicializado.
*/
Registo_P init_RP(Data data_s, char matricula[], float faturacao){
    Registo_P registo;

    strcpy(registo.matricula, matricula);
    registo.data_s = data_s;
    registo.faturacao = faturacao;

    return registo;
}


/**
 * Adiciona um registo de parques.
 * @param registo registo a inserir.
 * @param dia usado para obter a cabeça e a cauda da lista.
*/
void push_RP(Registo_P registo, Dia *dia){
    link_RP new;

    // Aloca a memória necessária para new e atribui os valores para new.
    new = (link_RP) malloc(sizeof(struct node_RP));
    new -> registo_p = registo;
    new -> next = NULL;

    // Insere o elemento na lista.
    if (dia->head_RP == NULL){
        dia->head_RP = new;
    }
    if (dia->tail_RP != NULL){
        dia->tail_RP -> next = new;
    }
    dia->tail_RP = new;

}


/**
 * Função auxiliar do limpa_RP. Limpa um registo.
 * @param link ponteiro para o registo. 
 * @return ponteiro para o link seguinte.
*/
link_RP limpa_RP_aux(link_RP link){
    link_RP next;
    if (link == NULL){
        return NULL;
    }
    next = link->next;
    free(link);
    return next;
}


/**
 * Limpa todo o registo de um dia.
 * @param dia ponteiro usado para obter a cabeça e a cauda.
*/
void limpa_RP(Dia *dia){
    link_RP link = dia->head_RP;

    while (link != NULL){
        link = limpa_RP_aux(link);
    }

}


/**
 * Inicializa um dia com as variáveis recebidas.
 * @param data data.
 * @param faturacao faturacao desse dia.
 * @param linkP ponteiro para o parque.
 * @return ponteiro para o dia dentro da lista de dias.
*/
link_D init_D(Data data, float faturacao, link_P linkP){
    Dia dia;

    dia.data.ano = data.ano;
    dia.data.mes = data.mes;
    dia.data.dia = data.dia;
    dia.faturacao = faturacao;
    dia.head_RP = NULL;
    dia.tail_RP = NULL;
    push_D(dia, &linkP->parque);

    return procura_d(data, linkP->parque.head_D);
}


/**
 * Insere um dia na lista de dias de um parque.
 * @param dia dia.
 * @param parque ponteiro para o parque.
*/
void push_D(Dia dia, Parque *parque){
    link_D new;

    // Aloca a memória necessária e atribui os valores para new.
    new = (link_D) malloc(sizeof(struct node_D));
    new -> dia = dia;
    new -> next = NULL;

    // Insere o elemento na lista.
    if (parque->head_D == NULL){
        parque->head_D = new;
    }
    if (parque->tail_D != NULL){
        parque->tail_D -> next = new;
    }
    parque->tail_D = new;
}


/**
 * Procura um Dia na lista.
 * @param data dia a procurar.
 * @param head cabeça da lista.
 * @return cabeça da lista possivelmente alterada.
*/
link_D procura_d(Data data, link_D head){
    link_D x;

    for (x = head; x != NULL; x = x->next){
        if (x->dia.data.ano == data.ano && x->dia.data.mes == data.mes 
        && x->dia.data.dia == data.dia){
            return x;
        }
    }
    return NULL;
}


/**
 * Limpa um dia da lista.
 * @param link ponteiro para o dia.
*/
void limpa_d(link_D link){
    while (link != NULL){
        link = limpa_d_aux(link);
    }
}


/**
 * Limpa um registo de um dia.
 * @param link ponteiro para o dia.
 * @return o ponteiro para o elemento seguinte. 
*/
link_D limpa_d_aux(link_D link){
    link_D next;
    if (link == NULL){
        return NULL;
    }

    next = link->next;
    limpa_RP(&link->dia);
    free(link);
    return next;
}


/**
 * Lista a faturação de um parque
 * @param head cabeça da lista dos dias.
*/
void lista_f(link_D head){
    link_D x;

    for (x = head; x != NULL; x = x->next){
        printf("%02d-%02d-%04d %.2f\n", x->dia.data.dia, x->dia.data.mes, 
        x->dia.data.ano, x->dia.faturacao);
    }
}


/**
 * Lista a faturação de um dia.
 * @param head cabeça da lista do registo dos parques.
*/
void lista_f_data(link_RP head){
    link_RP x;
    Registo_P registo;

    for (x = head; x != NULL; x = x->next){
        registo = x->registo_p;
        printf("%s %02d:%02d %.2f\n", registo.matricula, 
        registo.data_s.hora, registo.data_s.min, registo.faturacao);
    }
}


/**
 * Calcula a faturação total de um dado parque.
 * @param linkP ponteiro para o parque.
 * @return faturação total desse parque.
*/
float calcula_faturacao(link_P linkP){
    link_D x;
    float soma = 0;

    for (x = linkP->parque.head_D; x != NULL; x = x->next){
        soma += x->dia.faturacao;
    }

    return soma;
}
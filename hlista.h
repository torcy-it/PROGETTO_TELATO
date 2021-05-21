#ifndef HLISTA_H
#define HLISTA_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define FIELDSIZE 25

typedef struct lista
{  
    char targaID [FIELDSIZE];
    char password [FIELDSIZE];
    
    char name_user [FIELDSIZE];
    char surname_user [FIELDSIZE];
    
    int peso_veicolo;
    int carico_veivolo;

    struct lista * next;

}lista_user;


lista_user * preleva_dati_da_file( FILE * ); //creo una lista degli user tramite la lettura del file

bool check_nodo_ID ( lista_user *,const char * ); 

bool check_nodo_KEY ( lista_user * , const char *, const char *);

lista_user * add_node ( lista_user *, lista_user * );

void deallocateList ( lista_user *);

void print_lista_user ( lista_user * );

#endif
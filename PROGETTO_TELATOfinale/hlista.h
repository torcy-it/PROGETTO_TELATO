#ifndef HLISTA_H
#define HLISTA_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define FIELDSIZE 25



typedef struct user
{
    char targaID [FIELDSIZE];
    char password [FIELDSIZE];
    
    char name_user [FIELDSIZE];
    char surname_user [FIELDSIZE];
    
    int peso_veicolo;
    int carico_veivolo;

}user_info;



typedef struct merce
{
    char alimento [FIELDSIZE];

    int colle;
    int peso;

}merce_info;



typedef struct list
{  
    merce_info info_merce; // true

    user_info info_user; // false

    struct list * next;

}lista;

void load_user (  lista *  , lista *  );

lista * preleva_merce ( FILE * );

lista * preleva_user ( FILE * );

lista * preleva_dati_da_file( FILE * , bool ); //creo una lista degli user tramite la lettura del file

bool check_nodo_ID ( lista *, const char * , bool ); 

bool check_nodo_KEY ( lista * , const char *, const char * );

lista * add_node ( lista *, lista * );

void aggiorna_user_su_file ( lista *, FILE * );

void print_lista_merce ( lista *  );

bool check_quantita_merce ( lista * , lista *  );

lista * crea_nodo_merce ( lista *  , lista *  , lista * , lista *  );

int operazione_nodo_merce ( lista *  , lista * );

lista *  mod_nodo_del (  lista *  , lista *  );

lista * mod_nodo_add ( lista *  , lista* , bool  );

void deallocate_list ( lista *);

int somma_elementi_lista ( lista * );

#endif
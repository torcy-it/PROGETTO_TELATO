#ifndef HLISTA_H
#define HLISTA_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

//variabile globale per dimensione array
#define FIELDSIZE 25

// lista singolarmente linkata 
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

//creazione della lista tramite file utenti.txt
lista_user * preleva_dati_da_file( FILE * ); 

//scorrimento della lista per trovare ID user
bool check_nodo_ID ( lista_user *,const char * ); 

//scorrimento della per trovare KEY e ID user
bool check_nodo_KEY ( lista_user * , const char *, const char *);

//aggiungimento nodo in coda alla lista
lista_user * add_node ( lista_user *, lista_user * );

//deallocamento della lista utenti con eventuale aggiornamento sul file utenti.txt
void aggiona_dati_su_file ( lista_user *  , FILE *  );

//stampa della lista
void print_lista_user ( lista_user * );

#endif

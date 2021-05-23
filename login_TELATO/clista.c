
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "hlista.h"


lista_user * preleva_dati_da_file( FILE * fp )
{

    if(!fp) //controllo apertura file
    {   
        printf("\nErrore scrittura ospite FILE appuntamenti\n"); 
        return NULL; // return testa NULL
    }

    lista_user * nodo_t = (lista_user *) malloc(sizeof(lista_user)); //mallocamento nodo della lista
    
    
    //controllo variabili in entrata == 6
    //caso base                       TARGA                PASSWORD               NOME              COGNOME               PESO                   CARICO
    if(fscanf(fp,"%s %s %s %s %d %d", nodo_t->targaID, nodo_t->password , nodo_t->name_user  , nodo_t->surname_user, &nodo_t->peso_veicolo, &nodo_t->carico_veivolo) != 6) 
    {
        fclose( fp ); // chiusura file
        
        free ( nodo_t ); //free nodo non più utilizzabile

        return NULL; // return coda della lista a NULL, chiusura stack
    }
    
    //inserimento nodo_t nello stack
    // caso ricorsivo
    nodo_t->next = preleva_dati_da_file( fp );
    
    //return nodo_t nello stack
    return nodo_t;

}

bool check_nodo_ID ( lista_user * head , const char * targaID)
{
    if( !head )         //caso base head e' NULL, nessuna corrispondenza trovata, return false trovato nessuna corrispondenza
        return false;
    
    if(!strcmp ( head->targaID, targaID )) //trovato corrispondenza return true
        return true; 

    check_nodo_ID (head->next , targaID); //scorrimento lista
}


bool check_nodo_KEY ( lista_user * head , const char * targaID, const char * password )
{
    if( !head )      //caso base head e' NULL, nessuna corrispondenza trovata, return false trovato nessuna corrispondenza
        return false;
    
    if( !strcmp ( head->targaID, targaID ) && !strcmp ( head->password, password) )//trovato corrispondenza return true
        return true; 

    check_nodo_KEY (head->next , targaID, password); //scorrimento lista
}


lista_user * add_node ( lista_user * head, lista_user * info_new_user )
{
    if( !head )      //caso base head e' NULL aggiungo nodo 
        return info_new_user;

    head->next = add_node ( head->next , info_new_user ); // scorrimento lista

    return head; // return collegamento head
}


void aggiona_dati_su_file ( lista_user * head , FILE * fp )
{

    if(!fp) //eseguo un controllo per vedere se il file e' stato aperto correttamente
    {   
        printf("\nErrore scrittura ospite FILE appuntamenti\n"); 
        return ;
    }

    if ( !head ) 
    {
        fclose ( fp );
        return; //checks if head is null 
    }

    lista_user * next = head->next; //faccio una copia del next cosi da non perdere il riferimento dopo aver deallocato
    
    fprintf(fp,"\n%s %s %s %s %d %d", head->targaID, head->password , head->name_user  , head->surname_user, head->peso_veicolo, head->carico_veivolo);

    free( head );

    aggiona_dati_su_file( next , fp );   
}

void print_lista_user ( lista_user * head )
{

    if( !head ) return;

    printf("\n|%s| |%s| |%s| |%s| %d %d", head->targaID, head->password , head->name_user  , head->surname_user, head->peso_veicolo, head->carico_veivolo);

    print_lista_user ( head->next);
}

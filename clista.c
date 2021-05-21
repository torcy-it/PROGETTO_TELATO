
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "hlista.h"

lista_user * preleva_dati_da_file( FILE * fp )
{

    if(!fp) //eseguo un controllo per vedere se il file e' stato aperto correttamente
    {   
        printf("\nErrore scrittura ospite FILE appuntamenti\n"); 
        return NULL;
    }

    lista_user * nodo_t = (lista_user *) malloc(sizeof(lista_user)); //alloco memoria per il nodo

    //caso base                       TARGA                PASSWORD               NOME              COGNOME               PESO                   CARICO
    if(fscanf(fp,"%s %s %s %s %d %d", nodo_t->targaID, nodo_t->password , nodo_t->name_user  , nodo_t->surname_user, &nodo_t->peso_veicolo, &nodo_t->carico_veivolo) != 6) 
    {
        fclose( fp ); // chiudo il file
        
        free ( nodo_t ); //libero il nodo allocato in precendenza 

        return NULL; // e ritorno null quindi lo stack si chiudera' dando come ultimo elemento un nodo a NULL
    }
    
    // caso ricorsivo
    nodo_t->next = preleva_dati_da_file(fp);

    return nodo_t;

}

bool check_nodo_ID ( lista_user * head , const char * targaID)
{
    if( !head )         //caso base dove head e' NULL e ritorno false perche' non ho trovato nessuna corrispondenza
        return false;
    
    if(!strcmp ( head->targaID, targaID )) // ho trovato una corrispondenza ritorno true
        return true; 

    check_nodo_ID (head->next , targaID); // caso ricorsivo dove scorro head
}


bool check_nodo_KEY ( lista_user * head , const char * targaID, const char * password )
{
    if( !head )      //caso base dove head e' NULL e ritorno false perche' non ho trovato nessuna corrispondenza
        return false;
    
    if( !strcmp ( head->targaID, targaID ) && !strcmp ( head->password, password) ) // ho trovato una corrispondenza ritorno true
        return true; 

    check_nodo_KEY (head->next , targaID, password); //caso ricorsivo dove scorro head
}


lista_user * add_node ( lista_user * head, lista_user * info_new_user )
{
    if( !head )
        return info_new_user;

    head->next = add_node ( head->next , info_new_user );

    return head;
}


void deallocate_list ( lista_user * head )
{
   if ( !head ) return; //checks if head is null 

   lista_user * next = head->next; //faccio una copia del next cosi da non perdere il riferimento dopo aver deallocato

   free( head );

   deallocate_list( next );   
}

void print_lista_user ( lista_user * head )
{

    if( !head ) return;

    printf("\n%s %s %s %s %d %d", head->targaID, head->password , head->name_user  , head->surname_user, head->peso_veicolo, head->carico_veivolo);

    print_lista_user ( head->next);
}
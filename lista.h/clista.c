
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "hlista.h"
#include "hour_function.h"

// PRELEVA MERCE
// Accetta in ingresso un puntatore aperto sul file stock_merce.txt in modalità "r"
// che usa per leggere le righe del file. Ogni riga comprende 3 stringhe e corrisponde a un prodotto.
lista * preleva_merce ( FILE * fp )
{
    // Alloca memoria per il nodo
    lista * nodo_t = (lista *) malloc(sizeof(lista));o

    // Se non legge 3 stringhe (è arrivato alla fine del file)
    if ( fscanf(fp,"%s %d %d",nodo_t->info_merce.alimento, &nodo_t->info_merce.colle, &nodo_t->info_merce.peso ) != 3 ) 
    {
        // Restituisci NULL
        return NULL;
    }
    
    // Restituisci il nodo 
    return nodo_t;    
}

// PRELEVA USER
// Accetta in ingresso un puntatore aperto sul file driver_registrati.txt in modalità "r"
// che usa per leggere le righe del file. Ogni riga comprende 4 stringhe e 2 interi e corrisponde a un driver registrato
lista * preleva_user ( FILE * fp )
{
    // Alloca memoria per il nodo
    lista * nodo_t = (lista *) malloc(sizeof(lista)); //alloco memoria per il nodo

    // Se non legge 4 stringhe e 2 interi (è arrivato alla fine del file)
    if ( fscanf(fp,"%s %s %s %s %d %d", nodo_t->info_user.targaID , nodo_t->info_user.password , nodo_t->info_user.name_user  , nodo_t->info_user.surname_user,
                 &nodo_t->info_user.peso_veicolo, &nodo_t->info_user.carico_veivolo) != 6 )
    {
        // Restituisci NULL
        return NULL;
    }

    // Restituisci il nodo
    return nodo_t;
}

// PRELEVA DATI DA FILE
// Accetta in ingresso un puntatore aperto su un file, che può essere o driver_registrati.txt
// o stock_merce.txt. Da quale dei due file prelevare i dati è determinato dal 2° parametro: scelta.
// Se scelta è false preleva un utente da driver_registrati.txt, mentre se è true preleva un prodotto da stock_merce.txt
lista * preleva_dati_da_file( FILE * fp , bool scelta )
{

    // Se il file non è stato aperto correttamente (controllo errore)
    if(!fp)
    {   
        // Stampa un messaggio che informi l'utente
        printf("\nErrore scrittura ospite FILE appuntamenti\n"); 
        // Restituisci NULL
        return NULL;
    }

    // Dichiara un nodo
    lista * nodo_t;

    // Se scelta è false
    if( !scelta )
    {
        // Preleva un driver
        nodo_t = preleva_user ( fp );
    }
    // Altrimenti
    else 
    {
        // Preleva un prodotto
        nodo_t = preleva_merce ( fp );
    }


    // Caso base 
    if( !nodo_t ) 
    {
        // Chiudi il file
        fclose( fp );
        
        // Libera il nodo allocato in precedenza
        free ( nodo_t ); 

        // Restituisci NULL in modo che lo stack si chiuda dando come ultimo elemento un nodo a NULL
        return NULL;
    }
    
    // Passo ricorsivo
    nodo_t->next = preleva_dati_da_file(fp, scelta);

    // Restituisci il nodo
    return nodo_t;

}

// LOAD USER
void load_user (  lista * head , lista * utente )
{
    if ( !head )
    {
        utente->info_user.carico_veivolo = -84;

        return ;
    }
    

    if( ! strcmp( head->info_user.targaID, utente->info_user.targaID ) && ! strcmp( head->info_user.password , utente->info_user.password ) )
    {
        strcpy ( utente->info_user.name_user ,head->info_user.name_user );
        strcpy ( utente->info_user.surname_user, head->info_user.surname_user);

        utente->info_user.peso_veicolo = head->info_user.peso_veicolo;
        utente->info_user.carico_veivolo = 0;

        system("pause");
        return;
    }

    load_user ( head->next, utente );

}


bool check_nodo_ID ( lista * head , const char * id_tofind , bool scelta )
{
    if( !head )         //caso base dove head e' NULL e ritorno false perche' non ho trovato nessuna corrispondenza
    {
        return false;
    }

    if( !scelta )
    {
        if(!strcmp ( head->info_user.targaID, id_tofind  )) // ho trovato una corrispondenza ritorno true
            return true;   
                
    }
    else
    {
        if(!strcmp ( head->info_merce.alimento, id_tofind ) ) // ho trovato una corrispondenza ritorno true
            return true;          
    }

    check_nodo_ID (head->next , id_tofind , scelta ); // caso ricorsivo dove scorro head
}


bool check_nodo_KEY ( lista * head , const char * targaID, const char * password )
{
    if( !head )      //caso base dove head e' NULL e ritorno false perche' non ho trovato nessuna corrispondenza
        return false;
    
    if( !strcmp ( head->info_user.targaID, targaID ) && !strcmp ( head->info_user.password, password) ) // ho trovato una corrispondenza ritorno true
        return true; 

    check_nodo_KEY (head->next , targaID, password); //caso ricorsivo dove scorro head
}


lista * add_node ( lista * head, lista * info_new_user )
{
    if( !head )
        return info_new_user;

    head->next = add_node ( head->next , info_new_user );

    return head;
}


void aggiorna_user_su_file ( lista * head , FILE * fp )
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

    fprintf(fp,"\n%s %s %s %s %d %d", head->info_user.targaID, head->info_user.password , head->info_user.name_user  , 
                                    head->info_user.surname_user, head->info_user.peso_veicolo, head->info_user.carico_veivolo);



    aggiorna_user_su_file(head-> next , fp );   
}



void print_lista_merce ( lista * head )
{

    if( !head ) return;

    printf("\n|%32s| %d %d", head->info_merce.alimento, head->info_merce.colle, head->info_merce.peso);

    print_lista_merce ( head->next);
}


lista * mod_nodo_add ( lista * head , lista* add, bool found )
{
    if(  head && !strcmp ( head->info_merce.alimento,add->info_merce.alimento ) && head )
    {
        head->info_merce.colle  += add->info_merce.colle;
        found = true;
    }
    
    if( !head )
    {
        if( found )
        {
            return NULL;    
        }
        else
        {
            return add;
        }
        
    }


    head->next = mod_nodo_add ( head->next , add , found);

    return head;
}

lista *  mod_nodo_del (  lista * head , lista * del )
{

    if( !head )
    {
        return NULL;
    }
    else
    {
        head->next = mod_nodo_del (head->next , del ) ;


        if( !strcmp ( head->info_merce.alimento, del->info_merce.alimento ) )
        {

            if ( (del->info_merce.colle - head->info_merce.colle) == 0 )
            {
                lista * tmp;
                tmp = head->next;

                // Cancello il nodo
                free( head );

                // Restituisco il puntatore a nodo temporaneo
                return tmp;

            }
            else if( head->info_merce.colle < del->info_merce.colle)
            {
                if ( (   del->info_merce.colle - head->info_merce.colle) < 0 )
                {
                    printf("\n\n\t\tNon e' possibile fare questa operazione perche ( head->info_merce.colle - del->info_merce.colle ) < 0\n\n");
                }
                else
                {
                    head->info_merce.colle =  del->info_merce.colle - head->info_merce.colle;
        
                }
                
            }
            else
            {
                if ( (  head->info_merce.colle - del->info_merce.colle  ) < 0 )
                {
                    printf("\n\n\t\tNon e' possibile fare questa operazione perche ( del->info_merce.colle - head->info_merce.colle ) < 0\n\n");
                }
                else
                {
                    head->info_merce.colle =  head->info_merce.colle - del->info_merce.colle;
                }
                
            }

        }
    }
    
    return head;
}

lista * crea_nodo_merce ( lista * head )
{
    lista nodo;
    lista * nodo_toLink = (lista * )malloc ( sizeof ( lista ));

    do
    {
        printf("\n\n\tInserisci alimento presente in lista merce\n>");
        scanf("%s",nodo.info_merce.alimento);
        to_upper( nodo.info_merce.alimento);

    } while ( !check_nodo_ID ( head , nodo.info_merce.alimento, true )  || !strcmp (nodo.info_merce.alimento,"back" ));


    do
    {
        printf("\n\n\tInserisci la quantita desiderata \n>");
        nodo.info_merce.colle = insert_int ();

        if( nodo.info_merce.colle > 0 )
        {
            if ( check_quantita_merce ( head, &nodo ) )
            {
                break;
            }
        }

    }while ( 1 ); 

    strcpy (nodo_toLink->info_merce.alimento, nodo.info_merce.alimento);

    nodo_toLink->info_merce.colle = nodo.info_merce.colle;

    nodo_toLink->info_merce.peso = nodo.info_merce.peso;

    nodo_toLink->next = NULL;

    return nodo_toLink;
    
}

bool check_quantita_merce ( lista * head, lista * nodo_to_check )
{
    if( !head )         //caso base dove head e' NULL e ritorno false perche' non ho trovato nessuna corrispondenza
    {
        return false;
    }
   

    if(!strcmp ( head->info_merce.alimento, nodo_to_check->info_merce.alimento ) 
                && nodo_to_check->info_merce.colle > 0 && nodo_to_check->info_merce.colle <= head->info_merce.colle ) // ho trovato una corrispondenza ritorno true
    {
        nodo_to_check->info_merce.peso = head->info_merce.peso;
        return true;          
    }

    check_quantita_merce (head->next , nodo_to_check); // caso ricorsivo dove scorro head
}

void deallocate_list ( lista * head )
{
    if ( !head )
    {
        return;
    }
        
    deallocate_list(head->next); 

    free(head);
}

int somma_elementi_lista ( lista * testa )
{

    if ( testa != NULL )
        return ((testa->info_merce.peso * testa->info_merce.colle ) + somma_elementi_lista(testa->next));
    else
        return 0;

}


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "hlista.h"

#include <time.h>

lista * preleva_merce ( FILE * fp )
{
    lista * nodo_t = (lista *) malloc(sizeof(lista)); //alloco memoria per il nodo

    if ( fscanf(fp,"%s %d %d",nodo_t->info_merce.alimento, &nodo_t->info_merce.colle, &nodo_t->info_merce.peso ) != 3 ) 
    {
        return NULL;
    }

    return nodo_t;    
}

lista * preleva_user ( FILE * fp )
{
    lista * nodo_t = (lista *) malloc(sizeof(lista)); //alloco memoria per il nodo

    if ( fscanf(fp,"%s %s %s %s %d %d", nodo_t->info_user.targaID , nodo_t->info_user.password , nodo_t->info_user.name_user  , nodo_t->info_user.surname_user,
                 &nodo_t->info_user.peso_veicolo, &nodo_t->info_user.carico_veivolo) != 6 )
    {
        return NULL;
    }

    return nodo_t;
}

lista * preleva_dati_da_file( FILE * fp , bool scelta )
{

    if(!fp) //eseguo un controllo per vedere se il file e' stato aperto correttamente
    {   
        printf("\nErrore scrittura ospite FILE appuntamenti\n"); 
        return NULL;
    }

    lista * nodo_t;


    if( !scelta )
    {
        nodo_t = preleva_user ( fp );
    }
    else 
    {
        nodo_t = preleva_merce ( fp );
    }


    //caso base 
    if( !nodo_t ) 
    {
        fclose( fp ); // chiudo il file
        
        free ( nodo_t ); //libero il nodo allocato in precendenza 

        return NULL; // e ritorno null quindi lo stack si chiudera' dando come ultimo elemento un nodo a NULL
    }
    
    // caso ricorsivo
    nodo_t->next = preleva_dati_da_file(fp, scelta);

    return nodo_t;

}

bool check_nodo_ID ( lista * head , const char * stringa_to_find , bool scelta )
{
    if( !head )         //caso base dove head e' NULL e ritorno false perche' non ho trovato nessuna corrispondenza
    {
        return false;
    }

    if( !scelta )
    {
        if(!strcmp ( head->info_user.targaID, stringa_to_find )) // ho trovato una corrispondenza ritorno true
            return true;         
    }
    else
    {
        if(!strcmp ( head->info_merce.alimento, stringa_to_find ) ) // ho trovato una corrispondenza ritorno true
            return true;          
    }

    check_nodo_ID (head->next , stringa_to_find, scelta ); // caso ricorsivo dove scorro head
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

    lista * next = head->next; //faccio una copia del next cosi da non perdere il riferimento dopo aver deallocato
    
    fprintf(fp,"\n%s %s %s %s %d %d", head->info_user.targaID, head->info_user.password , head->info_user.name_user  , 
                                    head->info_user.surname_user, head->info_user.peso_veicolo, head->info_user.carico_veivolo);

    free( head );

    aggiorna_user_su_file( next , fp );   
}



void print_lista_merce ( lista * head )
{

    if( !head ) return;

    printf("\n|%32s| %d %d", head->info_merce.alimento, head->info_merce.colle, head->info_merce.peso);

    print_lista_merce ( head->next);
}


void aggiorna_merce_file ( lista * head )
{
    time_t t;
    lista * next = NULL;
    FILE * fp = fopen ("stock_merce.txt","w");

    if (!fp)
    {
        printf("\n\n\tERRORE nella scrittura file stock alimento\n");
        return;
    }

    int max_colle = 100;

    int max_peso = 20;

    srand((unsigned) time(&t));

    do
    {
        fprintf(fp,"%s %d %d", head->info_merce.alimento, rand() % max_colle, rand( )% max_peso);

        next = head->next;

        free( head );

        head = next;

    }while( !head );

    fclose(fp);
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

    } while ( !check_nodo_ID ( head , nodo.info_merce.alimento, true )  || !strcmp (nodo.info_merce.alimento,"back" ));


    do
    {
        printf("\n\n\tInserisci la quantita desiderata \n>");
        scanf("%d",&nodo.info_merce.colle);

    }while ( !check_quantita_merce ( head, &nodo ) || !strcmp (nodo.info_merce.alimento,"back" ) ); 

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
                && nodo_to_check->info_merce.colle >= 0 && nodo_to_check->info_merce.colle <= head->info_merce.colle ) // ho trovato una corrispondenza ritorno true
    {
        nodo_to_check->info_merce.peso = head->info_merce.peso;
        return true;          
    }

    check_quantita_merce (head->next , nodo_to_check); // caso ricorsivo dove scorro head
}

void deallocate_list ( lista * head )
{
    if( !head ) return ;

    lista * next = head->next;

    free( head );

    deallocate_list ( next );
}
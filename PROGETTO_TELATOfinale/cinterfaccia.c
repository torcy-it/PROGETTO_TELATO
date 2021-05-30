#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

#include "hlista.h"
#include "hutility_function.h"
#include "hgrafi.h"

#define FIELD_SIZE 25
#define INIT 4



void schermata_percorso ( int  );

lista * schermata_ordini ( lista *, lista * merce);

char * scelte_ordini ( int  );

void schermata_avvio ( );

char * scelte_avvio ( int  );


//          LOGIN SCELTE
char *scelte_avvio ( int scelta )
{
    if ( scelta == 0) return "log";
    else if ( scelta == 1 ) return "sign";
    else return "exit";

}


void schermata_avvio ( )
{
    int ch = 0;
    int scelta = 0;
    bool exit = false;
    
    lista * lista_merci = NULL;
    lista * utente  = NULL;
    lista * lista_user = preleva_dati_da_file ( fopen ("driver_registrati.txt","r"), false);
    

    do
    {

        system ("cls");

        stampa_intestazione_schermata ( 1 );
        
        if( ch == 75 ) scelta = scelta - 1;

        if( ch == 77 ) scelta = scelta + 1;

        if ( scelta < 0 ) scelta = 2;

        if ( scelta > 2 ) scelta = 0;


        for ( int i = 0; i < 3; i++ )
        {
            if ( i == scelta ) printf ("\t [ %s ] ", scelte_avvio( i ) );
            
            else printf("\t%s", scelte_avvio( i ));
        }
        printf("\n\n\n\n\t");
        
        ch = getch( );


        if( ( ch == '\r') )
        {
            if( scelta == 0 ) 
            {
                
                system("cls");

                utente = login ( lista_user );

                
                if( utente->info_user.carico_veivolo >= 0 )
                {
                    printf("\n\n\n\n\n\n\t\tCREDENZIALI CORRETTE. ACCESSO IN CORSO....\n\n\n");
                    sleep ( 2 );

                    lista_merci = schermata_ordini ( utente , lista_merci );
                }
                else
                {
                    printf("\n\n\n\n\n\n\t\tCREDENZIALI NON CORRETTE. ACCESSO NEGATO\n\n\n");
                    system("pause");
                }

            }
            
            if( scelta == 1 )
            {
                system("cls");

                lista_user = signin ( lista_user );

            }

            if( scelta == 2 )
            {
                exit = true;
            }
            else
            {
                utente  = NULL;
            }


            system ("cls"); 


        }


    }while ( !exit );  

    
    aggiorna_user_su_file ( lista_user, fopen("driver_registrati.txt","w"));

    deallocate_list ( lista_merci );
    deallocate_list ( lista_user );
    free ( utente );

}


char * merce_scelte ( int scelta )
{
    if ( scelta == 0) return "aggiungi";
    else if ( scelta == 1 ) return "rimuovi";
    else if (scelta == 2 ) return "conferma";
    else return "logout";

}

lista * schermata_ordini ( lista * utente , lista * lista_merce)
{   
    int ch = 0;
    int scelta = 0;
    bool exit = false;

    bool bool_continue = false;
    int choice = 't'; 
    
    if( !lista_merce ) lista_merce = preleva_dati_da_file ( fopen ("stock_merce.txt","r"), true);

    lista * lista_spesa = NULL;

    utente->info_user.carico_veivolo = utente->info_user.peso_veicolo;

    do
    {

        stampa_schermata_ordini ( 4 , lista_merce , lista_spesa, utente );

        if( ch == 75 ) scelta = scelta - 1;

        if( ch == 77 ) scelta = scelta + 1;

        if ( scelta < 0 ) scelta = 3;

        if ( scelta > 3 ) scelta = 0;


        for ( int i = 0; i < 4; i++ )
        {
            if ( i == scelta ) printf ("\t [ %s ] ", merce_scelte( i ) );
            
            else printf("%10s", merce_scelte( i ));
        }
        printf("\n\n\n\n\t");
        
        ch = getch( );


        if( ( ch == '\r') )
        {
            if( scelta == 0 ) 
            {
                if( lista_merce )
                {
                    lista * nodo_merce = crea_nodo_merce( lista_merce, lista_merce , lista_spesa , utente );

                    lista_spesa = mod_nodo_add ( lista_spesa, nodo_merce, false );

                    lista_merce = mod_nodo_del ( lista_merce , nodo_merce );
                    
                    if( lista_spesa )
                        utente->info_user.carico_veivolo =  (nodo_merce->info_merce.colle * nodo_merce->info_merce.peso) + utente->info_user.carico_veivolo;

                }
                else
                {
                    printf("\n\n\tImpossibile prelevare. Nessuna merce in stock\n");
                    system("pause");
                }

            }
            
            if( scelta == 1 )
            {
                if( lista_spesa )
                {
                    lista * nodo_merce = crea_nodo_merce(  lista_spesa, lista_merce , lista_spesa, utente  );

                    lista_merce = mod_nodo_add ( lista_merce, nodo_merce, false );

                    lista_spesa = mod_nodo_del ( lista_spesa , nodo_merce );

                    utente->info_user.carico_veivolo = operazione_nodo_merce ( nodo_merce, utente);  
                }
                else
                {
                    printf("\nImpossibile prelevare. Lista della spesa vuota\n\n");
                    system("pause");
                }

            }

            if( scelta == 2 )
            {

                //grafo
                if( !lista_spesa )
                {
                    printf("\tATTENZIONE : lista della spesa vuota\n");

                    printf("\tVuoi continuare lo stesso? y/n\n\t>");

                    choice = getch (); 

                    if ( choice == 'y') bool_continue = true;
                
                }
                
                if ( lista_spesa || bool_continue )
                {
                    //peso_totale = somma_elementi_lista ( lista_spesa ) + utente->info_user.peso_veicolo;

                    system("cls");

                    printf("\n\tPeso totale : %d\n\tConfermi ordine? y/n\n\t>",utente->info_user.carico_veivolo);

                    choice = getch (); 

                    if ( choice == 'y') 
                    {

                        system("cls");

                        printf("\n\tElaborazione ordine in corso...\n");
                        sleep( 2 );   
                        
                        printf("\tOrdine confermato\n\n\t");
                        system("pause");

                        schermata_percorso ( utente->info_user.carico_veivolo );

                        deallocate_list ( lista_spesa ); // non funziona  una volta entrato in interfaccia percorso 
                        //e aver concluso tale funzione ritornado qui la lista della spesa esiste ancora

                        lista_spesa = NULL;

                        utente->info_user.carico_veivolo = utente->info_user.peso_veicolo;
                    }

                }


            }

            if( scelta == 3 )
            {
                exit = true;

                system ("cls");

                printf("\n\n\n\n\n\n\t\tLOGOUT IN CORSO....\n\n\n");

                sleep ( 2 );
            }

            system ("cls");
        }
         
        system ("cls");

    }while ( !exit );  

    return lista_merce;

}


void schermata_percorso ( int peso_totale )
{
    system("cls");
    int source = 0, target = 0;
    
    grafo gr = NULL;       //grafo inizializzato a NULL

    int num_vertici = 0;

    gr  = (grafo  )malloc(sizeof( struct graph ));

    if(gr == NULL) 
    {
        printf("ERRORE: imp. allocare mem. del grafo\n");
        exit(1);
    }

    


    gr->adj = ( arco *)malloc( INIT * sizeof ( arco ));

    if(gr->adj == NULL)  
    {
        printf("ERRORE: imp. allocare mem. per la lista del grafo\n");
        exit (1);
    } 
    
    
    create_graph( gr, fopen("mappa_island.txt","r"), &num_vertici, 0);

    stampa_nome_schermata( 5 );
    
    stampa_graphic_grafo ( );

    gr->numero_vertici = num_vertici ;

    //gr != NULL ? stampa_grafo ( gr, 0 ) : printf("\n\n\tGrafo Vuoto\n")  ;  


    do
    {
        printf("\n\n\tInserisci la partenza\n\t>");
        source = insert_int ( );

    }while ( source < 0 && source > gr->numero_vertici );

    do
    {
        printf("\n\n\tInserisci la destinazione\n\t>");
        target = insert_int ( );

    } while ( target < 0 && target > gr->numero_vertici );
    
    dijkstra( gr, source, target, peso_totale );

    system("pause");
}



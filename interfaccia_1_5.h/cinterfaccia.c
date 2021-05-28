#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include "hlista.h"
#include "hour_function.h"
#include "hgrafi.h"
#define FIELD_SIZE 25
#define INIT 4

#include "hlista.h"
#include "hour_function.h"
#include "hgrafi.h"

void interfaccia_percorso ( int  );

lista * interfaccia_merce ( lista *, lista * merce);
char * merce_scelte ( int  );

void interfaccia_login ( );
char * login_scelte ( int  );



//Fabrizio se vuoi inserire la tua printf dell lista merci fallo 
// perchè non sono riuscito ad emularla
// per cambiare la printf vai su clista.c e cambi la funzione 
//print_merce che stampa la lista fino a quando non e' null
char *login_scelte ( int scelta )
{
    if ( scelta == 0) return "log";
    else if ( scelta == 1 ) return "sign";
    else return "exit";

}


void interfaccia_login ( )
{
    int ch = 0;
    int scelta = 0;
    bool exit = false;
    
    lista * lista_merci = NULL;
    lista * utente  = NULL;
    lista * lista_user = preleva_dati_da_file ( fopen ("utenti.txt","r"), false);

    do
    {
        

        system("cls");

        printf("\n\n\n");
        if( ch == 75 ) scelta = scelta - 1;

        if( ch == 77 ) scelta = scelta + 1;

        if ( scelta < 0 ) scelta = 2;

        if ( scelta > 2 ) scelta = 0;


        for ( int i = 0; i < 3; i++ )
        {
            if ( i == scelta ) printf ("\t [ %s ] ", login_scelte( i ) );
            
            else printf("\t%s ", login_scelte( i ));
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
                    lista_merci = interfaccia_merce ( utente , lista_merci );
                }
                else
                {
                    printf("\n\n\t\tLOGIN FAILED\n\n\n");
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

    
    aggiorna_user_su_file ( lista_user, fopen("utenti.txt","w"));

    deallocate_list ( lista_merci );
    deallocate_list ( lista_user );
    free ( utente );

}


char * merce_scelte ( int scelta )
{
    if ( scelta == 0) return "add";
    else if ( scelta == 1 ) return "remove";
    else if (scelta == 2 ) return "conferma";
    else return "exit";

}

lista * interfaccia_merce ( lista * utente , lista * lista_merce)
{   
    int ch = 0;
    int scelta = 0;
    bool exit = false;
    
    if( !lista_merce ) lista_merce = preleva_dati_da_file ( fopen ("stock_merce.txt","r"), true);

    lista * lista_spesa = NULL;

    int peso_totale = utente->info_user.carico_veivolo + utente->info_user.peso_veicolo;

    do
    {

        system("cls");

        printf("\nLista merce\n");

        if ( lista_merce ) print_lista_merce ( lista_merce );// GOTO riga 155

        printf("\n\t\tNULL\n\nLISTA SPESA\n");

        if ( lista_spesa )  print_lista_merce ( lista_spesa );

        printf("\n\t\tNULL\n\n");

        printf("\t\tBENVENUTO %s %s \n",utente->info_user.name_user, utente->info_user.surname_user);


        if( ch == 75 ) scelta = scelta - 1;

        if( ch == 77 ) scelta = scelta + 1;

        if ( scelta < 0 ) scelta = 3;

        if ( scelta > 3 ) scelta = 0;


        for ( int i = 0; i < 4; i++ )
        {
            if ( i == scelta ) printf ("\t [ %s ] ", merce_scelte( i ) );
            
            else printf("\t%s ", merce_scelte( i ));
        }
        printf("\n\n\t");
        
        ch = getch( );


        if( ( ch == '\r') )
        {
            if( scelta == 0 ) 
            {
                if( lista_merce )
                {
                    lista * nodo_merce = crea_nodo_merce( lista_merce );

                    lista_spesa = mod_nodo_add ( lista_spesa, nodo_merce, false );

                    lista_merce = mod_nodo_del ( lista_merce , nodo_merce );

                }
                else
                {
                    printf("\n\n\tLista merce vuota\n");
                    system("pause");
                }

            }
            
            if( scelta == 1 )
            {
                if( lista_spesa )
                {
                    lista * nodo_merce = crea_nodo_merce( lista_spesa );

                    lista_merce = mod_nodo_add ( lista_merce, nodo_merce, false );

                    lista_spesa = mod_nodo_del ( lista_spesa , nodo_merce );  
                }
                else
                {
                    printf("\nLista della spesa vuota\n\n");
                    system("pause");
                }

            }

            if( scelta == 2 )
            {
                //grafo
                if( !lista_spesa )
                {
                    printf("\n\n\tLISTA SPESA VUOTA\n\n");

                    printf("\t\tInserire y per uscire\n>");
                    int y = getch (); 

                    if ( y == 'y') return NULL;
                }
                else
                {
                    peso_totale = somma_elementi_lista ( lista_spesa ) + utente->info_user.peso_veicolo;

                    printf("%d\n",peso_totale);

                    system("pause");

                    
                    system ("cls");


                    interfaccia_percorso ( peso_totale );


                    deallocate_list ( lista_spesa ); // non funziona  una volta entrato in interfaccia percorso 
                    //e aver concluso tale funzione ritornado qui la lista della spesa esiste ancora

                    lista_spesa = NULL;
                }


            }

            if( scelta == 3 )
            {
                exit = true;
            }


        }
        system ("cls"); 

    }while ( !exit );  

    return lista_merce;

}


void interfaccia_percorso ( int peso_totale )
{
    system("cls");
    int partenza = 0, destinazione = 0;
    
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
    
    
    create_graph( gr, fopen("TELATO.txt","r"), &num_vertici, 0);

    stampa_graphic_grafo ( );

    gr->numero_vertici = num_vertici ;

    //gr != NULL ? stampa_grafo ( gr, 0 ) : printf("\n\n\tGrafo Vuoto\n")  ;  


    do
    {
        printf("\n\n\tInserisci la partenza\n>");
        partenza = insert_int ( );

    }while ( partenza < 0 && partenza > gr->numero_vertici );

    do
    {
        printf("\n\n\tInserisci la destinazione\n>");
        destinazione = insert_int ( );
    } while ( destinazione < 0 && destinazione > gr->numero_vertici );
    
    gr != NULL ? dijkstra( gr, partenza, destinazione, peso_totale ) : printf("\n\n\tGrafo Vuoto\n");

    system("pause");
}

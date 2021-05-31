#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

#include "hlista.h"
#include "hutility_function.h"
#include "hgrafi.h"
#include "hinterfaccia.h"

#define FIELD_SIZE 25
#define INIT 4

// utilizzo delle funzioni scelte
/*
    abbiamo adottato questo procedimento affinche' l'utente possa scegliere
    tramite una variabile intera che far stampare a schermo 
*/

// utilizzo delle funzioni schermate except schermata percorso
/*
    abbiamo adottato questo procedimento affinche l'utente possa scegliere
    che funzioni utilizzare.
    abbiamo utilizzato la libreria conio.h per utilizzare la funzione getch ()
    che prende l'input da tastiera senza stampare nulla a schermo.
    grazie a questo abbiamo pensato che utilizzando un vettore di dimensione data a priori 
    in base al tipo di schermata. Potevamo creare una simulazione di scelta tramite freccette.
    chiamando le scelte con l'equivalente freccetta ( if -> int scelta ++ ) ( if <- int scelta --)
    if( scelta > dim ) scelta = 0 . ( if scleta < 0) scelta = dim-1
    se si preme invio viene caricato scelta uguale all'equivalente intero e si procede alle funzioni scelte
*/

//          LOGIN SCELTE
char *scelte_avvio ( int scelta )
{
    if ( scelta == 0) return "log";
    else if ( scelta == 1 ) return "sign";
    else return "exit";

}

//          SCHERMATA LOGIN E SIGNIN
void schermata_avvio ( )
{
    int i = 0;

    int ch = 84;
    int scelta = 0;
    bool exit = false;
    
    lista * lista_merce = preleva_dati_da_file ( fopen ("stock_merce.txt","r"), true);

    lista * utente  = NULL;

    lista * lista_user = preleva_dati_da_file ( fopen ("driver_registrati.txt","r"), false);
    
    //ciclo finche' la variabile booleana exit non e' = true
    do
    {

        system ("cls");

        stampa_intestazione_schermata ( 1 );
        
        if( ch == 75 ) scelta = scelta - 1;

        if( ch == 77 ) scelta = scelta + 1;

        if ( scelta < 0 ) scelta = 2;

        if ( scelta > 2 ) scelta = 0;

        // stampo scelte
        for ( i = 0; i < 3; i++ )
        {
            if ( i == scelta ) printf ("\t [ %s ] ", scelte_avvio( i ) );
            
            else printf("\t%s", scelte_avvio( i ));
        }
        printf("\n\n\n\n\t");
        
        ch = getch( );

        // carico int scelta 
        if( ( ch == '\r') )
        {
            if( scelta == 0 && lista_user ) 
            {
                
                system("cls");

                // carico user loggato
                utente = login ( lista_user );

                // se l'user di peso veicolo e' maggiore di zero loggo
                // else significa che in login l'utente non e' riuscito a loggare
                // impostando peso veicolo ad un int < 0 
                if( utente->info_user.carico_veivolo >= 0 )
                {
                    printf("\n\n\n\n\n\n\t\tCREDENZIALI CORRETTE. ACCESSO IN CORSO....\n\n\n");
                    sleep ( 2 );

                    //step successivo vado in schermata ordini mantenendo la lista merce modificata
                    lista_merce = schermata_ordini ( utente , lista_merce );
                }
                else
                {
                    printf("\n\n\n\n\n\n\t\tCREDENZIALI NON CORRETTE. ACCESSO NEGATO\n\n\n\t\t");
                    system("pause");
                }

            }
            
            if( scelta == 1 )
            {
                system("cls");

                // aggiorno lista user con un nodo appena creato 
                // cioe' utente appena registrato 
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


    // chiusura programma

    // scrivo su file
    aggiorna_user_su_file ( lista_user, fopen("driver_registrati.txt","w"));

    // dealloco le liste usate
    deallocate_list ( lista_merce );
    deallocate_list ( lista_user );

    free ( utente );

}

//       SCELTE MERCE
char * merce_scelte ( int scelta )
{
    if ( scelta == 0) return "aggiungi";
    else if ( scelta == 1 ) return "rimuovi";
    else if (scelta == 2 ) return "conferma";
    else return "logout";

}


//          SCHERMATA GESTIONE MERCE 
lista * schermata_ordini ( lista * utente , lista * lista_merce)
{   
    int ch = 0;
    int scelta = 0;
    bool exit = false;

    bool bool_continue = false;
    int choice = 't'; 

    lista * lista_spesa = NULL;

    // aggiorno carico veicolo con la il peso
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
                    // creo un elemento di tipo struct che contine i dati di quello che si vuole prendere
                    lista * nodo_merce = crea_nodo_merce( lista_merce, lista_merce , lista_spesa , utente );

                    //aggiungo quell'elemento alla lista spesa
                    lista_spesa = mod_nodo_add ( lista_spesa, nodo_merce, false );

                    //sottraggo quell'elemento alla lista merce
                    lista_merce = mod_nodo_del ( lista_merce , nodo_merce );
                    
                    //aggiorno peso veicolo
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
                    // creo un elemento di tipo struct che contine i dati di quello che si vuole prendere
                    lista * nodo_merce = crea_nodo_merce(  lista_spesa, lista_merce , lista_spesa, utente  );

                    //aggiungo quell'elemento alla lista merce
                    lista_merce = mod_nodo_add ( lista_merce, nodo_merce, false );

                    //sottraggo quell'elemento alla lista spesa
                    lista_spesa = mod_nodo_del ( lista_spesa , nodo_merce );

                    //aggiorno peso veicolo
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

                if( !lista_spesa )
                {
                    printf("\tATTENZIONE : lista della spesa vuota\n");

                    printf("\tVuoi continuare lo stesso? y/n\n\t>");

                    choice = getch (); 

                    if ( choice == 'y') bool_continue = true;
                
                }
                
                if ( lista_spesa || bool_continue )
                {

                    system("cls");

                    printf("\n\n");


                    if( utente->info_user.carico_veivolo > 100)
                    {
                        printf("\n\tPeso totale : %d\n\tPeso troppo elevato, non puoi raggiungere nessun isola. Range 0 - 100 \n\n\n\t",utente->info_user.carico_veivolo);

                        choice = 't';

                        system("pause");

                    }
                    else
                    {
                        printf("\n\tPeso totale : %d\n\tConfermi ordine? y/n\n\t>",utente->info_user.carico_veivolo);
                        
                        choice = getch ( ); 
                    }
                    

                    if ( choice == 'y') 
                    {

                        system("cls");

                        printf("\n\tElaborazione ordine in corso...\n");
                        sleep( 2 );   
                        
                        printf("\tOrdine confermato\n\n\t");
                        system("pause");

                        schermata_percorso ( utente->info_user.carico_veivolo );

                        deallocate_list ( lista_spesa ); 

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


    free ( utente );
    
    if( lista_spesa ) 
    {
        lista_merce = aggiorna_lista_merce ( lista_merce, lista_spesa );
        deallocate_list ( lista_spesa );
    }

    return lista_merce;

}


//             SCHERMATA GRAFO CON MIN_PATH
void schermata_percorso ( int peso_totale )
{
    system("cls");

    // variabili per il min path
    int source = 0, target = 0;

    //grafo inizializzato a NULL
    grafo * gr = NULL;       

    // varibile per i num vertici
    int num_vertici = 0;

    // malloco memoria per il grafo
    gr  = ( grafo * )malloc(sizeof( grafo ));


    // check failed malloc mem
    if(gr == NULL) 
    {
        printf("ERRORE: imp. allocare mem. del grafo\n");
        return;
    }

    // malloco memoria per la lista adj
    gr->adj = ( arco **)malloc( INIT * sizeof ( arco * ));


    // check failed malloc mem
    if(gr->adj == NULL)  
    {
        printf("ERRORE: imp. allocare mem. per la lista del grafo\n");
        return;
    } 
    
    // prelevo dati da file creando grafo
    create_graph( gr, fopen("mappa_island.txt","r"), &num_vertici, 0);

    //inizializzo numero vertici 
    gr->numero_vertici = num_vertici ;


    stampa_nome_schermata( 5 );

    printf("\t\t\tPeso Veicolo : %d\n", peso_totale );
    
    stampa_graphic_grafo ( );

    //gr != NULL ? stampa_grafo ( gr, 0 ) : printf("\n\n\tGrafo Vuoto\n")  ;  


    printf("\n\n\tInserisci la partenza\n\t>");

    source = get_char ( gr->numero_vertici );   //prendo un intero decifrato da char



    printf("\n\n\tInserisci la destinazione\n\t>");

    target = get_char ( gr->numero_vertici );   //prendo un intero decifrato da char


    // abbiamo utilizzato l'algoritmo di dijsktra per il miglior mion path
    dijkstra( gr, source, target, peso_totale );

    system("pause");
}



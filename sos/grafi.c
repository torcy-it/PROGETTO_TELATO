#include <stdio.h>
#include <stdlib.h>

#include "grafi.h"

// completo
// creo un grafo con n nodi adiacenti
Grafo crea_grafo(int n)
{
    Grafo G;
    int i;


    G = (struct graph * )malloc( sizeof(  struct graph ) );

    if (  empty_grafo( G ) )
    {
        printf("ERRORE: impossibile allocare memoria per ilgrafo\n");
    }
    else
    {

        G->adj = ( Arco * )malloc( n * sizeof( struct archi *));

        if ( G->adj == NULL )
        {
            printf("ERRORE: impossibile allocare memoria per la lista del grafo\n");
            free( G );
            G = NULL;
        }
        else
        {
            G->numero_vertici = n;

            for ( i = 0; i < n; i++)
                G->adj[i] = NULL;
        }
    }

    return(G);
}

// completo
int empty_grafo( Grafo G )
{
    return ( G == NULL )? 1 : 0;
}

// completo
int empty_edge( Arco A )
{
    return ( A == NULL )? 1 : 0;
}

// completo
int numero_vertici( Grafo G )
{
    return G->numero_vertici;
}

// incompleto
// la somma degli archi non è cosi banale
int numero_archi( Grafo G )
{
    return G->numero_vertici -1 ;
}

// completo
void dai_peso_arco( Arco A , int peso)
{
    A->peso = peso;;
}

// completo
void modifica_peso_arco( Arco A)
{
    int peso = 0;
    int flag_peso_minore_di_zero = 0;

    do
    {
        flag_peso_minore_di_zero = 0;

        printf("\nInserisci nuovo valore per il peso: ");
        scanf("%d", &peso );

        if(peso < 0)
        {
            printf("\nErrore, peso deve essere maggiore di 0...\n Riprova\n");
            flag_peso_minore_di_zero = 1;
        }

    }
    while( flag_peso_minore_di_zero );

    A->peso = peso;

}

// completo
void verifica_presenza_arco( Grafo G, int u, int v , int * flag_trovato_uv_flag_errore_arco_gia_esistente )
{

    Arco scorri_adiacenti;
    Arco scorri_lista;

    int flag_errore_arco_gia_esistente = 0;
    int flag_trovato_uv = 0;




    for( int i = 0; i < G->numero_vertici; i++ )
    {

        // per ogni nodo verifico...

        scorri_adiacenti = G->adj[i];
        scorri_lista = scorri_adiacenti;

        // se c'è u...
        if( scorri_adiacenti->key == u )
        {
            flag_trovato_uv++;

            // guardo nella sua lista di adiacenze per cercare se esiste gia l'arco con v
            while( !empty_edge( scorri_lista->next ) )
            {
                if(  scorri_lista->key == v )
                {
                    printf("\nErrore arco già esistente\n");
                    flag_errore_arco_gia_esistente = 1;
                    break;
                }

                scorri_lista = scorri_lista->next;
            }

            // se esiste larco esco dal for
            if( flag_errore_arco_gia_esistente )
            {
                break;
            }
            // vado avanti nella lista di adiacenza


        }
        else if( scorri_adiacenti->key == v )
        {
            flag_trovato_uv++;

            while( !empty_edge( scorri_lista->next ) )
            {
                if( scorri_lista->key == u )
                {
                    printf("\nErrore arco già esistente\n");
                    flag_errore_arco_gia_esistente = 1;
                    break;
                }

                scorri_lista = scorri_lista->next;
            }
            if( flag_errore_arco_gia_esistente )
            {
                 break;
            }
        }
        // end else if

    }
    // end for


    // assegno le flag ad un array che verra restituito per conferma:
    if( flag_trovato_uv == 2 )
    {
        flag_trovato_uv_flag_errore_arco_gia_esistente[ 0 ] = 1;
    }
    else
    {
        flag_trovato_uv_flag_errore_arco_gia_esistente[ 0 ] = 0;
        printf("\nErrore: i nodi %d e %d non sono presenti nel grafo", u, v);
    }

    flag_trovato_uv_flag_errore_arco_gia_esistente[ 1 ] = flag_errore_arco_gia_esistente;

}

// comprelto
void add_arco( Grafo G, int u, int v, int peso_di_v)
{
    Arco nuovo = NULL;
    Arco scorri_adiacenti = NULL;
    Arco scorri_lista = NULL;

    int flag_trovato_uv_e_flag_errore_arco_gia_esistente[ 2 ];
    nuovo = ( Arco ) malloc( sizeof( struct archi ) );


    /////////////////////////////////////// controlli :


    // verifico che non si sia gia un arco ( u , v ) nel grafo
    // e
    // i nodi u e v siano nel grafo
    verifica_presenza_arco( G, u, v, flag_trovato_uv_e_flag_errore_arco_gia_esistente );
    if( flag_trovato_uv_e_flag_errore_arco_gia_esistente[ 0 ] == 1 || flag_trovato_uv_e_flag_errore_arco_gia_esistente[ 1 ] == 1)
    {
        printf("\nErrore\n");
        return;
    }


    // -memoria per 'nuovo' ben istanziata
    if ( empty_edge( nuovo ) )
    {
         printf("ERRORE: impossibile allocare memoria \n");
         return;
    }


    ////////////////////////////////////////////////////////// end controlli


    // add_arco:


    nuovo->key = v;
    nuovo->peso = peso_di_v;
    nuovo->next = NULL;

    // cerca u

    for( int i = 0; i < G->numero_vertici; i++ )
    {
        scorri_adiacenti = G->adj[ i ];
        scorri_lista = scorri_adiacenti;

        while( !empty_edge( scorri_lista ) )
        {

            if( scorri_lista->key == u )
            {
                printf("\nTrovato");
                break;
            }
        }
    }
    // alla fine del for in scorri_lista ci sara u
    // e in scorri_adiacenti ci sara il primo nodo del vettore adiacenze
    // perche i controlli fatti prima sono andati a buon fine


    // se u non ha archi:
    if ( scorri_adiacenti->next == NULL)
    {
        scorri_adiacenti->next = nuovo;
    }
    else
    {
        // percorro le adiacenze e aggiungo l'arco v
        scorri_lista = scorri_adiacenti;
        while ( !empty_edge( scorri_lista ) )
        {
            scorri_lista = scorri_lista->next;
        }

        scorri_lista->next = nuovo;
    }


}

// completo
void remove_arco( Grafo G, int u, int v)
{

    Arco prev; /* l'arco precedente a quello da togliere nella lista */
    Arco e; /* l'arco da togliere dalla lista */


    //controlla che g non sia vuoto...
    if( !empty_grafo( G ) )
    {

        // cerco l'arco ( u , v ) e lo elimino
        // se non c'è non fara nulla
        for( int i = 0; i < G->numero_vertici; i++ )
        {

            prev = G->adj[i];
            e = prev->next;

            // trovato u cerco v nella sua lista di adiacenze...
            // trovato v cerco u nella sua lista di adiacenze...
            // altrimenti cerco se ci sono ripetizioni dell'arco ( u , v ) e le cancello...
            if( prev->key == u )
            {
                // se gia il prossimo nodo non è vuoto:
                // cerco v tra gli adiacenti
                while( !empty_edge( e ) )
                {

                    // trovato v lo libero e congiungo il prossimo nodo
                    // altrimenti vado avanti sia con e che con prev...
                    if( e->key == v )
                    {
                        prev->next = e->next;
                        free( e );
                    }
                    else
                    {
                        e = e->next;
                        prev = prev->next;
                    }

                }//end while

            }
            else if( prev->key == v)
            {

                while( !empty_edge( e ) )
                {
                    if( e->key == u )
                    {
                        prev->next = e->next;
                        free( e );
                    }
                    else
                    {
                        e = e->next;
                        prev = prev->next;
                    }
                }// end while

            }
            else
            {

                // quindi cerco u e v
                // se ci sono li elimino dal grafo
                while( !empty_edge( e ) )
                {
                    if( e->key == u )
                    {
                        prev->next = e->next;
                        free( e );
                    }
                    else if( e->key == v)
                    {
                        prev->next = e->next;
                        free( e );
                    }
                    else
                    {
                        e = e->next;
                        prev = prev->next;
                    }
                }// end while

            }

        }// end for

    } //end if( eiste il grafo )
    else
    {
        printf("\nGrafo vuoto");
    }

}


// da controllare
void stampa_grafo( Grafo G )
{

    int i;

    Arco scorri_lista;



    // se il grafo esiste stampo ogni nodo e i suoi adiacenti...
    if ( !empty_grafo( G ) )
    {
        printf("\nIl grafo ha %d vertici:\n", numero_vertici( G ) );

        // per ogni nodi del grafo...
        for ( i=0; i<G->numero_vertici; i++ )
        {
            printf("\nnodi adiacenti al nodo %d -> ", i );

            scorri_lista = G->adj[ i ];

            // per ogni adiacente...
            while ( !empty_edge( scorri_lista ) )
            {
                printf("%d-> ", scorri_lista->key );
                scorri_lista = scorri_lista->next;
            }


            printf("\n");
        }
    }
}

// incmpleto
int grado( Grafo G, Arco A )
{
    int grado = 0;



    return grado;
}


// completo
Grafo add_nodo( Grafo G )
{
    Arco nuovo;
    int numero_nodi;
    int flag_numero_nodi_minore_di_zero = 0;

    // se il grafo non esiste lo crea e add il nodo
    // altrimenti add il nodo
    if( empty_grafo( G ) )
    {

        printf( "\nGrafo inesistente...\nQuanti nodi vuoi che abbia il tuo grafo?\n" );

        do
        {
            flag_numero_nodi_minore_di_zero = 0;


            scanf( "%d", &numero_nodi );

            if( numero_nodi < 0 || numero_nodi > 20 )
            {
                printf( "\nErrore, il numero dei nodi di un grafo dese essere tra ( 0 - 20 ) ...\n Riprova, grazie... \n" );
                flag_numero_nodi_minore_di_zero = 1;
            }

        }
        while( flag_numero_nodi_minore_di_zero );

        G = crea_grafo( numero_nodi );
    }
    else
    {
        nuovo = realloc( G->adj, (G->numero_vertici + 1) * sizeof( struct archi * ) );
    }

    // controllo istanziazione memoria
    if( nuovo == NULL )
    {

        printf("ERRORE: impossibile reallocare memoria \n");

    }
    else
    {

        G->adj = &nuovo;
        G->adj[ G->numero_vertici ] = NULL;
        G->numero_vertici = G->numero_vertici + 1;
    }

    return G ;
}





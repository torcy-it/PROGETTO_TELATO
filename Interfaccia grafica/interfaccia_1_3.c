#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include "hlista.h"

void interfaccia_merce ( );
char * merce_scelte ( int  );

int main ( )
{
    interfaccia_merce ( );
    
    return 0;
}



char * merce_scelte ( int scelta )
{
    if ( scelta == 0) return "add";
    else if ( scelta == 1 ) return "remove";
    else if (scelta == 2 ) return "conferma";
    else return "exit";

}

void interfaccia_merce ( )
{   
    int ch = 0;
    int scelta = 0;
    bool exit = false;
    

    lista * lista_merce = preleva_dati_da_file ( fopen ("stock_merce.txt","r"), true);
    lista * lista_spesa = NULL;

    do
    {



        system("cls");

        printf("\n\nLista merce\n");

        print_lista_merce ( lista_merce );// GOTO riga 155

        printf("\n\t\tNULL\n\nLISTA SPESA\n");

        print_lista_merce ( lista_spesa );

        printf("\n\t\tNULL\n\n");


        if( ch == 75 ) scelta = scelta - 1;

        if( ch == 77 ) scelta = scelta + 1;

        if ( scelta < 0 ) scelta = 3;

        if ( scelta > 3 ) scelta = 0;


        for ( int i = 0; i < 4; i++ )
        {
            if ( i == scelta ) printf ("\t [ %s ] ", merce_scelte( i ) );
            
            else printf("\t%s ", merce_scelte( i ));
        }
        printf("\n\n\n\n\t");
        
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

                    if ( y == 'y') return ;
                }
                else
                {
                    printf("\n\n\t\t\tfunzioni graph francesco\t\t\t");
                    system("pause");
                }


            }

            if( scelta == 3 )
            {
                exit = true;
            }
            system ("cls"); 


        }


    }while ( !exit );  


}

//Fabrizio se vuoi inserire la tua printf dell lista merci fallo 
// perchè non sono riuscito ad emularla
// per cambiare la printf vai su clista.c e cambi la funzione 
//print_merce che stampa la lista fino a quando non e' null
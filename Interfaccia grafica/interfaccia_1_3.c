#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>

#define FIELD_SIZE 25

#include "hlista.h"
#include "hour_function.h"

void interfaccia_merce ( lista );
char * merce_scelte ( int  );

void interfaccia_login ( );
char * login_scelte ( int  );

void login ( lista *  , lista * );
lista * signin ( lista *  );

int main ( )
{
    interfaccia_login ( );
    
    return 0;
}



char * merce_scelte ( int scelta )
{
    if ( scelta == 0) return "add";
    else if ( scelta == 1 ) return "remove";
    else if (scelta == 2 ) return "conferma";
    else return "exit";

}

void interfaccia_merce ( lista utente )
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

        printf("\t\tBENVENUTO %s %s \n\n",utente.info_user.name_user, utente.info_user.surname_user);


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

    aggiorna_merce ( lista_merce );

}

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
    lista utente;


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

                login ( lista_user, &utente );

                
                if( utente.info_user.carico_veivolo >= 0 )
                {
                    interfaccia_merce ( utente );
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
            system ("cls"); 


        }


    }while ( !exit );  

    aggiorna_user_su_file ( lista_user, fopen("utenti.txt","w"));
    aggiorna_file_merce ( );

}

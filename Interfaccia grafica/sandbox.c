
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

void interfaccia_1_0 ( );

void print ( int );

char * what_choice_is ( int  );

int main ( )
{
    interfaccia_1_0 ( );
    
    return 0;
}

void print ( int choice )
{
    for  ( int i = 0; i < 3 ; i++ )
    {
        if( choice == i ) printf (" %s[*] ",what_choice_is ( i ));

        else printf(" %s[ ] ", what_choice_is ( i ));
    }
}

char * what_choice_is ( int choice )
{

    if ( choice == 0) return "login";
    else if ( choice == 1 ) return "registrazione";
    else return "exit";
}

void interfaccia_1_0 ( )
{
    int ch = 0;
    int indice = 0;
    int dim = 3;


    do
    {

        if(ch == 75 ) indice = indice - 1;

        if( ch == 77 ) indice = indice + 1;

        if ( indice < 0 ) indice = dim-1;

        if ( indice > dim-1 ) indice = 0;

        

        system("cls");

        printf("\n\n\n\n\t");

        print( indice );
        
        printf("\n\n\n\n\t");

    }while( ( ch = getch( ) ) != '\r' );

    //indice equivale alla scelta dell'utente 
    //se indice è uguale a 0 allora vai in login 
    //se indice è uguale a 1 vai in sigin 
    //se è uguale a 2 vai in exit
    
}

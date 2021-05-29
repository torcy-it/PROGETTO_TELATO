
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

void interfaccia_1_0 ( );

void print ( int );

char * what_choice_is ( int  );

// MAIN
int main ( )
{
    // Richiama l'interfaccia con le operazioni da tastiera
    interfaccia_1_0 ( );
    
    // Ritorna 0
    return 0;
}

// PRINT
// Procedura che evidenzia l'operazione
void print ( int choice )
{
    // Per tutte le operazioni selezionabili (3 va sostituito con il numero di operazioni)
    for  ( int i = 0; i < 3 ; i++ )
    {
        // Evidenzia l'operazione scelta
        if( choice == i ) printf (" %s[*] ",what_choice_is ( i ));

        // Non evidenziare le altre
        else printf(" %s[ ] ", what_choice_is ( i ));
    }
}

// WHAT CHOICE IS
// Elenco delle operazioni selezionabili (in questo caso: login, registrazione, exit)
char * what_choice_is ( int choice )
{
    // Login
    if ( choice == 0) return "login";
    // Registrazione
    else if ( choice == 1 ) return "registrazione";
    // Exit
    else return "exit";
}

// INTERFACCIA 1_0
// Racchiude la logica di selezione dell'operazione tramite tastiera
void interfaccia_1_0 ( )
{
    // Carattere premuto da tastiera
    int ch = 0;
    // Posizione cursore che indica l'operazione (Es: 0 operazione X, 1 operazione Y, 2 operazione Z)
    int indice = 0;
    // Numero operazioni
    int dim = 3;

    
    // Esegui
    do
    {
        // Se il carattere digitato è la freccia sinistra
        if(ch == 75 )
        {
            // Diminuisci l'indice di 1
            indice = indice - 1;
        }

        // Se il carattere digitato è la freccia destra
        if( ch == 77 )
        {
            // Aumenta l'indice di 1
            indice = indice + 1;
        }

        // Se l'indice è negativo ricomincia dal lato opposto
        if ( indice < 0 )
        {
            indice = dim-1;
        }

        // Se l'indice supera il numero di operazioni, ricomincia dal lato opposto
        if ( indice > dim-1 )
        {
            indice = 0;
        }

        // Pulisci lo schermo
        system("cls");

        printf("\n\n\n\n\t");
        
        // Evidenzia l'operazione indicata da indice
        print( indice );
        
        printf("\n\n\n\n\t");

    // Finché non viene premuto un carattere di escape
    }while( ( ch = getch( ) ) != '\r' );
    
}


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>

#include "hlista.h"

#define FIELD_SIZE 25

void get_password( char *password, int inizio )
{
    int ch = 84; //variabile intera per prendere da input della tastiera

    if( inizio == FIELD_SIZE-1 || ( (ch = getch()) == '\r'  && inizio != 0) ) //controllo se ci troviamo in una pos maggiore della dim dell'array
    {                                                                         //GETCH prende i dati da input e ne blocca il buffer per l'output
        *password = '\0';                                                       // inizio != 0 perche' l'utente deve inserire per forza una password
        return;                                                                 //controllo se il carattere inserito è uguale a '\r' cioe'0 a return 
    }
    
    if ( ch < 48 || ch > 122) //controllo se il carattere e' contenuto nel range dell'asci 48 to 122
    {

        if (inizio != 0 && ch == '\b' ) //se non sono stati inseriti dei caratteri nell'array allora non cancellare 
        {                               
            printf("\b%c\b", ' ');
            inizio--;
            password--;
        }
    }
    else //in questo campo do come outputa video '*' e inserisco in password il carattere ch 
    {
        putchar('*');

        *password = (char)ch;

        password++; // incremento il puntatore

        inizio++; //incremento inizio per il controllo del backspace
    }

    get_password ( password , inizio );
}


//---------------------------------------------


void to_upper(char *stringa) 
{
    if (*stringa == '\0') //fine stringa
        return;

    else if (*stringa >= 'a' && *stringa <= 'z') //controllo carattere minuscolo
    {
        *stringa = *stringa - 'a' + 'A';//cambio in maiuscolo
    }

    to_upper(stringa + 1);// aumento pos indirizzo puntatore
}


void double_password(char *password)
{
    char tmp_password[FIELD_SIZE];

    printf("\n\n\t\t\tPassword: ");
    fflush( stdout );

    get_password( tmp_password , 0);

    if (!strcmp(tmp_password, "back"))
    {
        strcpy(password, "back");
        return;
    }

    printf("\n\n\t\t\tPassword: ");
    fflush( stdout );

    get_password( password , 0 );

    if (!strcmp(password, "back"))
        return;
    

    if (!strcmp(tmp_password, password))
        return;

    system("cls");

    printf("\n\t\t\tLe password !%s! !%s! non combaciano riprova\n", tmp_password, password);
    fflush(stdout);
    
    double_password(password);
    

}

/*
void insert_int ( int * numero )
{
    int ch;

    if ( (ch = getch()) == '\r'  && *numero %10 != 0 ) 
    {
        return ;
    }
    else
    {
        if ( ch < 48 || ch > 57) //controllo se il carattere e' contenuto nel range dell'asci 48 to 57
        {
            
            if ( ch == '\b' &&   *numero %10 != 0  ) //se non sono stati inseriti dei caratteri nell'array allora non cancellare 
            {                               
                printf("\b%c\b",' ');

                * numero = *  numero /10;
            }
        }
        else //in questo campo do come outputa video '*' e inserisco in password il carattere ch 
        {
            putchar ( ch );
            
            if( *numero %10 != 0 )
                *numero = *numero * 10;

            
            *numero = *numero + ( ch -'0' );

        }

        insert_int ( numero );

    }
    
}
*/

int insert_int ( )
{
    int ch;
    int numero = 0;

    do 
    {
        if ( ch < 48 || ch > 57) //controllo se il carattere e' contenuto nel range dell'asci 48 to 57
        {
            
            if ( ch == '\b' &&   numero %10 != 0  ) //se non sono stati inseriti dei caratteri nell'array allora non cancellare 
            {                               
                printf("\b%c\b",' ');

                numero = numero /10;
            }
        }
        else //in questo campo do come outputa video '*' e inserisco in password il carattere ch 
        {
            putchar ( ch );
            
            if( numero %10 != 0 )
                numero = numero * 10;

            
            numero = numero + ( ch -'0' );

        }

        if ( (ch = getch()) == '\r' && numero %10 != 0 ) 
            break;

    }while( 1 );

    return numero;
    
}
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include "hlista.h"
#include "hour_function.h"
#include <time.h>

#define FIELD_SIZE 25


// GET PASSWORD
// Funzione che maschera la password inserita con '*'
// in modo da nasconderla a video
void get_password( char *password, int inizio )
{
    // Variabile intera per prendere input da tastiera
    int ch = 84;

    // Caso base.
    // Controlla se ci troviamo in una posizione maggiore della dimensione dell'array.
    // getch prende i dati da input e ne blocca il buffer per l'output.
    // inizio!=0 perché l'utente deve inserire per forza una password.
    // Controlla se il carattere inserito è uguale a '\r' cioé 0 a return
    if( inizio == FIELD_SIZE-1 || ( (ch = getch()) == '\r'  && inizio != 0) )
    {  
        *password = '\0';                                                  
        return;                                                                 
    }
    
    // Se il carattere è contenuto nel range ASCII da 48 a 122
    if ( ch < 48 || ch > 122)
    {
        // Se non sono stati inseriti dei caratteri nell'array allora non cancellare
        if (inizio != 0 && ch == '\b' )
        {                               
            printf("\b%c\b", ' ');
            inizio--;
            password--;
        }
    }
    // Altrimenti
    else
    {
        // Stampa a video *
        putchar('*');

        // Inserisci in password il carattere ch
        *password = (char)ch;

        // Incrementa il puntatore
        password++;

        // Incrementa inizio per il controllo del backspace
        inizio++;
    }

    // Passo ricorsivo
    get_password ( password , inizio );
}

// TO UPPER
// Funzione che rende maiuscola la stringa passata
void to_upper(char *stringa) 
{
    // Caso base.
    // Se la stringa è terminata
    if (*stringa == '\0')
    {
        // Ritorna
        return;
    }

    // Altrimenti se il carattere è minuscolo
    else if (*stringa >= 'a' && *stringa <= 'z')
    {
        // Cambialo in minuscolo
        *stringa = *stringa - 'a' + 'A';
    }

    // Passo ricorsivo.
    // Passa al carattere successivo
    to_upper(stringa + 1);
}

// DOUBLE PASSWORD
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

// INSERT INT
int insert_int ( )
{
    int ch;
    unsigned int numero = 0;
    int count = 0;

    do 
    {
        if ( ch < 48 || ch > 57) //controllo se il carattere e' contenuto nel range dell'asci 48 to 57
        {
            
            if ( ch == '\b' && count!= 0 ) //se non sono stati inseriti dei caratteri nell'array allora non cancellare 
            {                               
                printf("\b%c\b",' ');
                count--;
                numero = numero /10;
            }
        }
        else //in questo campo do come outputa video '*' e inserisco in password il carattere ch 
        {
            putchar ( ch );
            
            numero = numero * 10;

            count++;
            numero = numero + ( ch -'0' );

        }

        if ( (ch = getch()) == '\r' ) 
            break;

    }while( 1 );

    return numero;
    
}


lista * signin ( lista * head )
{

    lista * data_user = ( lista * ) malloc ( sizeof (lista ));

    do
    {
        printf("\n\n\t\t\tUser ID: ");
        fflush( stdout );

        scanf("%s", data_user->info_user.targaID);

        to_upper(data_user->info_user.targaID);

        system("cls");

    }while( check_nodo_ID ( head , data_user->info_user.targaID , false));


    printf("\n\n\t\t\tName: ");
    scanf("%s",data_user->info_user.name_user);

    system("cls");
    
    printf("\n\n\t\t\tSurname : ");
    scanf("%s",data_user->info_user.surname_user);

    system("cls");

    double_password( data_user->info_user.password );

    system("cls");

    printf("\n\n\t\t\tPeso camion: ");
    fflush( stdout );

    do 
    {
        data_user->info_user.peso_veicolo = insert_int ( );     

    }while ( data_user->info_user.peso_veicolo > 0 );
    
    
    data_user->info_user.carico_veivolo = 0;

    data_user->next = NULL;

    system("cls");

    return add_node( head , data_user );

}

lista * login ( lista * head )
{
    lista * utente = ( lista *)malloc ( sizeof ( lista ));

    printf("\n\n\t\t\tUser ID: ");
    fflush(stdout);

    scanf("%s", utente->info_user.targaID);

    to_upper(utente->info_user.targaID);  

    printf("\n\n\t\t\tPassword: ");
    fflush(stdout);

    get_password( utente->info_user.password , 0);

    system("cls");

    load_user ( head , utente ); 

    utente->next = NULL;
}

// STAMPA GRAPHIC GRAFO
void stampa_graphic_grafo( void )
{
    printf("\n\n");
    printf("                    ___                   ___\n");
    printf("                   /\xB0\xB1\xB0\\       100       /\xB0\xB1\xB0\\\n");
    printf("                  |\xB0\xB1%c\xB1\xB0|---------------|\xB0\xB1%c\xB1\xB0|\n",'A','B');
    printf("                   \\\xB0\xB1\xB0/                 \\\xB0\xB1\xB0/\n");
    printf("                   /    \\               /    \\ \n");
    printf("                  /      \\             /      \\ \n");
    printf("                 /        \\           /        \\ \n");
    printf("                /       50 \\         / 100      \\ \n");
    printf("               /            \\       /            \\ \n");
    printf("           40 /              \\     /              \\ 40\n");
    printf("             /                \\   /                \\ \n");
    printf("            /                 /\xB0\xB1\xB0\\                 \\ \n");
    printf("           /                 |\xB0\xB1%c\xB1\xB0|                 \\ \n",'C');
    printf("          /                   \\\xB0\xB1\xB0/                   \\ \n");
    printf("         /         100        / | \\         60         \\ \n");
    printf("      /\xB0\xB1\xB0\\------------------'  |  '------------------/\xB0\xB1\xB0\\      \n");
    printf("     |\xB0\xB1%c\xB1\xB0|                  30|                    |\xB0\xB1%c\xB1\xB0|\n",'D','E');
    printf("      \\\xB0\xB1\xB0/-----------------.   |   .-----------------\\\xB0\xB1\xB0/\n");
    printf("         \\         100       \\  |  /       100         / \n");
    printf("          \\                   /\xB0\xB1\xB0\\                   / \n");
    printf("           \\                 |\xB0\xB1%c\xB1\xB0|                 / \n",'F');
    printf("            \\                 \\\xB0\xB1\xB0/                 / \n");
    printf("             \\                /   \\                /\n");
    printf("           60 \\              /     \\              / 100\n");
    printf("               \\            /       \\            /\n");
    printf("                \\       40 /         \\ 90       /\n");
    printf("                 \\        /           \\        /\n");
    printf("                  \\      /             \\      /\n");
    printf("                   \\    /               \\    /\n");
    printf("                   /\xB0\xB1\xB0\\                 /\xB0\xB1\xB0\\      \n");
    printf("                  |\xB0\xB1%c\xB1\xB0|---------------|\xB0\xB1%c\xB1\xB0|\n",'G','H');
    printf("                   \\\xB0\xB1\xB0/       100       \\\xB0\xB1\xB0/\n");
}

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
// Controllo password
void double_password(char *password)
{
    // Dichiara una variabile password temporanea dove verrà salvata la password temporanea
    char tmp_password[FIELD_SIZE];

    // Stampa a video la parola "Password"
    printf("\n\n\t\t\tPassword: ");
    // Pulisci buffer
    fflush( stdout );

    // Richiedi password all'utente
    get_password( tmp_password , 0);

    // Se la password digitata è "back"
    if (!strcmp(tmp_password, "back"))
    {
        // Copia "back" nel parametro passato in input
        strcpy(password, "back");
        // Ritorna
        return;
    }

    // Stampa a video la parola "Password"
    printf("\n\n\t\t\tPassword: ");
    // Pulisci buffer
    fflush( stdout );

    // Richiedi password all'utente
    get_password( password , 0 );

    // Se la password digitata è "back"
    if (!strcmp(password, "back"))
    {
        // Ritorna
        return;
    }
    
    // Se le password coincidono
    if (!strcmp(tmp_password, password))
    {
        // Ritorna
        return;
    }

    // Altrimenti le password non coincidono, quindi:
    
    // Pulisci schermo
    system("cls");

    // Informa l'utente che non c'è corrispondenza tra le 2 password
    printf("\n\t\t\tLe password !%s! !%s! non combaciano riprova\n", tmp_password, password);
    
    // Pulisci buffer
    fflush(stdout);
    
    // Chiamata ricorsiva per chiedere nuovamente la password
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
// Funzione per permettere l'inserimento da tastiera dei soli numeri interi.
// Usata, ad esempio, quando viene richiesto all'utente di digitare il peso del veicolo o la quantità di merce.
int insert_int ( )
{
    // Carattere digitato da tastiera
    int ch;
    // Numero restituito alla fine della funzione
    unsigned int numero = 0;
    // Variabile di conteggio
    int count = 0;
    
    // Esegui
    do 
    {
        // Se il carattere non è contenuto nel range ASCII da 48 a 57 (se non è un intero)
        if ( ch < 48 || ch > 57)
        {
            // Cancella il carattere
            if ( ch == '\b' && count!= 0 )
            {                               
                printf("\b%c\b",' ');
                count--;
                numero = numero /10;
            }
        }
        // Altrimenti
        else
        {
            // Visualizza carattere
            putchar ( ch );
            
            numero = numero * 10;

            count++;
            numero = numero + ( ch -'0' );

        }

        // Se viene digitato un carattere di escape
        if ( (ch = getch()) == '\r' )
        {
            // Esci dal ciclo
            break;
        }

    // Finché true
    }while( 1 );

    // Ritorna numero
    return numero;
    
}

// SIGN IN
// Registrazione del driver al sistema
lista * signin ( lista * head )
{
    // Alloca nodo data_user
    lista * data_user = ( lista * ) malloc ( sizeof (lista ));

    // Esegui
    do
    {
        // Stampa a video "User ID" (da sostituire con Digitare targa)
        printf("\n\n\t\t\tUser ID: ");
        // Pulisci buffer
        fflush( stdout );

        // Richiedi targa driver all'utente
        scanf("%s", data_user->info_user.targaID);

        // Converti la targa digitata in maiuscolo
        to_upper(data_user->info_user.targaID);

        // Pulisci schermo
        system("cls");

    // Finché la targa digitata non ha corrispondenza
    }while( check_nodo_ID ( head , data_user->info_user.targaID , false));

    // Stampa a video "Nome" (da sostituire con Digitare nome)
    printf("\n\n\t\t\tName: ");
    
    // Richiedi nome driver da tastiera
    scanf("%s",data_user->info_user.name_user);
    
    // Pulisci schermo
    system("cls");
    
    // Stampa a video "Surname" (da sostituire con Cognome)
    printf("\n\n\t\t\tSurname : ");
    
    // Richiedi cognome driver da tastiera
    scanf("%s",data_user->info_user.surname_user);

    // Pulisci schermo
    system("cls");

    // Richiedi password
    double_password( data_user->info_user.password );

    // Pulisci schermo
    system("cls");

    // Stampa a video "Peso camion" (da sostituire con Digitare Peso camion)
    printf("\n\n\t\t\tPeso camion: ");
    // Pulisci buffer
    fflush( stdout );

    // Richiedi il peso del veicolo
    do 
    {
        // Accettando solo valori interi
        data_user->info_user.peso_veicolo = insert_int ( );     

    }while ( data_user->info_user.peso_veicolo > 0 );
    
    // Imposta il peso del carico a 0
    data_user->info_user.carico_veivolo = 0;

    // Imposta a NULL il puntatore a next
    data_user->next = NULL;

    // Pulisci schermo
    system("cls");

    // Restituisci utente creato
    return add_node( head , data_user );

}

// LOGIN
// Accesso del driver accreditato
lista * login ( lista * head )
{
    // Alloca un nodo utente
    lista * utente = ( lista *)malloc ( sizeof ( lista ));

    // Stampa a video USER ID (come sopra) 
    printf("\n\n\t\t\tUser ID: ");
    
    // Pulisci buffer
    fflush(stdout);

    // Leggi targa da tastiera
    scanf("%s", utente->info_user.targaID);

    // Converti stringa/targa digitata in maiuscolo
    to_upper(utente->info_user.targaID);  

    // Stampa a video "Password"
    printf("\n\n\t\t\tPassword: ");
    
    // Pulisci buffer
    fflush(stdout);

    // Leggi password mascherando le lettere digitate con '*'
    get_password( utente->info_user.password , 0);

    // Pulisci schermo
    system("cls");

    // Accedi con le credenziali digitate
    load_user ( head , utente ); 

    // Imposta a NULL il puntatore a next del nodo Utente
    utente->next = NULL;
}

// STAMPA GRAPHIC GRAFO
// Stampa a video la mappa di Island
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

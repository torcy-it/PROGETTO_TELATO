
#include <stdlib.h>
#include <stdio.h>

#include <string.h>
#include <stdbool.h>
#include <conio.h>

#include "hlista.h"

#define FIELD_SIZE 25


void double_password( char *);

void to_lower( char *); //una tolower scritta a mano

void get_password( char * , int);

void login ( lista_user * );

lista_user * signin ( lista_user * );



int main(void)
{
    system("cls");

    lista_user * head = preleva_dati_da_file ( fopen("utenti.txt","r") );

    head = signin ( head );

    login ( head );
    print_lista_user ( head );

    return 0;
}

lista_user * signin ( lista_user * head )
{

    lista_user * info_user = ( lista_user * ) malloc ( sizeof (lista_user ));

    printf("\n\n\t\t\tUser ID: ");
    fflush( stdout );
    
    scanf("%s", info_user->targaID);

    to_lower(info_user->targaID);

    system("cls");

    while( check_nodo_ID ( head , info_user->targaID ))
    {
        printf("\n\n\t\t\tUser already taken: ");
        fflush( stdout );

        scanf("%s", info_user->targaID);

        to_lower(info_user->targaID);

        system("cls");
    }

    printf("\n\n\t\t\tName: ");
    scanf("%s",info_user->name_user);

    system("cls");
    
    printf("\n\n\t\t\tSurname : ");
    scanf("%s",info_user->surname_user);

    system("cls");

    double_password( info_user->password );

    system("cls");

    printf("\n\n\t\t\tPeso camion: ");
    fflush( stdout );

    scanf("%d",&info_user->peso_veicolo);
    info_user->carico_veivolo = 0;

    info_user->next = NULL;

    system("cls");

    
    return add_node( head , info_user );

}

void login ( lista_user * head )
{
    char user_id[FIELD_SIZE];  //user id
    char password[FIELD_SIZE]; //password

    printf("\n\n\t\t\tUser ID: ");
    fflush(stdout);

    scanf("%s", user_id);

    to_lower(user_id);  


    printf("\n\n\t\t\tPassword: ");
    fflush(stdout);

    get_password( password , 0);


    system("cls");

    if ( check_nodo_KEY( head, user_id, password ))
        printf("\n\n\t\tUSER AUTHENTICATED\n");
    else
        printf("\n\n\t\tINVALID USER\n");

}

void get_password( char *password, int inizio )
{
    int ch; //variabile intera per prendere da input della tastiera

    if( inizio == FIELD_SIZE-1 || ( (ch = getch()) == '\r'  && inizio != 0) ) //controllo se ci troviamo in una pos maggiore della dim dell'array
    {                                                                         //GETCH prende i dati da input e ne blocca il buffer per l'output
        *password = '\0';                                                       // inizio != 0 perche' l'utente deve inserire per forza una password
        return;                                                                 //controllo se il carattere inserito è uguale a '\r' cioe'0 a return 
    }
    
    
    if (ch == '\b' || ch == '\r' ) //controllo se il carattere inserito e' uguale a backspace '\b' oppure a return
    {

        if (inizio != 0 && ch != '\r' ) //se non sono stati inseriti dei caratteri nell'array allora non cancellare e infine controlla
        {                               //se il carattere inserito e' diverso da return 
            printf("\b%c\b", ' ');
            inizio--;
            password--;
        }
    }
    else //in questo campo do come output * e inserisco in password il carattere ch 
    {
        putchar('*');

        *password = (char)ch;

        password++; // incremento il puntatore

        inizio++; //incremento inizio per il controllo del backspace
    }

    get_password ( password , inizio );
}

//---------------------------------------------


void to_lower(char *stringa) //

{
    if (*stringa == '\0')
        return;

    else if (*stringa >= 'A' && *stringa <= 'Z')
        *stringa = *stringa - 'A' + 'a';

    to_lower(stringa + 1);
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
    {
        return;
    }

    if (!strcmp(tmp_password, password))
        return;
    else
    {
        system("cls");

        printf("\n\t\t\tLe password !%s! !%s! non combaciano riprova\n", tmp_password, password);
        fflush(stdout);
        
        double_password(password);
    }

}

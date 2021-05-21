
#include <stdlib.h>
#include <stdio.h>

#include <string.h>
#include <stdbool.h>
#include <conio.h>

#include "hlista.h"

#define FIELD_SIZE 25


void double_password(char *);

void to_lower(char *); //una tolower scritta a mano

void get_password(char *, int);

void login ( lista_user * );

lista_user * signin ( lista_user * );



int main(void)
{

    lista_user * head = preleva_dati_da_file ( fopen("utenti.txt","r") );

    head = signin ( head );

    login ( head );

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

    get_password(password, sizeof password);


    system("cls");

    if ( check_nodo_KEY( head, user_id, password ))
        printf("\n\n\t\tUSER AUTHENTICATED\n");
    else
        printf("\n\n\t\tINVALID USER\n");

}

void get_password(char *password, int size)
{
    int i = 0;
    int ch;

    while (i < size - 1 && (ch = getch()) != '\r')
    {
        if (ch == '\b')
        {
            // Don't run off the front end of the array
            if (i != 0)
            {
                printf("\b%c\b", ' ');
                --i;
            }
        }
        else
        {
            putchar('*');
            password[i++] = (char)ch;
        }
    }

    password[i] = '\0';
}


//---------------------------------------------


void to_lower(char *stringa) //una tolower scritta a mano
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

    get_password(tmp_password, FIELD_SIZE);

    if (!strcmp(tmp_password, "back"))
    {
        strcpy(password, "back");
        return;
    }

    printf("\n\n\t\t\tPassword: ");
    fflush( stdout );

    get_password(password, FIELD_SIZE);

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

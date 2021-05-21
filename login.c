
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

void signin ( void );



int main(void)
{
    lista_user * head = preleva_dati_da_file ( fopen("utenti.txt","r") );

    login( head );

    lista_user * nodo = (lista_user *) malloc ( sizeof (lista_user) );   

    strcpy(nodo->targaID,"adolf");
    strcpy(nodo->password,"hitler");
    strcpy(nodo->name_user,"3reich");
    strcpy(nodo->surname_user ,"ww2");
    nodo->carico_veivolo = 19;
    nodo->peso_veicolo = 39;
    nodo->next = NULL;

    head = add_node ( head, nodo);

    print_lista_user ( head );


    return 0;
}

void signin ( )
{
    char user_id[FIELD_SIZE];  //user id
    char password[FIELD_SIZE]; //password
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

int is_authorized(const char *user_id, const char *pwd) 
{


    return 0;
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


void double_password(char *stringa)
{
    char tmp_stringa[FIELD_SIZE];

    get_password(tmp_stringa, sizeof tmp_stringa);

    if (!strcmp(tmp_stringa, "back"))
    {
        strcpy(stringa, "back");
        return;
    }

    get_password(stringa, sizeof stringa);

    if (!strcmp(stringa, "back"))
    {
        return;
    }

    if (!strcmp(tmp_stringa, stringa))
        return;
    else
    {
        system("cls");

        printf("\n\t\t\tLe password !%s! !%s! non combaciano riprova\n", tmp_stringa, stringa);
        free(tmp_stringa);
    }

    double_password(stringa);
}

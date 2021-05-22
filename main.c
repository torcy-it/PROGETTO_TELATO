#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// STAMPA TITOLO
// Stampa il titolo del programma
void stampa_titolo_programma()
{
    printf("\t\t\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB\n");
    printf("\t\t\xBA  I-EATS\xA9  \xBA\n");
    printf("\t\t\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC\n");
}

// STAMPA NOME SCHERMATA
// Stampa il nome della schermata.
// Effettua i confronti per determinare quanto spazio lasciare a sinistra
// in modo da stampare il nome della schermata al centro
void stampa_nome_schermata(char nome_schermata[30])
{
    printf("\n");
    // Se il nome della schermata è menù principale
    if (strcmp(nome_schermata,"Men\xA3 principale")==0){
        printf("             \xFE %s \xFE\n",nome_schermata);
    }

    // Se il nome della schermata è schermata login
    if (strcmp(nome_schermata,"Schermata Login")==0){
        printf("             \xFE %s \xFE\n",nome_schermata);
    }

    // Se il nome della schermata è schermata registrazione
    if (strcmp(nome_schermata,"Schermata Registrazione")==0){
        printf("         \xFE %s \xFE\n",nome_schermata);
    }
    printf("\n");
}

// SCHERMATA LOGIN
// Viene aperta dal menù principale tramite l'operazione LOGIN
void schermata_login()
{
    // Operazione digitata dall'utente
    char operazione[50];
    do{
        // Stampa contenuto schermata
        system("cls");
        stampa_titolo_programma();
        stampa_nome_schermata("Schermata Login");
        printf("[INS]  - Inserisci credenziali\n");
        printf("[BACK] - Torna al Men\xA3 principale\n");
        printf("\n\nDigitare l'operazione desiderata: ");
        scanf("%s",operazione);

        // Controllo errore sull'operazione digitata dall'utente
        while(strcmp(operazione,"INS") != 0 && strcmp(operazione,"BACK"))
        {
            system("cls");
            stampa_titolo_programma();
            stampa_nome_schermata("Schermata Login");
            printf("[INS]  - Inserisci credenziali\n");
            printf("[BACK] - Torna al Men\xA3 principale");

            printf("\n\nErrore. Comando non riconosciuto.\n");
            printf("Digitare l'operazione desiderata: ");
            scanf("%s",operazione);
        }

    }while (strcmp(operazione,"BACK") != 0);
}

// SCHERMATA REGISTRAZIONE
// Viene aperta dal menù principale tramite l'operazione REG
void schermata_registrazione()
{
        // Operazione digitata dall'utente
    char operazione[50];
    do{
        // Stampa contenuto schermata
        system("cls");
        stampa_titolo_programma();
        stampa_nome_schermata("Schermata Registrazione");
        printf("[REG]  - Procedi con la registrazione\n");
        printf("[BACK] - Torna al Men\xA3 principale\n");
        printf("\n\nDigitare l'operazione desiderata: ");
        scanf("%s",operazione);

        // Controllo errore sull'operazione digitata dall'utente
        while(strcmp(operazione,"REG") != 0 && strcmp(operazione,"BACK"))
        {
            system("cls");
            stampa_titolo_programma();
            stampa_nome_schermata("Schermata Registrazione");
            printf("[REG]  - Procedi con la registrazione\n");
            printf("[BACK] - Torna al Men\xA3 principale\n");

            printf("\n\nErrore. Comando non riconosciuto.\n");
            printf("Digitare l'operazione desiderata: ");
            scanf("%s",operazione);
        }

    }while (strcmp(operazione,"BACK") != 0);
}

// SCHERMATA DRIVER
// Viene aperta

// MAIN - MENU' PRINCIPALE

int main()
{
    // Operazione utente
    char operazione[50];

    do
    {
        system("cls");
        stampa_titolo_programma();
        stampa_nome_schermata("Men\xA3 principale");
        printf("[REG]   - Registrazione Driver\n");
        printf("[LOGIN] - Login Driver\n");
        printf("[EXIT]  - Esci dal programma\n");
        printf("\n\nDigitare l'operazione desiderata: ");
        scanf("%s",operazione);

        // Controllo errore sull'operazione digitata dall'utente
        while(strcmp(operazione,"REG") != 0 && strcmp(operazione,"LOGIN") != 0 && strcmp(operazione,"EXIT") != 0)
        {
            system("cls");
            stampa_titolo_programma();
            stampa_nome_schermata("Men\xA3 principale");
            printf("[REG]   - Registrazione Driver\n");
            printf("[LOGIN] - Login Driver\n");
            printf("[EXIT]  - Esci dal programma\n");

            printf("\n\nErrore. Comando non riconosciuto.\n");
            printf("Digitare l'operazione desiderata: ");
            scanf("%s",operazione);
        }

        // Chiamata schermata operazione scelta
        if(strcmp(operazione,"REG") == 0)
        {
            schermata_registrazione();
        }

        if (strcmp(operazione,"LOGIN") == 0)
        {
            schermata_login();
        }

    } while(strcmp(operazione,"EXIT") != 0);

    printf("\nTerminazione programma in corso...");
    sleep(1);
    return 0;
}

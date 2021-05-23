#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

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
    if (strcmp(nome_schermata,"Men\xA3 principale")==0)
    {
        printf("             \xFE %s \xFE\n",nome_schermata);
    }

    // Se il nome della schermata è schermata login
    if (strcmp(nome_schermata,"Schermata Login")==0)
    {
        printf("             \xFE %s \xFE\n",nome_schermata);
    }

    // Se il nome della schermata è schermata registrazione
    if (strcmp(nome_schermata,"Schermata Registrazione")==0)
    {
        printf("          \xFE %s \xFE\n",nome_schermata);
    }

    // Se il nome della schermata è schermata driver
    if (strcmp(nome_schermata,"Schermata Driver")==0)
    {
        printf("             \xFE %s \xFE\n",nome_schermata);
    }

    // Se il nome della schermata è schermata carico
    if (strcmp(nome_schermata,"Schermata Carico")==0)
    {
        printf("             \xFE %s \xFE\n",nome_schermata);
    }
    printf("\n");
}

// GOTOXY
// Serve a posizionare elementi in modo ordinato
// spostando il cursore secondo le coordinate x e y
void gotoxy(int x, int y)
{
    COORD coord = {0,0};
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// SCHERMATA LOGIN
// Viene aperta dal menù principale tramite l'operazione LOGIN
void schermata_login()
{
    char operazione[50];   // Operazione digitata dall'utente
    char targa_camion[10]; // Targa del camion per la verifica delle credenziali
    char password[10];     // Password del driver per la verifica delle credenziali

    do{
        // Stampa contenuto schermata
        system("cls");
        stampa_titolo_programma();
        stampa_nome_schermata("Schermata Login");
        printf("\t[INS]  - Inserisci credenziali\n");
        printf("\t[BACK] - Torna al Men\xA3 principale\n");
        printf("\n\n Digitare l'operazione desiderata: ");
        scanf("%s",operazione);

        // Controllo errore sull'operazione digitata dall'utente
        while(strcmp(operazione,"INS") != 0 && strcmp(operazione,"BACK"))
        {
            system("cls");
            stampa_titolo_programma();
            stampa_nome_schermata("Schermata Login");
            printf("\t[INS]  - Inserisci credenziali\n");
            printf("\t[BACK] - Torna al Men\xA3 principale");

            printf("\n\n Errore. Comando non riconosciuto.\n");
            printf(" Digitare l'operazione desiderata: ");
            scanf("%s",operazione);
        }

        // Qui integriamo con le funzioni di Adolfo
        if(strcmp(operazione,"INS") == 0){
            printf(" Qui vanno le funzioni di Adolfo...\n");
            printf("\n Digitare targa camion: ");
            scanf("%s",targa_camion);
            // Inserire controllo lunghezza targa
            printf(" Digitare password: ");
            scanf("%s",password);
            // Inserire controllo lunghezza password
            // Inserire controllo credenziali
                //Se il controllo va a buon fine
                printf("\n Accesso in corso...");
                sleep(2);
                schermata_driver();
                //Altrimenti stampa messaggio di errore
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
        printf("\t[REG]  - Esegui registrazione\n");
        printf("\t[BACK] - Torna al Men\xA3 principale\n");
        printf("\n\n Digitare l'operazione desiderata: ");
        scanf("%s",operazione);

        // Controllo errore sull'operazione digitata dall'utente
        while(strcmp(operazione,"REG") !=0 && strcmp(operazione,"BACK")!=0)
        {
            system("cls");
            stampa_titolo_programma();
            stampa_nome_schermata("Schermata Registrazione");
            printf("\t[REG]  - Esegui registrazione\n");
            printf("\t[BACK] - Torna al Men\xA3 principale\n");

            printf("\n\n Errore. Comando non riconosciuto.\n");
            printf(" Digitare l'operazione desiderata: ");
            scanf("%s",operazione);
        }

        // Se l'utente digita REG, eseguire la funzione di registrazione scritta da Adolfo
        if(strcmp(operazione,"REG") == 0){
            printf("\n Qui va la funzione di Adolfo...\n");
            sleep(2);
        }

    }while (strcmp(operazione,"BACK") != 0);
}

// SCHERMATA CARICO
// Schermata di gestione del carico.
// Viene aperta tramite l'operazione CARICO
void schermata_carico()
{
    // Puntatore al file stock_merce.txt usato tramite l'operazione CARICO
    FILE* puntatore_file;

    puntatore_file = fopen("stock_merce.txt","r");

    if(puntatore_file == NULL)
    {
        printf("\n Errore nella procedura schermata_driver(). File stock_merce.txt non trovato\n\n");
        exit(-1);
    }
    system("cls");
    stampa_titolo_programma();
    stampa_nome_schermata("Schermata Carico");
    gotoxy(1,7);
    printf("\t\tMERCE IN STOCK");
    gotoxy(1,8);
    printf("\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4");
    printf("\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4");
    gotoxy(4,9);
    printf("NOME\t   NUM.COLLI\t      PESO");
    gotoxy(1,10);
    printf("\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4");
    printf("\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4");
    gotoxy(1,12);
    system("pause");
}

// SCHERMATA DRIVER
// Viene aperta dalla schermata login tramite l'operazione INS
// e inserendo delle credenziali corrette
void schermata_driver()
{
    // Operazione digitata dall'utente
    char operazione[50];

    do{
        // Stampa contenuto schermata
        system("cls");
        stampa_titolo_programma();
        stampa_nome_schermata("Schermata Driver");
        printf("\tBenvenuto Nome Cognome\n"); //Nome e Cognome saranno sostituiti dai campi nome e cognome del nodo driver
        printf("\tPeso camion: 50\n");  //50 sarà sostituito dal campo peso_camion del nodo driver
        printf("\tPeso carico: 0\n");   //0 sarà sostituito dal campo peso_carico del nodo driver
        printf("\t\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4");
        printf("\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\n");
        printf("\t[CARICO] - Gestione carico\n");
        printf("\t[TOMTOM] - Richiedi indicazioni\n");
        printf("\t[LOGOUT] - Esegui il logout\n");
        printf("\n\n Digitare l'operazione desiderata: ");
        scanf("%s",operazione);

        // Controllo errore sull'operazione digitata dall'utente
        while(strcmp(operazione,"CARICO") !=0 && strcmp(operazione,"TOMTOM") !=0 && strcmp(operazione,"LOGOUT") !=0 )
        {
            system("cls");
            stampa_titolo_programma();
            stampa_nome_schermata("Schermata Driver");
            printf("\tBenvenuto Nome Cognome\n"); //Nome e Cognome saranno sostituiti dai campi nome e cognome del nodo driver
            printf("\tPeso camion: 50\n");  //50 sarà sostituito dal campo peso_camion del nodo driver
            printf("\tPeso carico: 0\n");   //0 sarà sostituito dal campo peso_carico del nodo driver
            printf("\t\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4");
            printf("\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\n");
            printf("\t[CARICO] - Gestione carico\n");
            printf("\t[TOMTOM] - Richiedi indicazioni\n");
            printf("\t[LOGOUT] - Esegui il logout\n");

            printf("\n\n Errore. Comando non riconosciuto.\n");
            printf(" Digitare l'operazione desiderata: ");
            scanf("%s",operazione);
        }

        if(strcmp(operazione,"CARICO") == 0)
        {
            schermata_carico();
        }

        if(strcmp(operazione,"TOMTOM") == 0)
        {
            printf("\n Qui vanno le funzioni di Francesco...\n");
            sleep(2);
        }

    }while (strcmp(operazione,"LOGOUT") != 0);
    printf("\n Logout in corso...");
    sleep(2);
}

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
        printf("\t[REG]   - Registrazione Driver\n");
        printf("\t[LOGIN] - Login Driver\n");
        printf("\t[EXIT]  - Esci dal programma\n");
        printf("\n\n Digitare l'operazione desiderata: ");
        scanf("%s",operazione);

        // Controllo errore sull'operazione digitata dall'utente
        while(strcmp(operazione,"REG") != 0 && strcmp(operazione,"LOGIN") != 0 && strcmp(operazione,"EXIT") != 0)
        {
            system("cls");
            stampa_titolo_programma();
            stampa_nome_schermata("Men\xA3 principale");
            printf("\t[REG]   - Registrazione Driver\n");
            printf("\t[LOGIN] - Login Driver\n");
            printf("\t[EXIT]  - Esci dal programma\n");

            printf("\n\n Errore. Comando non riconosciuto.\n");
            printf(" Digitare l'operazione desiderata: ");
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

    printf("\n Terminazione programma in corso...");
    sleep(2);
    printf("\n Addios!\n\n");
    return 0;
}

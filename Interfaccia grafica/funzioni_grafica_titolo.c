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

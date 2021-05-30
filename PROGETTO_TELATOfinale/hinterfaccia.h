#ifndef HGRAPHIC_H
#define HGRAPHIC_H

#include "hlista.h"

void schermata_percorso ( int  );

void stampa_titolo_programma( void );

void stampa_nome_schermata( int );

lista * schermata_ordini ( lista *, lista * );

char * scelte_ordini ( int  );

void schermata_avvio ( );

char * scelte_avvio ( int  );

#endif
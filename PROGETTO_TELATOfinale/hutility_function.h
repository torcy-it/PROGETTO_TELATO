#ifndef HF_H
#define HF_H

#include <stdlib.h>
#include <stdio.h>
#include "hlista.h"


void stampa_intestazione_schermata ( int  );

void stampa_titolo_programma( void );

void stampa_schermata_ordini ( int , lista *  , lista * , lista *  );

void double_password( char *);

void to_upper( char *); 

void get_password( char * , int);

int get_char ( int  );

int insert_int ( void ) ;

lista * login ( lista *   );

lista * signin ( lista *  );

void stampa_graphic_grafo( void );

#endif
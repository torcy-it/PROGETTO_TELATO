
#ifndef HLOGIN_H
#define HLOGIN_H

#include <stdlib.h>
#include <stdio.h>

#include "hlista.h"

void double_password( char *);

void to_upper( char *); 

void get_password( char * , int);

void login ( lista_user * );

lista_user * signin ( lista_user * );

int insert_int ( void ) ;

#endif
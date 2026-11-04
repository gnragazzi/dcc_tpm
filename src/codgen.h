#ifndef CODGEN_H
#define CODGEN_H

#include "sistejec.h"

extern float CODE[TAM_PROG];
extern int libre;

extern char CTES[TAM_CTES];
extern int libre_ctes;

extern int construccion_no_soportada;

int generar_objeto(char *fuente);

#endif

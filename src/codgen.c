#include <stdlib.h>
#include <string.h>
#include "codgen.h"

float CODE[TAM_PROG];
int libre = 0;

char CTES[TAM_CTES];
int libre_ctes = 0;

int construccion_no_soportada = 0;

int generar_objeto(char *fuente)
{
	size_t largo = strlen(fuente);
	char *objeto = (char *) malloc(largo + 3);
	int ok;

	strcpy(objeto, fuente);
	if (largo >= 2 && strcmp(fuente + largo - 2, ".c") == 0)
		objeto[largo - 1] = 'o';
	else
		strcat(objeto, ".o");

	ok = guardar_codgen(CODE, CTES, objeto);
	free(objeto);
	return ok;
}

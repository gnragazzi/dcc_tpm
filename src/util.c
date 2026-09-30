#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "util.h"
#include "codigos.h"
#include "error.h"


void scanner()
{
	int i;
	for(; (i = yylex()) != NADA && lookahead() == SEGUIR;);

	if(i == NADA)
		sbol->codigo = CEOF;
	/* yylex retorna 0 si llego a fin de archivo */

	liberar = linea;
	linea = (char *) malloc (strlen(linea) + strlen (token1.lexema) + 3);
	strcpy(linea, liberar);
	strcat(linea, token1.lexema);
	free((void *) liberar);
}


void init_parser(int argc, char *argv[])
{
	linea = (char *) malloc (2);
	strcpy(linea, "");
	nro_linea = 0;

	if(argc != 3)
	{
		error_handler(6);
		error_handler(COD_IMP_ERRORES);
		exit(1);
	}
	else
	{
		if(strcmp(argv[1], "-c") == 0)
		{
			if((yyin = fopen(argv[2], "r")) == NULL)
			{
				error_handler(8);
				error_handler(COD_IMP_ERRORES);
				exit(1);
			}
		}
		else
		{
			error_handler(7);
			error_handler(COD_IMP_ERRORES);
			exit(1);
		}
	}

	sbol = &token1;

	scanner();
}


void match(set codigo, int ne)
{
    if(lookahead() & codigo)
        scanner();
    else
        error_handler(ne);
}


set lookahead()
{
	return sbol->codigo;
}


set lookahead_in(set conjunto)
{
	return lookahead() & conjunto;
}

void test(set c1, set c2, int ne)
{
	if(!lookahead_in(c1))
	{
		error_handler(ne);
		set conjunto_sincronizacion = c1 | c2;
		while(!lookahead_in(conjunto_sincronizacion))
			scanner();
	}
}

enum boolean esTipoBase(enum tipo tipo) {return tipo > 0;}

enum tipo resolverTipo(char *nombre){
	if(strcmp(T_VOID, nombre) == 0)
		return VOID;
	if(strcmp(T_CHAR, nombre) == 0)
		return CHAR;
	if(strcmp(T_INT, nombre) == 0)
		return INT;
	if(strcmp(T_FLOAT, nombre) == 0)
		return FLOAT;
	if(strcmp(T_ARREGLO, nombre) == 0)
		return ARREGLO;
	else
		return ERROR;
}

enum boolean param1_es_coercionable_a_param2(enum tipo param1, enum tipo param2){
	if(param1>0 && param1 <= param2)
		return TRUE;

	return FALSE;
}
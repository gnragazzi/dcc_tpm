#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "util.h"
#include "codigos.h"
#include "error.h"
#include "ts.h"


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

void iniciar_lista_parametros(Lista_Parametros *lista) {
	lista->primer_parametro = NULL;
	lista->ultimo_parametro = NULL;
	lista->cantidad = 0;
}

void agregar_parametro(Lista_Parametros *lista, enum tipo tipo_dato, enum tipo tipo_base, enum boolean es_clase_variable) {
	Parametro *nuevo_parametro = (Parametro *) malloc(sizeof(Parametro));

	nuevo_parametro->tipo_dato = tipo_dato;
	if (tipo_dato == ARREGLO) {
		nuevo_parametro->tipo_base = tipo_base;
	}
	nuevo_parametro->es_clase_variable = es_clase_variable;
	nuevo_parametro->siguiente = NULL;

	if (lista->cantidad == 0) {
		lista->primer_parametro = lista->ultimo_parametro = nuevo_parametro;
	}else {
		lista->ultimo_parametro->siguiente = nuevo_parametro;
        lista->ultimo_parametro = nuevo_parametro;
	}

	lista->cantidad = lista->cantidad + 1;

	return;
}

void limpiar_lista(Lista_Parametros *lista) {
	if (lista->cantidad == 0)
		return;

	Parametro *proximo = lista->primer_parametro;
	while (proximo != NULL) {
		Parametro *aux = proximo->siguiente;
		free(proximo);
		proximo = aux;
	}
}

enum boolean es_tipo_base(enum tipo tipo) {return tipo > 0;}

enum tipo resolver_tipo(char *nombre){
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

int resolver_tipo_en_TS(enum tipo tipo){
	switch (tipo) {
		case VOID:
			return en_tabla(T_VOID);
		case CHAR:
			return en_tabla(T_CHAR);
		case INT:
			return en_tabla(T_INT);
		case FLOAT:
			return en_tabla(T_FLOAT);
		case ARREGLO:
			return en_tabla(T_ARREGLO);
		case ERROR:
			return en_tabla(T_ERROR);
	}
}

enum boolean param1_es_coercionable_a_param2(enum tipo param1, enum tipo param2){
	if(param1>0 && param1 <= param2)
		return TRUE;

	return FALSE;
}

enum tipo mayor(enum tipo a, enum tipo b){
    if (a > b)
        return a;

    return b;
}

void lanzar_error_si_corresponde(enum tipo a){
    if(a == ARREGLO || a == VOID){
        error_handler(96);
    }
    if( a == STRING){
        error_handler(94);
    }

}

enum tipo resolver_tipo_operador(enum tipo tipo_1, enum tipo tipo_2){
    if(es_tipo_base(tipo_1) && es_tipo_base(tipo_2)){
        return mayor(tipo_1, tipo_2);
    }

    lanzar_error_si_corresponde(tipo_1);
    lanzar_error_si_corresponde(tipo_2);

    return ERROR;
}

entrada_TS *nueva_entrada() {
	return inf_id;
}
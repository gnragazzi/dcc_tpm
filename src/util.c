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

void insertar_parametro_en_funcion(int posicion_tabla_simbolos, Parametro_en_TS parametro_en_ts) {
	entrada_TS *entrada_funcion = ts[posicion_tabla_simbolos].ets;
	tipo_inf_res *nuevo_parametro = (tipo_inf_res *) malloc(sizeof(tipo_inf_res));

	nuevo_parametro->ptero_tipo = parametro_en_ts.puntero_tipo_dato;
	nuevo_parametro->tipo_pje = parametro_en_ts.tipo_pasaje;
	nuevo_parametro->ptero_tipo_base = parametro_en_ts.puntero_tipo_base;
	nuevo_parametro->ptr_sig = NULL;

	int cantidad_parametros = entrada_funcion->desc.part_var.sub.cant_par;

	if (cantidad_parametros == 0) {
		entrada_funcion->desc.part_var.sub.ptr_inf_res = nuevo_parametro;
	}else {
		tipo_inf_res *ultimo_parametro = entrada_funcion->desc.part_var.sub.ptr_inf_res;

		for (int i = 1; i < cantidad_parametros; i++) {
			ultimo_parametro = ultimo_parametro->ptr_sig;
		}

		ultimo_parametro->ptr_sig = nuevo_parametro;
	}

	entrada_funcion->desc.part_var.sub.cant_par++;
}

void chequear_igualdad_parametro_actual_vs_parametro_TS(Parametro_actual parametro_actual, tipo_inf_res *parametro_formal) {
	enum tipo tipo_formal = resolver_tipo(ts[parametro_formal->ptero_tipo].ets->nbre);

	if (parametro_formal->tipo_pje == REFERENCIA && !parametro_actual.es_clase_variable) {
		error_handler(93);
		return;
	}

	if (tipo_formal == ARREGLO) {
		if (parametro_actual.tipo_dato != ARREGLO) {
			error_handler(parametro_actual.es_clase_variable ? 91 : 98);
		} else if (parametro_actual.tipo_base != resolver_tipo(ts[parametro_formal->ptero_tipo_base].ets->nbre)) {
			error_handler(91);
		}
		return;
	}

	if (parametro_actual.tipo_dato == ARREGLO) {
		error_handler(91);
		return;
	}

	enum boolean tipos_compatibles = parametro_formal->tipo_pje == REFERENCIA
		? parametro_actual.tipo_dato == tipo_formal
		: param1_es_coercionable_a_param2(parametro_actual.tipo_dato, tipo_formal);

	if (!tipos_compatibles) {
		error_handler(91);
	}
}

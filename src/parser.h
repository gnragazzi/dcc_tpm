#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "codigos.h"
#include "util.h"
#include "error.h"

/* BORRAR CUANDO YA ESTÉN IMPLEMENTADOS LOS FIRST!!!!!!! */
#include <limits.h>
#define PLACEHOLDER LLONG_MAX
/* */

#define F_UNIDAD_TRADUCCION PLACEHOLDER
#define F_DECLARACIONES PLACEHOLDER
#define F_ESPECIFICADOR_TIPO PLACEHOLDER
#define F_ESPECIFICADOR_DECLARACION PLACEHOLDER
#define F_DEFINICION_FUNCION PLACEHOLDER
#define F_DECLARACION_VARIABLE PLACEHOLDER
#define F_LISTA_DECLARACIONES_PARAM PLACEHOLDER
#define F_DECLARACION_PARAMETRO PLACEHOLDER
#define F_DECLARADOR_INIT PLACEHOLDER
#define F_LISTA_DECLARACIONES_INIT PLACEHOLDER
#define F_LISTA_INICIALIZADORES PLACEHOLDER
#define F_LISTA_PROPOSICIONES PLACEHOLDER
#define F_LISTA_DECLARACIONES PLACEHOLDER
#define F_DECLARACION PLACEHOLDER
#define F_PROPOSICION PLACEHOLDER
#define F_PROPOSICION_EXPRESION PLACEHOLDER
#define F_PROPOSICION_COMPUESTA PLACEHOLDER
#define F_PROPOSICION_SELECCION PLACEHOLDER
#define F_PROPOSICION_ITERACION PLACEHOLDER
#define F_PROPOSICION_E_S PLACEHOLDER
#define F_PROPOSICION_RETORNO PLACEHOLDER
#define F_EXPRESION PLACEHOLDER
#define F_EXPRESION_SIMPLE PLACEHOLDER
#define F_TERMINO PLACEHOLDER
#define F_FACTOR PLACEHOLDER
#define F_VARIABLE PLACEHOLDER
#define F_LLAMADA_FUNCION PLACEHOLDER
#define F_LISTA_EXPRESIONES PLACEHOLDER
#define F_CONSTANTE PLACEHOLDER
#define F_RELACION PLACEHOLDER

#define F_RESTO_EXPRESION PLACEHOLDER
#define F_RESTO_EXPRESION_SIMPLE PLACEHOLDER
#define F_RESTO_TERMINO PLACEHOLDER
#define F_RESTO_OPCIONAL PLACEHOLDER
#define F_RESTO_LISTA_EXPRESIONES PLACEHOLDER
#define F_OPERADOR_OPCIONAL PLACEHOLDER
#define F_OPERADOR PLACEHOLDER
#define F_OPERADOR_MUL PLACEHOLDER

#define F_ELSE_OPCIONAL PLACEHOLDER
#define F_RESTO_PROP_IN PLACEHOLDER
#define F_RESTO_PROP_OUT PLACEHOLDER

#define F_RESTO_LISTA_DECLARACIONES_PARAM PLACEHOLDER
#define F_RESTO_LISTA_DECLARACIONES_INIT PLACEHOLDER
#define F_RESTO_LISTA_INICIALIZADORES PLACEHOLDER
#define F_OPREF_OPCIONAL PLACEHOLDER
#define F_ARREGLO_OPCIONAL PLACEHOLDER
#define F_LIMITE_OPCIONAL PLACEHOLDER
#define F_LISTA_OPCIONAL PLACEHOLDER

int last_call=0;

/*********** prototipos *************/

void unidad_traduccion();
void declaraciones();
void especificador_tipo();
void especificador_declaracion();
void definicion_funcion();
void declaracion_variable();
void lista_declaraciones_param();
void declaracion_parametro();
void declarador_init();
void lista_declaraciones_init();
void lista_inicializadores();
void lista_proposiciones();
void lista_declaraciones();
void declaracion();
void proposicion();
void proposicion_expresion();
void proposicion_compuesta();
void proposicion_seleccion();
void proposicion_iteracion();
void proposicion_e_s();
void proposicion_retorno();
void expresion();
void expresion_simple();
void termino();
void factor();
void variable();
void llamada_funcion();
void lista_expresiones();
void constante();

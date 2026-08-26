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
#define ESPECIFICADOR_DECLARACION PLACEHOLDER
#define DEFINICION_FUNCION PLACEHOLDER
#define DECLARACION_VARIABLE PLACEHOLDER
#define LISTA_DECLARACIONES_PARAM PLACEHOLDER
#define DECLARACION_PARAMETRO PLACEHOLDER
#define DECLARADOR_INIT PLACEHOLDER
#define LISTA_DECLARACIONES_INIT PLACEHOLDER
#define LISTA_INICIALIZADORES PLACEHOLDER
#define LISTA_PROPOSICIONES PLACEHOLDER
#define LISTA_DECLARACIONES PLACEHOLDER
#define DECLARACION PLACEHOLDER
#define PROPOSICION PLACEHOLDER
#define PROPOSICION_EXPRESION PLACEHOLDER
#define PROPOSICION_COMPUESTA PLACEHOLDER
#define PROPOSICION_SELECCION PLACEHOLDER
#define PROPOSICION_ITERACION PLACEHOLDER
#define PROPOSICION_E_S PLACEHOLDER
#define PROPOSICION_RETORNO PLACEHOLDER
#define EXPRESION PLACEHOLDER
#define EXPRESION_SIMPLE PLACEHOLDER
#define TERMINO   PLACEHOLDER
#define FACTOR    PLACEHOLDER
#define VARIABLE  PLACEHOLDER
#define LLAMADA_FUNCION PLACEHOLDER
#define LISTA_EXPRESIONES PLACEHOLDER
#define CONSTANTE PLACEHOLDER

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

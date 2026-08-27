#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "conjuntos.h"
#include "util.h"
#include "error.h"

int last_call=0;

/*********** prototipos *************/

void unidad_traduccion(set folset);
void declaraciones(set folset);
void especificador_tipo(set folset);
void especificador_declaracion(set folset);
void definicion_funcion(set folset);
void declaracion_variable(set folset);
void lista_declaraciones_param(set folset);
void declaracion_parametro(set folset);
void declarador_init(set folset);
void lista_declaraciones_init(set folset);
void lista_inicializadores(set folset);
void lista_proposiciones(set folset);
void lista_declaraciones(set folset);
void declaracion(set folset);
void proposicion(set folset);
void proposicion_expresion(set folset);
void proposicion_compuesta(set folset);
void proposicion_seleccion(set folset);
void proposicion_iteracion(set folset);
void proposicion_e_s(set folset);
void proposicion_retorno(set folset);
void expresion(set folset);
void expresion_simple(set folset);
void termino(set folset);
void factor(set folset);
void variable(set folset);
void llamada_funcion(set folset);
void lista_expresiones(set folset);
void constante(set folset);

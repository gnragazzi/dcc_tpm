#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "conjuntos.h"
#include "util.h"
#include "error.h"
#include "ts.h"

typedef struct {} retorno_unidad_traduccion;
typedef struct {} retorno_declaraciones;

typedef struct {
    enum tipo tipo;
} retorno_especificador_tipo;

typedef struct {} retorno_especificador_declaracion;
typedef struct {} retorno_definicion_funcion;
typedef struct {} retorno_declaracion_variable;
typedef struct {} retorno_lista_declaraciones_param;
typedef struct {} retorno_declaracion_parametro;
typedef struct {} retorno_declarador_init;
typedef struct {} retorno_lista_declaraciones_init;

typedef struct {
    int cantidad_inicializadores;
    enum tipo tipo_inicializadores;
} retorno_lista_inicializadores;

typedef struct {} retorno_lista_proposiciones;
typedef struct {} retorno_lista_declaraciones;
typedef struct {} retorno_declaracion;
typedef struct {} retorno_proposicion;
typedef struct {} retorno_proposicion_expresion;
typedef struct {} retorno_proposicion_compuesta;
typedef struct {} retorno_proposicion_seleccion;
typedef struct {} retorno_proposicion_iteracion;
typedef struct {} retorno_proposicion_e_s;
typedef struct {} retorno_proposicion_retorno;
typedef struct {} retorno_expresion;
typedef struct {} retorno_expresion_simple;
typedef struct {} retorno_termino;
typedef struct {} retorno_factor;
typedef struct {} retorno_variable;
typedef struct {} retorno_llamada_funcion;
typedef struct {} retorno_lista_expresiones;
typedef struct {} retorno_constante;

int last_call=0;

/*********** prototipos *************/

void unidad_traduccion(set folset);
void declaraciones(set folset);
retorno_especificador_tipo especificador_tipo(set folset);
void especificador_declaracion(set folset);
void definicion_funcion(set folset);
void declaracion_variable(set folset);
void lista_declaraciones_param(set folset);
void declaracion_parametro(set folset);
void declarador_init(set folset);
void lista_declaraciones_init(set folset);
retorno_lista_inicializadores lista_inicializadores(set folset);
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

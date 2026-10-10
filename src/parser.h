#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "conjuntos.h"
#include "util.h"
#include "error.h"
#include "ts.h"

typedef struct {
    char *identificador;
    enum tipo tipo_declaracion;
} parametros_especificador_declaracion;

typedef struct {
    enum tipo tipo_retorno;
    int posicion_tabla_simbolos;
} parametros_definicion_funcion;

typedef struct {
    int posicion_tabla_simbolos;
} parametros_lista_declaraciones_param;

typedef struct {
    int posicion_tabla_simbolos;
} parametros_declaracion_parametro;

typedef struct {
    enum tipo tipo_declaracion;
    char *identificador;
} parametros_declaracion_variable;

typedef struct {
    enum tipo tipo_declaracion;
    char * identificador;
} parametros_declarador_init;

typedef struct {
    enum tipo tipo_declaracion;
} parametros_lista_declaraciones_init;

typedef struct {
    int indice_en_TS;
    enum boolean origen_proposicion_entrada;
}parametros_variable;

typedef struct {
    int indice_en_TS;
} parametros_llamada_funcion;

typedef struct {
    int indice_en_TS;
    enum boolean chequear_parametros;
} parametros_lista_expresiones;

typedef struct {
    enum tipo tipo;
} retorno_especificador_tipo;

typedef struct {
    enum tipo tipo_retorno;
    enum boolean *tiene_retorno;
} parametros_lista_proposiciones;

typedef struct {
    enum tipo tipo_retorno;
    enum boolean *tiene_retorno;
} parametros_proposicion;

typedef struct {
    enum tipo tipo_retorno;
    enum boolean *tiene_retorno;
} parametros_proposicion_compuesta;

typedef struct {
    enum tipo tipo_retorno;
    enum boolean *tiene_retorno;
} parametros_proposicion_seleccion;

typedef struct {
    enum tipo tipo_retorno;
    enum boolean *tiene_retorno;
} parametros_proposicion_iteracion;

typedef struct {
    enum tipo tipo_retorno;
} parametros_proposicion_retorno;

typedef struct {
    int cantidad_inicializadores;
    enum tipo tipo_inicializadores;
} retorno_lista_inicializadores;

typedef struct {
    enum tipo tipo;
    enum tipo tipo_base;
    enum boolean es_clase_variable;
} retorno_expresion;

typedef struct {
    enum tipo tipo;
    enum tipo tipo_base;
    enum boolean es_clase_variable;
} retorno_expresion_simple;

typedef struct {
    enum tipo tipo;
    enum tipo tipo_base;
    enum boolean es_clase_variable;
} retorno_termino;

typedef struct {
    enum tipo tipo;
    enum tipo tipo_base;
    enum boolean es_clase_variable;
} retorno_factor;

typedef struct {
    enum tipo tipo;
    enum tipo tipo_base;
} retorno_variable;

typedef struct {
    enum tipo tipo;
} retorno_llamada_funcion;

typedef struct {
    enum tipo tipo;
} retorno_constante;

int last_call=0;

/*********** prototipos *************/

void unidad_traduccion(set folset);
void declaraciones(set folset);
retorno_especificador_tipo especificador_tipo(set folset);
void especificador_declaracion(set folset, parametros_especificador_declaracion params);
void definicion_funcion(set folset, parametros_definicion_funcion params);
void declaracion_variable(set folset, parametros_declaracion_variable params);
void lista_declaraciones_param(set folset, parametros_lista_declaraciones_param params);
void declaracion_parametro(set folset, parametros_declaracion_parametro params);
void declarador_init(set folset, parametros_declarador_init params);
void lista_declaraciones_init(set folset, parametros_lista_declaraciones_init params);
retorno_lista_inicializadores lista_inicializadores(set folset);
void lista_proposiciones(set folset, parametros_lista_proposiciones params);
void lista_declaraciones(set folset);
void declaracion(set folset);
void proposicion(set folset, parametros_proposicion params);
void proposicion_expresion(set folset);
void proposicion_compuesta(set folset, parametros_proposicion_compuesta params);
void proposicion_seleccion(set folset, parametros_proposicion_seleccion params);
void proposicion_iteracion(set folset, parametros_proposicion_iteracion params);
void proposicion_e_s(set folset);
void proposicion_retorno(set folset, parametros_proposicion_retorno params);
retorno_expresion expresion(set folset);
retorno_expresion_simple expresion_simple(set folset);
retorno_termino termino(set folset);
retorno_factor factor(set folset);
retorno_variable variable(set folset, parametros_variable);
retorno_llamada_funcion llamada_funcion(set folset, parametros_llamada_funcion);
void lista_expresiones(set folset, parametros_lista_expresiones);
retorno_constante constante(set folset);


#endif

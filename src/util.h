#ifndef UTIL_H
#define UTIL_H

#include "var_globales.h"
#include <stdio.h>

#include "ts.h"

#define T_VOID "void"
#define T_CHAR "char"
#define T_INT "int"
#define T_FLOAT "float"
#define T_ARREGLO "TIPOARREGLO"
#define T_ERROR "TIPOERROR"

enum boolean { FALSE, TRUE };

enum tipo { STRING = -3, ERROR = -2, VOID = -1, ARREGLO = 0, CHAR, INT, FLOAT };

enum tipo_pasaje { VALOR, REFERENCIA };

typedef struct parametro_en_ts {
    int puntero_tipo_dato;
    enum tipo_pasaje tipo_pasaje;
    int puntero_tipo_base;
} Parametro_en_TS;

typedef struct parametro_actual {
    enum tipo tipo_dato;
    enum tipo tipo_base;
    enum boolean es_clase_variable;
} Parametro_actual;

token *sbol;
extern FILE *yyin;

void scanner();

void init_parser(int, char **);

void match(set, int);

set lookahead();

set lookahead_in(set);

void test(set, set, int);

enum boolean es_tipo_base(enum tipo tipo);

enum tipo resolver_tipo(char *nombre);

int resolver_tipo_en_TS(enum tipo tipo);

enum boolean param1_es_coercionable_a_param2(enum tipo param1, enum tipo param2);

void lanzar_error_si_corresponde(enum tipo a);

enum tipo resolver_tipo_operador(enum tipo tipo_1, enum tipo tipo_2);

entrada_TS *nueva_entrada();

void insertar_parametro_en_funcion(int posicion_tabla_simbolos, Parametro_en_TS parametro_en_ts);

#endif

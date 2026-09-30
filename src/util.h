#include "var_globales.h"
#include <stdio.h>

#define T_VOID "void"
#define T_CHAR "char"
#define T_INT "int"
#define T_FLOAT "float"
#define T_ARREGLO "TIPOARREGLO"
#define T_ERROR "TIPOERROR"

enum boolean {FALSE, TRUE};
enum tipo {STRING = -3, ERROR = -2, VOID = -1, ARREGLO = 0, CHAR, INT, FLOAT};

token *sbol;
extern FILE *yyin;

void scanner();
void init_parser(int, char **);

void match(set, int);
set lookahead();
set lookahead_in(set);

void test(set, set, int);

enum boolean esTipoBase(enum tipo tipo);

enum tipo resolverTipo(char *nombre);
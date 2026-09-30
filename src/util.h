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
enum tipo_pasaje {VALOR, REFERENCIA};

typedef struct parametro {
    enum tipo tipo_dato;
    enum tipo_pasaje tipo_pasaje;
    enum tipo tipo_base;
    struct parametro  *siguiente;
} Parametro;

typedef struct {
    Parametro *primer_parametro;
    Parametro *ultimo_parametro;
    int cantidad;
}Lista_Parametros;

void iniciar_lista_parametros(Lista_Parametros *lista);

void agregar_parametro(Lista_Parametros *lista, enum tipo tipo_dato, enum tipo_pasaje tipo_pasaje, enum tipo tipo_base);

void limpiar_lista(Lista_Parametros *lista);

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

enum boolean param1_es_coercionable_a_param2(enum tipo param1, enum tipo param2);
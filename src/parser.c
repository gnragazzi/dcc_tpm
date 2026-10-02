#include "parser.h"


int main(int argc, char *argv[])
{
	init_parser(argc, argv);
	inic_tablas();

	unidad_traduccion(CEOF);

	match(CEOF, 9);

	last_call=1;

	error_handler(COD_IMP_ERRORES);

	return 0;
}


/********* funciones del parser ***********/

void unidad_traduccion(set folset)
{
	test((F_UNIDAD_TRADUCCION | folset), NADA, 40);

	while(lookahead_in(F_UNIDAD_TRADUCCION)) {
		declaraciones(folset | F_UNIDAD_TRADUCCION);
	}
}


void declaraciones(set folset)
{
	retorno_especificador_tipo especificador_tipo_1 = especificador_tipo(folset | CIDENT | F_ESPECIFICADOR_DECLARACION);

	match(CIDENT, 17);

	especificador_declaracion(folset);
}


retorno_especificador_tipo especificador_tipo(set folset)
{
	test(F_ESPECIFICADOR_TIPO, folset, 41);

	switch(lookahead())
	{
		case CVOID:
			scanner();
			break;

		case CCHAR:
			scanner();
			break;

		case CINT:
			scanner();
			break;

		case CFLOAT:
			scanner();
			break;
	}

	test(folset, NADA, 42);
}


void especificador_declaracion(set folset)
{
	test(F_ESPECIFICADOR_DECLARACION, folset, 43);

	switch(lookahead())
	{
		case CPAR_ABR:
			definicion_funcion(folset);
			break;

		case CASIGNAC:
		case CCOR_ABR:
		case CCOMA:
		case CPYCOMA:
			declaracion_variable(folset);
			break;
	}
}


void definicion_funcion(set folset)
{
	match(CPAR_ABR, 20);

	if(lookahead_in(F_LISTA_DECLARACIONES_PARAM))
		lista_declaraciones_param(folset | CPAR_CIE | F_PROPOSICION_COMPUESTA);

	match(CPAR_CIE, 21);

	proposicion_compuesta(folset);
}


void lista_declaraciones_param(set folset)
{
	declaracion_parametro(folset | CCOMA | F_DECLARACION_PARAMETRO);

	while(lookahead_in(CCOMA | F_DECLARACION_PARAMETRO))
	{
		if(lookahead_in(CCOMA))
			scanner();
		else
			error_handler(64);

		declaracion_parametro(folset | CCOMA | F_DECLARACION_PARAMETRO);
	}
}


void declaracion_parametro(set folset)
{
	retorno_especificador_tipo especificador_tipo_1 = especificador_tipo(folset | CAMPER | CIDENT | CCOR_ABR | CCOR_CIE);

	if(lookahead_in(CAMPER))
		scanner();

	match(CIDENT, 17);

	if(lookahead_in(CCOR_ABR))
	{
		scanner();
		match(CCOR_CIE, 22);
	}

	test(folset, NADA, 45);
}


void lista_declaraciones_init(set folset)
{
	test(F_LISTA_DECLARACIONES_INIT, folset, 46);

	match(CIDENT, 17);

	declarador_init(folset | CCOMA | F_LISTA_DECLARACIONES_INIT);

	while(lookahead_in(CCOMA | F_LISTA_DECLARACIONES_INIT))
	{
		match(CCOMA, 64);
		match(CIDENT, 17);
		declarador_init(folset | CCOMA | F_LISTA_DECLARACIONES_INIT);
	}
}


void declaracion_variable(set folset)
{
	declarador_init(folset | CCOMA | F_LISTA_DECLARACIONES_INIT | CPYCOMA);

	if(lookahead_in(CCOMA | F_LISTA_DECLARACIONES_INIT))
	{
		match(CCOMA, 64);
		lista_declaraciones_init(folset | CPYCOMA);
	}

	match(CPYCOMA, 23);

	test(folset, NADA, 51);
}


void declarador_init(set folset)
{
	test(F_DECLARADOR_INIT | folset, CCOR_CIE | CLLA_ABR | CLLA_CIE, 47);

	switch(lookahead())
	{
		case CASIGNAC:
			scanner();
			retorno_constante constante_1 = constante(folset);
			break;

		/* ] { } son puntos de reconfiguracion de esta alternativa: se entra por
		ellos y cada match anterior reporta el token obligatorio omitido */
		case CCOR_ABR:
		case CCOR_CIE:
		case CLLA_ABR:
		case CLLA_CIE:
			match(CCOR_ABR, 35);

			if(lookahead_in(CCONS_ENT))
				scanner();

			match(CCOR_CIE, 22);

			if(lookahead_in(CASIGNAC | CLLA_ABR | CLLA_CIE))
			{
				match(CASIGNAC, 66);
				match(CLLA_ABR, 24);
				retorno_lista_inicializadores lista_inicializadores_1 = lista_inicializadores(CLLA_CIE | folset);
				match(CLLA_CIE, 25);
			}
			break;
	}

	test(folset, NADA, 48);
}


retorno_lista_inicializadores lista_inicializadores(set folset)
{
	retorno_constante constante_1 = constante(folset | CCOMA | F_CONSTANTE);

	while(lookahead_in(CCOMA | F_CONSTANTE))
	{
		if(lookahead_in(CCOMA))
			scanner();
		else
			error_handler(64);

		retorno_constante constante_n = constante(folset | CCOMA | F_CONSTANTE);
	}
}


void proposicion_compuesta(set folset)
{
	test(F_PROPOSICION_COMPUESTA, folset | F_LISTA_DECLARACIONES | F_LISTA_PROPOSICIONES | CLLA_CIE, 49);

	if(lookahead_in(CLLA_ABR))
		scanner();

	if(lookahead_in(F_LISTA_DECLARACIONES))
		lista_declaraciones(folset | F_LISTA_PROPOSICIONES | CLLA_CIE);

	if(lookahead_in(F_LISTA_PROPOSICIONES)) {
		retorno_lista_proposiciones lista_proposiciones_1 = lista_proposiciones(folset | CLLA_CIE);
	}

	match(CLLA_CIE, 25);
	test(folset, NADA, 50);
}


void lista_declaraciones(set folset)
{
	declaracion(folset | F_DECLARACION);

	while(lookahead_in(F_DECLARACION))
	{
		declaracion(folset | F_DECLARACION);
	}
}


void declaracion(set folset)
{
	retorno_especificador_tipo especificador_tipo_1 = especificador_tipo(folset | F_LISTA_DECLARACIONES_INIT | CPYCOMA);

	lista_declaraciones_init(folset | CPYCOMA);

	match(CPYCOMA, 23);

	test(folset, NADA, 51);
}


retorno_lista_proposiciones lista_proposiciones(set folset)
{
	proposicion(folset | F_PROPOSICION);

	while(lookahead_in(F_PROPOSICION))
		proposicion(folset | F_PROPOSICION);
}


void proposicion(set folset)
{
	test(F_PROPOSICION, folset, 52);

	switch(lookahead())
	{
		case CLLA_ABR:
			proposicion_compuesta(folset);
			break;

		case CWHILE:
			proposicion_iteracion(folset);
			break;

		case CIF:
			proposicion_seleccion(folset);
			break;

		case CIN:
		case COUT:
			proposicion_e_s(folset);
			break;

		case CMAS:
		case CMENOS:
		case CIDENT:
		case CPAR_ABR:
		case CNEG:
		case CCONS_ENT:
		case CCONS_FLO:
		case CCONS_CAR:
		case CCONS_STR:
		case CPYCOMA:
			proposicion_expresion(folset);
			break;

		case CRETURN:
			proposicion_retorno(folset);
			break;
	}
}


void proposicion_iteracion(set folset)
{
	match(CWHILE, 27);

	match(CPAR_ABR, 20);

	retorno_expresion expresion_1 = expresion(folset | CPAR_CIE | F_PROPOSICION);

	match(CPAR_CIE, 21);

	proposicion(folset);
}


void proposicion_seleccion(set folset)
{
	match(CIF, 28);

	match(CPAR_ABR, 20);

	retorno_expresion expresion_1 = expresion(folset | CPAR_CIE | F_PROPOSICION | F_ELSE_OPCIONAL);

	match(CPAR_CIE, 21);

	proposicion(folset | F_ELSE_OPCIONAL | F_PROPOSICION);

	if(lookahead_in(F_ELSE_OPCIONAL))
	{
		scanner();
		proposicion(folset);
	}
}


void proposicion_e_s(set folset)
{
	switch(lookahead())
	{
		case CIN:
			scanner();

			match(CSHR, 30);

			retorno_variable variable_1 = variable(folset | F_RESTO_PROP_IN | F_VARIABLE | CPYCOMA);

			while(lookahead_in(F_RESTO_PROP_IN | F_VARIABLE))
			{
				match(CSHR, 30);
				retorno_variable variable_n = variable(folset | F_RESTO_PROP_IN | F_VARIABLE | CPYCOMA);
			}

			match(CPYCOMA, 23);

			break;

		case COUT:
			scanner();

			match(CSHL, 31);

			retorno_expresion expresion_1 = expresion(folset | F_RESTO_PROP_OUT | F_EXPRESION | CPYCOMA);

			while(lookahead_in(F_RESTO_PROP_OUT | F_EXPRESION))
			{
				match(CSHL, 31);
				retorno_expresion expresion_2 = expresion(folset | F_RESTO_PROP_OUT | F_EXPRESION | CPYCOMA);
			}

			match(CPYCOMA, 23);

			break;

		default:
			error_handler(29);
			break;
	}

	test(folset, NADA, 53);
}


void proposicion_retorno(set folset)
{
	scanner();

	retorno_expresion expresion_1 = expresion(folset | CPYCOMA);

	match(CPYCOMA, 23);

	test(folset, NADA, 54);
}


void proposicion_expresion(set folset)
{
	if(lookahead_in(F_EXPRESION)) {
		retorno_expresion expresion_1 = expresion(folset | CPYCOMA);
	}

	match(CPYCOMA, 23);

	test(folset, NADA, 55);
}


retorno_expresion expresion(set folset)
{
	retorno_expresion_simple expresion_simple_1 = expresion_simple(folset | F_RESTO_EXPRESION | F_EXPRESION_SIMPLE);

	while(lookahead_in(F_RESTO_EXPRESION))
	{
		switch(lookahead())
		{
			case CASIGNAC:
				scanner();
				retorno_expresion_simple expresion_simple_2 = expresion_simple(folset | F_RESTO_EXPRESION | F_EXPRESION_SIMPLE);
				break;

			case CDISTINTO:
			case CIGUAL:
			case CMENOR:
			case CMEIG:
			case CMAYOR:
			case CMAIG:
				scanner();
				retorno_expresion_simple expresion_simple_3 = expresion_simple(folset | F_RESTO_EXPRESION | F_EXPRESION_SIMPLE);
				break;
		}
	}
}


retorno_expresion_simple expresion_simple(set folset) {
	test(F_EXPRESION_SIMPLE, (folset | F_RESTO_EXPRESION_SIMPLE), 56);

	if (lookahead_in(F_OPERADOR_OPCIONAL))
		scanner();

	retorno_termino termino_1 = termino(folset | F_RESTO_EXPRESION_SIMPLE);

	while (lookahead_in(F_RESTO_EXPRESION_SIMPLE)) {
		scanner();
		retorno_termino termino_n = termino(folset | F_RESTO_EXPRESION_SIMPLE);
	}
}


retorno_termino termino(set folset)
{
	retorno_factor factor_1 = factor(folset | F_RESTO_TERMINO | F_FACTOR);

	while(lookahead_in(F_RESTO_TERMINO))
	{
		scanner();
		retorno_factor factor_n = factor(folset | F_RESTO_TERMINO | F_FACTOR);
	}
}


retorno_factor factor(set folset)
{
	test(F_FACTOR, folset, 57);

	switch(lookahead())
	{
		case CIDENT:
			/***************** Re-hacer *****************/
			if(sbol->lexema[0] == 'f') {
				retorno_llamada_funcion llamada_funcion_1 = llamada_funcion(folset);
			}
			else {
				retorno_variable variable_1 = variable(folset);
			}
			/********************************************/
			/* El alumno debera evaluar con consulta a TS
			si bifurca a variable o llamada a funcion */
			break;

		case CCONS_ENT:
		case CCONS_FLO:
		case CCONS_CAR:
			retorno_constante constante_1 = constante(folset);
			break;

		case CCONS_STR:
			scanner();
			break;

		case CPAR_ABR:
			scanner();
			retorno_expresion expresion_1 = expresion(folset | CPAR_CIE);
			match(CPAR_CIE, 21);
			break;

		case CNEG:
			scanner();
			retorno_expresion expresion_2 = expresion(folset);
			break;
	}

	test(folset, 0, 58);
}


retorno_variable variable(set folset)
{
	test(F_VARIABLE, folset | CCOR_ABR, 59);

	match(CIDENT, 17);

	/* El alumno debera verificar con una consulta a TS
	si, siendo la variable un arreglo, corresponde o no
	verificar la presencia del subindice */

	if(lookahead_in(CCOR_ABR))
	{
		scanner();
		retorno_expresion expresion_1 = expresion(folset | CCOR_CIE);
		match(CCOR_CIE, 22);
	}

	test(folset, NADA, 60);
}


retorno_llamada_funcion llamada_funcion(set folset)
{
	match(CIDENT, 17);

	match(CPAR_ABR, 20);

	if(lookahead_in(F_LISTA_EXPRESIONES)){
		retorno_lista_expresiones lista_expresiones_1 = lista_expresiones(folset | CPAR_CIE);
	}

	match(CPAR_CIE, 21);

	test(folset, NADA, 61);
}


retorno_lista_expresiones lista_expresiones(set folset)
{
	retorno_expresion expresion_1 = expresion(folset | CCOMA | F_EXPRESION);

	while(lookahead_in(CCOMA | F_EXPRESION))
	{
		match(CCOMA, 64);
		retorno_expresion expresion_n = expresion(folset | CCOMA | F_EXPRESION);
	}
}


retorno_constante constante(set folset)
{
	test(F_CONSTANTE, folset, 62);

	switch(lookahead())
	{
		case CCONS_ENT:
			scanner();
			break;

		case CCONS_FLO:
			scanner();
			break;

		case CCONS_CAR:
			scanner();
			break;
	}

	test(folset, 0, 63);
}

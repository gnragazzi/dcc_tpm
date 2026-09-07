#include "parser.h"


int main(int argc, char *argv[])
{
	init_parser(argc, argv);

	unidad_traduccion(CEOF);

	match(CEOF, 10);

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
	especificador_tipo(folset | CIDENT | F_ESPECIFICADOR_DECLARACION);

	match(CIDENT, 17);

	especificador_declaracion(folset);
}


void especificador_tipo(set folset)
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

		default:
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

		default:
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
	especificador_tipo(folset | CAMPER | CIDENT);

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
	match(CIDENT, 10);

	declarador_init(PLACEHOLDER);

	while(lookahead_in(CCOMA))
	{
		scanner();
		match(CIDENT, 10);
		declarador_init(PLACEHOLDER);
	}
}


void declaracion_variable(set folset)
{
	declarador_init(PLACEHOLDER);

	if(lookahead_in(CCOMA))
	{
		scanner();
		lista_declaraciones_init(PLACEHOLDER);
	}

	match(CPYCOMA, 10);
}


void declarador_init(set folset)
{
	switch(lookahead())
	{
		case CASIGNAC:
			scanner();
			constante(PLACEHOLDER);
			break;

		case CCOR_ABR:
			scanner();

			if(lookahead_in(CCONS_ENT))
				constante(PLACEHOLDER);

			match(CCOR_CIE, 10);

			if(lookahead_in(CASIGNAC))
			{
				scanner();
				match(CLLA_ABR, 10);
				lista_inicializadores(PLACEHOLDER);
				match(CLLA_CIE, 10);
			}
			break;
	}
}


void lista_inicializadores(set folset)
{
	constante(folset | CCOMA | F_CONSTANTE);

	while(lookahead_in(CCOMA | F_CONSTANTE))
	{
		if(lookahead_in(CCOMA))
			scanner();
		else
			error_handler(64);

		constante(folset | CCOMA | F_CONSTANTE);
	}
}


void proposicion_compuesta(set folset)
{
	test(F_PROPOSICION_COMPUESTA, folset | F_LISTA_DECLARACIONES | F_LISTA_PROPOSICIONES, 49);
	match(CLLA_ABR, 24);

	if(lookahead_in(F_LISTA_DECLARACIONES))
		lista_declaraciones(folset | F_LISTA_PROPOSICIONES | CLLA_CIE);

	if(lookahead_in(F_LISTA_PROPOSICIONES))
		lista_proposiciones(folset | CLLA_CIE);

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
	especificador_tipo(folset | F_LISTA_DECLARACIONES_INIT | CPYCOMA);

	lista_declaraciones_init(folset | CPYCOMA);

	match(CPYCOMA, 23);

	test(folset, NADA, 51);
}


void lista_proposiciones(set folset)
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

		default:
			break;
	}
}


void proposicion_iteracion(set folset)
{
	match(CWHILE, 27);

	match(CPAR_ABR, 20);

	expresion(folset | CPAR_CIE | F_PROPOSICION);

	match(CPAR_CIE, 21);

	proposicion(folset);
}


void proposicion_seleccion(set folset)
{
	match(CIF, 28);

	match(CPAR_ABR, 20);

	expresion(folset | CPAR_CIE | F_PROPOSICION | F_ELSE_OPCIONAL);

	match(CPAR_CIE, 21);

	proposicion(folset | F_ELSE_OPCIONAL);

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

			variable(folset | CSHR | F_VARIABLE | CPYCOMA);

			while(lookahead_in(CSHR | F_VARIABLE))
			{
				match(CSHR, 30);
				variable(folset | CSHR | F_VARIABLE | CPYCOMA);
			}

			match(CPYCOMA, 23);

			break;

		case COUT:
			scanner();

			match(CSHL, 31);

			expresion(folset | CSHL | F_EXPRESION | CPYCOMA);

			while(lookahead_in(CSHL | F_EXPRESION))
			{
				match(CSHL, 31);
				expresion(folset | CSHL | F_EXPRESION | CPYCOMA);
			}

			match(CPYCOMA, 23);

			break;

		default:
			error_handler(29);
	}

	test(folset, 0, 53);
}


void proposicion_retorno(set folset)
{
	scanner();

	expresion(folset | CPYCOMA);

	match(CPYCOMA, 23);

	test(folset, 0, 54);
}


void proposicion_expresion(set folset)
{
	if(lookahead_in(F_EXPRESION))
		expresion(folset | CPYCOMA);

	match(CPYCOMA, 23);

	test(folset, 0, 55);
}


void expresion(set folset)
{
	expresion_simple(folset | F_RESTO_EXPRESION);

	while(lookahead_in(F_RESTO_EXPRESION))
	{
		switch(lookahead())
		{
			case CASIGNAC:
				scanner();
				expresion_simple(folset | F_RESTO_EXPRESION);
				break;

			case CDISTINTO:
			case CIGUAL:
			case CMENOR:
			case CMEIG:
			case CMAYOR:
			case CMAIG:
				scanner();
				expresion_simple(folset | F_RESTO_EXPRESION);
				break;
		}
	}
}


void expresion_simple(set folset) {
	test(F_EXPRESION_SIMPLE, (folset | F_RESTO_EXPRESION_SIMPLE), 56);

	if (!lookahead_in(F_EXPRESION_SIMPLE | F_RESTO_EXPRESION_SIMPLE))
		return;

	if (lookahead_in(F_EXPRESION_SIMPLE)) {
		if (lookahead_in(F_OPERADOR_OPCIONAL))
			scanner();
		termino(folset | F_RESTO_EXPRESION_SIMPLE);
	} else {
		scanner();
		termino(folset | F_RESTO_EXPRESION_SIMPLE);
	}


	while (lookahead_in(F_RESTO_EXPRESION_SIMPLE)) {
		scanner();
		termino(folset | F_RESTO_EXPRESION_SIMPLE);
	}
}


void termino(set folset)
{
	factor(folset | F_RESTO_TERMINO);

	while(lookahead_in(F_RESTO_TERMINO))
	{
		scanner();
		factor(folset | F_RESTO_TERMINO);
	}
}


void factor(set folset)
{
	test(F_FACTOR, folset, 57);

	switch(lookahead())
	{
		case CIDENT:
			/***************** Re-hacer *****************/
			if(sbol->lexema[0] == 'f')
				llamada_funcion(folset);
			else
				variable(folset);
			/********************************************/
			/* El alumno debera evaluar con consulta a TS
			si bifurca a variable o llamada a funcion */
			break;

		case CCONS_ENT:
		case CCONS_FLO:
		case CCONS_CAR:
			constante(folset);
			break;

		case CCONS_STR:
			scanner();
			break;

		case CPAR_ABR:
			scanner();
			expresion(folset | CPAR_CIE);
			match(CPAR_CIE, 21);
			break;

		case CNEG:
			scanner();
			expresion(folset);
			break;

		default:
			break;
	}

	test(folset, 0, 58);
}


void variable(set folset)
{
	test(F_VARIABLE, folset | CCOR_ABR, 59);

	if(lookahead_in(CIDENT))
		scanner();

	/* El alumno debera verificar con una consulta a TS
	si, siendo la variable un arreglo, corresponde o no
	verificar la presencia del subindice */

	if(lookahead_in(CCOR_ABR))
	{
		scanner();
		expresion(folset | CCOR_CIE);
		match(CCOR_CIE, 22);
	}

	test(folset, NADA, 60);
}


void llamada_funcion(set folset)
{
	match(CIDENT, 17);

	match(CPAR_ABR, 20);

	if(lookahead_in(F_LISTA_EXPRESIONES))
		lista_expresiones(folset | CPAR_CIE);

	match(CPAR_CIE, 21);

	test(folset, NADA, 61);
}


void lista_expresiones(set folset)
{
	expresion(folset | CCOMA | F_EXPRESION);

	while(lookahead_in(CCOMA | F_EXPRESION))
	{
		match(CCOMA, 64);
		expresion(folset | CCOMA | F_EXPRESION);
	}
}


void constante(set folset)
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

		default:
			break;
	}

	test(folset, 0, 63);
}

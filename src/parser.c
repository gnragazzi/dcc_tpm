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
	while(lookahead_in(CVOID | CCHAR | CINT | CFLOAT))
		declaraciones(PLACEHOLDER);
}


void declaraciones(set folset)
{
	especificador_tipo(PLACEHOLDER);

	match(CIDENT, 10);

	especificador_declaracion(PLACEHOLDER);
}


void especificador_tipo(set folset)
{
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
			error_handler(10);
	}
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
	declaracion_parametro(PLACEHOLDER);

	while(lookahead_in(CCOMA))
	{
		scanner();
		declaracion_parametro(PLACEHOLDER);
	}
}


void declaracion_parametro(set folset)
{
	especificador_tipo(PLACEHOLDER);

	if(lookahead_in(CAMPER))
		scanner();

	match(CIDENT, 10);

	if(lookahead_in(CCOR_ABR))
	{
		scanner();
		match(CCOR_CIE, 10);
	}
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
	constante(PLACEHOLDER);

	while(lookahead_in(CCOMA))
	{
		scanner();
		constante(PLACEHOLDER);
	}
}


void proposicion_compuesta(set folset)
{
	match(CLLA_ABR, 10);

	if(lookahead_in(CVOID | CCHAR | CINT | CFLOAT))
		lista_declaraciones(PLACEHOLDER);

	if(lookahead_in(CLLA_ABR | CMAS | CMENOS | CIDENT | CPAR_ABR | CNEG |
					 CCONS_ENT | CCONS_FLO | CCONS_CAR | CCONS_STR |
					 CIF | CWHILE | CIN | COUT | CPYCOMA | CRETURN))
		lista_proposiciones(PLACEHOLDER);

	match(CLLA_CIE, 10);
}


void lista_declaraciones(set folset)
{
	declaracion(PLACEHOLDER);

	while(lookahead_in(CVOID | CCHAR | CINT | CFLOAT))
		declaracion(PLACEHOLDER);
}


void declaracion(set folset)
{
	especificador_tipo(PLACEHOLDER);

	lista_declaraciones_init(PLACEHOLDER);

	match(CPYCOMA, 10);
}


void lista_proposiciones(set folset)
{
	proposicion(PLACEHOLDER);

	while(lookahead_in(CLLA_ABR | CMAS | CMENOS | CIDENT | CPAR_ABR | CNEG |
						 CCONS_ENT | CCONS_FLO | CCONS_CAR | CCONS_STR |
						 CIF | CWHILE | CIN | COUT | CPYCOMA | CRETURN))
		proposicion(PLACEHOLDER);
}


void proposicion(set folset)
{
	switch(lookahead())
	{
		case CLLA_ABR:
			proposicion_compuesta(PLACEHOLDER);
			break;

		case CWHILE:
			proposicion_iteracion(PLACEHOLDER);
			break;

		case CIF:
			proposicion_seleccion(PLACEHOLDER);
			break;

		case CIN:
		case COUT:
			proposicion_e_s(PLACEHOLDER);
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
			proposicion_expresion(PLACEHOLDER);
			break;

		case CRETURN:
			proposicion_retorno(PLACEHOLDER);
			break;

		default:
			error_handler(10);
	}
}


void proposicion_iteracion(set folset)
{
	match(CWHILE, 10);

	match(CPAR_ABR, 10);

	expresion(PLACEHOLDER);

	match(CPAR_CIE, 10);

	proposicion(PLACEHOLDER);
}


void proposicion_seleccion(set folset)
{
	match(CIF, 10);

	match(CPAR_ABR, 10);

	expresion(PLACEHOLDER);

	match(CPAR_CIE, 10);

	proposicion(PLACEHOLDER);

	if(lookahead_in(CELSE))
	{
		scanner();
		proposicion(PLACEHOLDER);
	}
}


void proposicion_e_s(set folset)
{
	switch(lookahead())
	{
		case CIN:
			scanner();

			match(CSHR, 10);

			variable(PLACEHOLDER);

			while(lookahead_in(CSHR))
			{
				scanner();
				variable(PLACEHOLDER);
			}

			match(CPYCOMA, 10);

			break;

		case COUT:
			scanner();

			match(CSHL, 10);

			expresion(PLACEHOLDER);

			while(lookahead_in(CSHL))
			{
				scanner();
				expresion(PLACEHOLDER);
			}

			match(CPYCOMA, 10);

			break;

		default:
			error_handler(10);
	}
}


void proposicion_retorno(set folset)
{
	scanner();

	expresion(PLACEHOLDER);

	match(CPYCOMA, 10);
}


void proposicion_expresion(set folset)
{
	if(lookahead_in(CMAS | CMENOS | CIDENT | CPAR_ABR | CNEG | CCONS_ENT | CCONS_FLO | CCONS_CAR | CCONS_STR))
		expresion(PLACEHOLDER);

	match(CPYCOMA, 10);
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


void expresion_simple(set folset)
{
	test(F_EXPRESION_SIMPLE, (folset | F_RESTO_EXPRESION_SIMPLE), 56);

	if(lookahead_in(F_OPERADOR_OPCIONAL))
		scanner();

	termino(folset | F_RESTO_EXPRESION_SIMPLE);

	while(lookahead_in(F_RESTO_EXPRESION_SIMPLE))
	{
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
	switch(lookahead())
	{
		case CIDENT:
			/***************** Re-hacer *****************/
			if(sbol->lexema[0] == 'f')
				llamada_funcion(PLACEHOLDER);
			else
				variable(PLACEHOLDER);
			/********************************************/
			/* El alumno debera evaluar con consulta a TS
			si bifurca a variable o llamada a funcion */
			break;

		case CCONS_ENT:
		case CCONS_FLO:
		case CCONS_CAR:
			constante(PLACEHOLDER);
			break;

		case CCONS_STR:
			scanner();
			break;

		case CPAR_ABR:
			scanner();
			expresion(PLACEHOLDER);
			match(CPAR_CIE, 10);
			break;

		case CNEG:
			scanner();
			expresion(PLACEHOLDER);
			break;

		default:
			error_handler(10);
	}
}


void variable(set folset)
{
	match(CIDENT, 10);

	/* El alumno debera verificar con una consulta a TS
	si, siendo la variable un arreglo, corresponde o no
	verificar la presencia del subindice */

	if(lookahead_in(CCOR_ABR))
	{
		scanner();
		expresion(PLACEHOLDER);
		match(CCOR_CIE, 10);
	}
}


void llamada_funcion(set folset)
{
	match(CIDENT, 10);

	match(CPAR_ABR, 10);

	if(lookahead_in(CMAS | CMENOS | CIDENT | CPAR_ABR | CNEG | CCONS_ENT | CCONS_FLO | CCONS_CAR | CCONS_STR))
		lista_expresiones(PLACEHOLDER);

	match(CPAR_CIE, 10);
}


void lista_expresiones(set folset)
{
	expresion(PLACEHOLDER);

	while(lookahead_in(CCOMA))
	{
		scanner();
		expresion(PLACEHOLDER);
	}
}


void constante(set folset)
{
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
			error_handler(10);
	}
}

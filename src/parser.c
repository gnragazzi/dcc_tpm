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
	pushTB();
	test((F_UNIDAD_TRADUCCION | folset), NADA, 40);

	while(lookahead_in(F_UNIDAD_TRADUCCION)) {
		declaraciones(folset | F_UNIDAD_TRADUCCION);
	}

	pop_nivel();
}


void declaraciones(set folset) {
	parametros_especificador_declaracion parametros_especificador_declaracion;

	retorno_especificador_tipo especificador_tipo_1 = especificador_tipo(folset | CIDENT | F_ESPECIFICADOR_DECLARACION);
	parametros_especificador_declaracion.tipo_declaracion = especificador_tipo_1.tipo;

	if (lookahead() & CIDENT) {
		parametros_especificador_declaracion.identificador = (char *) malloc(sizeof(char) * TAM_LEXEMA);
		strcpy(parametros_especificador_declaracion.identificador, token1.lexema);
		scanner();
	} else {
		parametros_especificador_declaracion.identificador = NULL;
		error_handler(17);
	}

	especificador_declaracion(folset, parametros_especificador_declaracion);
	if (parametros_especificador_declaracion.identificador != NULL)
		free(parametros_especificador_declaracion.identificador);
}


retorno_especificador_tipo especificador_tipo(set folset)
{
	retorno_especificador_tipo retorno_especificador_tipo;
	test(F_ESPECIFICADOR_TIPO, folset, 41);

	switch(lookahead())
	{
		case CVOID:
			retorno_especificador_tipo.tipo = VOID;
			scanner();
			break;

		case CCHAR:
			retorno_especificador_tipo.tipo = CHAR;
			scanner();
			break;

		case CINT:
			retorno_especificador_tipo.tipo = INT;
			scanner();
			break;

		case CFLOAT:
			retorno_especificador_tipo.tipo = FLOAT;
			scanner();
			break;
	}

	test(folset, NADA, 42);
	return retorno_especificador_tipo;
}


void especificador_declaracion(set folset, parametros_especificador_declaracion params) {
	test(F_ESPECIFICADOR_DECLARACION, folset, 43);

	switch (lookahead()) {
		case CPAR_ABR: {
			parametros_definicion_funcion parametros_definicion_funcion;
			parametros_definicion_funcion.tipo_retorno = params.tipo_declaracion;
			parametros_definicion_funcion.posicion_tabla_simbolos = NIL;

			if (params.identificador != NULL) {
				entrada_TS *entrada_nueva_funcion = nueva_entrada();
				strcpy(entrada_nueva_funcion->nbre, params.identificador);
				entrada_nueva_funcion->clase = CLASFUNC;
				entrada_nueva_funcion->ptr_tipo = resolver_tipo_en_TS(params.tipo_declaracion);

				parametros_definicion_funcion.posicion_tabla_simbolos = insertarTS();
			}

			definicion_funcion(folset, parametros_definicion_funcion);
			break;
		}
		case CASIGNAC:
		case CCOR_ABR:
		case CCOMA:
		case CPYCOMA: {
			parametros_declaracion_variable parametros_declaracion_variable;
			parametros_declaracion_variable.identificador = params.identificador;
			parametros_declaracion_variable.tipo_declaracion = params.tipo_declaracion;

			declaracion_variable(folset, parametros_declaracion_variable);
			break;
		}
	}
}


void definicion_funcion(set folset, parametros_definicion_funcion params)
{
	enum tipo tipo_retorno = params.tipo_retorno;
	enum boolean tiene_retorno = FALSE;

	pushTB();

	int posicion_tabla_simbolos = params.posicion_tabla_simbolos;
	parametros_proposicion_compuesta parametros_proposicion_compuesta;

	parametros_proposicion_compuesta.tipo_retorno = tipo_retorno;
	parametros_proposicion_compuesta.tiene_retorno = &tiene_retorno;

	match(CPAR_ABR, 20);

	if(lookahead_in(F_LISTA_DECLARACIONES_PARAM)) {
		parametros_lista_declaraciones_param parametros_lista_declaraciones_param;
		parametros_lista_declaraciones_param.posicion_tabla_simbolos = posicion_tabla_simbolos;

		lista_declaraciones_param(folset | CPAR_CIE | F_PROPOSICION_COMPUESTA, parametros_lista_declaraciones_param);
	}

	match(CPAR_CIE, 21);

	proposicion_compuesta(folset, parametros_proposicion_compuesta);
}


void lista_declaraciones_param(set folset, parametros_lista_declaraciones_param params)
{
	int posicion_tabla_simbolos = params.posicion_tabla_simbolos;

	parametros_declaracion_parametro parametros_declaracion_parametro;
	parametros_declaracion_parametro.posicion_tabla_simbolos = posicion_tabla_simbolos;

	declaracion_parametro(folset | CCOMA | F_DECLARACION_PARAMETRO, parametros_declaracion_parametro);

	while(lookahead_in(CCOMA | F_DECLARACION_PARAMETRO))
	{
		if(lookahead_in(CCOMA))
			scanner();
		else
			error_handler(64);

		declaracion_parametro(folset | CCOMA | F_DECLARACION_PARAMETRO, parametros_declaracion_parametro);
	}
}


void declaracion_parametro(set folset, parametros_declaracion_parametro params) {
	int posicion_tabla_simbolos = params.posicion_tabla_simbolos;
	retorno_especificador_tipo especificador_tipo_1 = especificador_tipo(folset | CAMPER | CIDENT | CCOR_ABR | CCOR_CIE);
	enum tipo parametro_tipo = especificador_tipo_1.tipo;

	if (parametro_tipo == VOID) {
		parametro_tipo = ERROR;
		error_handler(73);
	}

	entrada_TS *nueva_variable = nueva_entrada();
	char *identificador;
	enum tipo_pasaje tipo_pasaje = VALOR;

	if (lookahead_in(CAMPER)) {
		tipo_pasaje = REFERENCIA;
		scanner();
	}

	if (lookahead() & CIDENT) {
		identificador = (char *) malloc(sizeof(char) * TAM_LEXEMA);
		strcpy(identificador, token1.lexema);
		scanner();
	} else {
		identificador = NULL;
		error_handler(17);
	}


	if (lookahead_in(CCOR_ABR)) {
		scanner();
		match(CCOR_CIE, 22);

		if (tipo_pasaje == REFERENCIA) {
			error_handler(92);
		}

		if (identificador != NULL) {
			strcpy(nueva_variable->nbre, identificador);
			nueva_variable->clase = CLASPAR;
			nueva_variable->ptr_tipo = resolver_tipo_en_TS(ARREGLO);
			nueva_variable->desc.part_var.param.ptero_tipo_base = resolver_tipo_en_TS(parametro_tipo);
			nueva_variable->desc.part_var.param.tipo_pje = VALOR;

			insertarTS();
		}
	} else {
		if (identificador != NULL) {
			strcpy(nueva_variable->nbre, identificador);
			nueva_variable->clase = CLASPAR;
			nueva_variable->ptr_tipo = resolver_tipo_en_TS(parametro_tipo);
			nueva_variable->desc.part_var.param.tipo_pje = tipo_pasaje;

			insertarTS();
		}
	}

	test(folset, NADA, 45);

	if (identificador != NULL)
		free(identificador);
}


void lista_declaraciones_init(set folset, parametros_lista_declaraciones_init params) {
	parametros_declarador_init parametros_declarador_init;
	parametros_declarador_init.tipo_declaracion = params.tipo_declaracion;

	test(F_LISTA_DECLARACIONES_INIT, folset, 46);

	if (lookahead() & CIDENT) {
		parametros_declarador_init.identificador = (char *) malloc(sizeof(char) * TAM_LEXEMA);
		strcpy(parametros_declarador_init.identificador, token1.lexema);
		scanner();
	} else {
		parametros_declarador_init.identificador = NULL;
		error_handler(17);
	}

	declarador_init(folset | CCOMA | F_LISTA_DECLARACIONES_INIT, parametros_declarador_init);

	while (lookahead_in(CCOMA | F_LISTA_DECLARACIONES_INIT)) {
		match(CCOMA, 64);

		if (lookahead() & CIDENT) {
			parametros_declarador_init.identificador = (char *) malloc(sizeof(char) * TAM_LEXEMA);
			strcpy(parametros_declarador_init.identificador, token1.lexema);

			scanner();
		} else {
			parametros_declarador_init.identificador = NULL;
			error_handler(17);
		}

		declarador_init(folset | CCOMA | F_LISTA_DECLARACIONES_INIT, parametros_declarador_init);
		if (parametros_declarador_init.identificador != NULL) {
			free((void *)parametros_declarador_init.identificador);
			parametros_declarador_init.identificador = NULL;
		}
	}
	if (parametros_declarador_init.identificador != NULL)
		free(parametros_declarador_init.identificador);
}


void declaracion_variable(set folset, parametros_declaracion_variable params) {
	parametros_declarador_init parametros_declarador_init;
	parametros_lista_declaraciones_init parametros_lista_declaraciones_init;

	enum tipo variable_tipo = params.tipo_declaracion;

	if (variable_tipo == VOID) {
		variable_tipo = ERROR;
		error_handler(73);
	}


	parametros_lista_declaraciones_init.tipo_declaracion =
			parametros_declarador_init.tipo_declaracion = variable_tipo;

	parametros_declarador_init.identificador = params.identificador;

	declarador_init(folset | CCOMA | F_LISTA_DECLARACIONES_INIT | CPYCOMA, parametros_declarador_init);

	if (lookahead_in(CCOMA | F_LISTA_DECLARACIONES_INIT)) {
		match(CCOMA, 64);
		lista_declaraciones_init(folset | CPYCOMA, parametros_lista_declaraciones_init);
	}

	match(CPYCOMA, 23);

	test(folset, NADA, 51);
}


void declarador_init(set folset, parametros_declarador_init params) {
	test(F_DECLARADOR_INIT | folset, CCOR_CIE | CLLA_ABR | CLLA_CIE, 47);
	entrada_TS *entrada_nueva_variable = nueva_entrada();
	entrada_nueva_variable->clase = CLASVAR;

	switch (lookahead()) {
		case CASIGNAC:
			scanner();
			entrada_nueva_variable->ptr_tipo = resolver_tipo_en_TS(params.tipo_declaracion);
			retorno_constante constante_1 = constante(folset);
			break;

		/* ] { } son puntos de reconfiguracion de esta alternativa: se entra por
		ellos y cada match anterior reporta el token obligatorio omitido */
		case CCOR_ABR:
		case CCOR_CIE:
		case CLLA_ABR:
		case CLLA_CIE:
			entrada_nueva_variable->ptr_tipo = resolver_tipo_en_TS(ARREGLO);
			entrada_nueva_variable->desc.part_var.arr.ptero_tipo_base = resolver_tipo_en_TS(params.tipo_declaracion);
			match(CCOR_ABR, 35);

			if (lookahead_in(CCONS_ENT))
				scanner();

			match(CCOR_CIE, 22);

			if (lookahead_in(CASIGNAC | CLLA_ABR | CLLA_CIE)) {
				match(CASIGNAC, 66);
				match(CLLA_ABR, 24);
				retorno_lista_inicializadores lista_inicializadores_1 = lista_inicializadores(CLLA_CIE | folset);
				match(CLLA_CIE, 25);
			}
			break;
		default:
			entrada_nueva_variable->ptr_tipo = resolver_tipo_en_TS(params.tipo_declaracion);
	}

	if (params.identificador != NULL) {
		strcpy(entrada_nueva_variable->nbre, params.identificador);
		insertarTS();
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


void proposicion_compuesta(set folset, parametros_proposicion_compuesta params)
{
	enum tipo tipo_retorno = params.tipo_retorno;
	enum boolean *tiene_retorno = params.tiene_retorno;

	test(F_PROPOSICION_COMPUESTA, folset | F_LISTA_DECLARACIONES | F_LISTA_PROPOSICIONES | CLLA_CIE, 49);

	if(lookahead_in(CLLA_ABR))
		scanner();

	if(lookahead_in(F_LISTA_DECLARACIONES))
		lista_declaraciones(folset | F_LISTA_PROPOSICIONES | CLLA_CIE);

	if(lookahead_in(F_LISTA_PROPOSICIONES)) {
		parametros_lista_proposiciones parametros_lista_proposiciones;
		parametros_lista_proposiciones.tipo_retorno = tipo_retorno;
		parametros_lista_proposiciones.tiene_retorno = tiene_retorno;

		lista_proposiciones(folset | CLLA_CIE, parametros_lista_proposiciones);
	}

	match(CLLA_CIE, 25);
	test(folset, NADA, 50);
	pop_nivel();
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
	parametros_lista_declaraciones_init parametros_lista_declaraciones_init;

	retorno_especificador_tipo especificador_tipo_1 = especificador_tipo(folset | F_LISTA_DECLARACIONES_INIT | CPYCOMA);

	enum tipo variable_tipo = especificador_tipo_1.tipo;

	if (variable_tipo == VOID) {
		variable_tipo = ERROR;
		error_handler(73);
	}

	parametros_lista_declaraciones_init.tipo_declaracion = variable_tipo;

	lista_declaraciones_init(folset | CPYCOMA, parametros_lista_declaraciones_init);

	match(CPYCOMA, 23);

	test(folset, NADA, 51);
}


void lista_proposiciones(set folset, parametros_lista_proposiciones params) {
	enum tipo tipo_retorno = params.tipo_retorno;
	enum boolean *tiene_retorno = params.tiene_retorno;

	parametros_proposicion parametros_proposicion;

	parametros_proposicion.tipo_retorno = tipo_retorno;
	parametros_proposicion.tiene_retorno = tiene_retorno;

	proposicion(folset | F_PROPOSICION, parametros_proposicion);

	while(lookahead_in(F_PROPOSICION)) {
		proposicion(folset | F_PROPOSICION, parametros_proposicion);
	}
}


void proposicion(set folset, parametros_proposicion params) {
	enum tipo tipo_retorno = params.tipo_retorno;
	enum boolean *tiene_retorno = params.tiene_retorno;

	test(F_PROPOSICION, folset, 52);

	switch(lookahead())
	{
		case CLLA_ABR:
			pushTB();

			parametros_proposicion_compuesta parametros_proposicion_compuesta;
			parametros_proposicion_compuesta.tipo_retorno = tipo_retorno;
			parametros_proposicion_compuesta.tiene_retorno = tiene_retorno;

			proposicion_compuesta(folset, parametros_proposicion_compuesta);
			break;

		case CWHILE: {
			parametros_proposicion_iteracion parametros_proposicion_iteracion;
			parametros_proposicion_iteracion.tipo_retorno = tipo_retorno;
			parametros_proposicion_iteracion.tiene_retorno = tiene_retorno;

			proposicion_iteracion(folset, parametros_proposicion_iteracion);
			break;
		}

		case CIF:
			parametros_proposicion_seleccion parametros_proposicion_seleccion;
			parametros_proposicion_seleccion.tipo_retorno = tipo_retorno;
			parametros_proposicion_seleccion.tiene_retorno = tiene_retorno;

			proposicion_seleccion(folset, parametros_proposicion_seleccion);
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
			*tiene_retorno = TRUE;

			parametros_proposicion_retorno parametros_proposicion_retorno;
			parametros_proposicion_retorno.tipo_retorno = tipo_retorno;

			proposicion_retorno(folset, parametros_proposicion_retorno);
			break;
	}
}


void proposicion_iteracion(set folset, parametros_proposicion_iteracion params)
{
	enum tipo tipo_retorno = params.tipo_retorno;
	enum boolean *tiene_retorno = params.tiene_retorno;

	parametros_proposicion parametros_proposicion;
	parametros_proposicion.tipo_retorno = tipo_retorno;
	parametros_proposicion.tiene_retorno = tiene_retorno;

	match(CWHILE, 27);

	match(CPAR_ABR, 20);

	retorno_expresion expresion_1 = expresion(folset | CPAR_CIE | F_PROPOSICION);

	match(CPAR_CIE, 21);

	proposicion(folset, parametros_proposicion);
}


void proposicion_seleccion(set folset, parametros_proposicion_seleccion params)
{
	enum tipo tipo_retorno = params.tipo_retorno;
	enum boolean *tiene_retorno = params.tiene_retorno;

	parametros_proposicion parametros_proposicion;
	parametros_proposicion.tipo_retorno = tipo_retorno;
	parametros_proposicion.tiene_retorno = tiene_retorno;

	match(CIF, 28);

	match(CPAR_ABR, 20);

	retorno_expresion expresion_1 = expresion(folset | CPAR_CIE | F_PROPOSICION | F_ELSE_OPCIONAL);

	match(CPAR_CIE, 21);

	proposicion(folset | F_ELSE_OPCIONAL | F_PROPOSICION, parametros_proposicion);

	if(lookahead_in(F_ELSE_OPCIONAL))
	{
		scanner();
		proposicion(folset, parametros_proposicion);
	}
}


void proposicion_e_s(set folset)
{
	switch(lookahead())
	{
		case CIN:
			parametros_variable parametros_variable;
			scanner();

			match(CSHR, 30);

			retorno_variable variable_1 = variable(folset | F_RESTO_PROP_IN | F_VARIABLE | CPYCOMA, parametros_variable);

			while(lookahead_in(F_RESTO_PROP_IN | F_VARIABLE))
			{
				match(CSHR, 30);
				retorno_variable variable_n = variable(folset | F_RESTO_PROP_IN | F_VARIABLE | CPYCOMA, parametros_variable);
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


void proposicion_retorno(set folset, parametros_proposicion_retorno params)
{
	enum tipo tipo_retorno = params.tipo_retorno;

	scanner();

	retorno_expresion expresion_1 = expresion(folset | CPYCOMA);

	match(CPYCOMA, 23);

	test(folset, NADA, 54);
}


void proposicion_expresion(set folset)
{
	if(lookahead_in(F_EXPRESION)) {
		retorno_expresion expresion_1 = expresion(folset | CPYCOMA);
		int a;
	}

	match(CPYCOMA, 23);

	test(folset, NADA, 55);
}


retorno_expresion expresion(set folset)
{
	retorno_expresion retorno_expresion;
	retorno_expresion_simple expresion_simple_1 = expresion_simple(folset | F_RESTO_EXPRESION | F_EXPRESION_SIMPLE);

	enum tipo tipo_izquierda_asignacion = retorno_expresion.tipo = expresion_simple_1.tipo;
	enum boolean clase_izquierda_asignacion_es_variable =
			retorno_expresion.es_clase_variable = expresion_simple_1.es_clase_variable;

	if (expresion_simple_1.tipo == ARREGLO) {
		error_handler(81);
	}

	while(lookahead_in(F_RESTO_EXPRESION))
	{
		switch(lookahead())
		{
			case CASIGNAC: {
				if (!clase_izquierda_asignacion_es_variable) {
					error_handler(82);
				}
				scanner();
				retorno_expresion_simple expresion_simple_2 = expresion_simple(folset | F_RESTO_EXPRESION | F_EXPRESION_SIMPLE);
				clase_izquierda_asignacion_es_variable = expresion_simple_2.es_clase_variable;
				tipo_izquierda_asignacion = expresion_simple_2.tipo;

				if (expresion_simple_2.tipo == ARREGLO) {
					error_handler(81);
				}

				break;
			}
			case CDISTINTO:
			case CIGUAL:
			case CMENOR:
			case CMEIG:
			case CMAYOR:
			case CMAIG: {
				scanner();
				retorno_expresion_simple expresion_simple_3 = expresion_simple(folset | F_RESTO_EXPRESION | F_EXPRESION_SIMPLE);
				clase_izquierda_asignacion_es_variable = FALSE;
				tipo_izquierda_asignacion = expresion_simple_3.tipo;
				retorno_expresion.tipo = resolver_tipo_operador(retorno_expresion.tipo, expresion_simple_3.tipo);

				break;
			}
		}
	}

	return retorno_expresion;
}


retorno_expresion_simple expresion_simple(set folset) {
	enum boolean hubo_operador_previo = FALSE;
	retorno_expresion_simple retorno_expresion_simple;

	test(F_EXPRESION_SIMPLE, (folset | F_RESTO_EXPRESION_SIMPLE), 56);

	if (lookahead_in(F_OPERADOR_OPCIONAL)) {
		hubo_operador_previo = TRUE;
		scanner();
	}

	retorno_termino termino_1 = termino(folset | F_RESTO_EXPRESION_SIMPLE);

	if (hubo_operador_previo && termino_1.tipo == STRING) {
		error_handler(94);
		retorno_expresion_simple.tipo = ERROR;
	}

	retorno_expresion_simple.tipo = !hubo_operador_previo && es_tipo_base(termino_1.tipo) || termino_1.tipo == ARREGLO? termino_1.tipo : ERROR;
	retorno_expresion_simple.es_clase_variable = !hubo_operador_previo && termino_1.es_clase_variable;


	while (lookahead_in(F_RESTO_EXPRESION_SIMPLE)) {
		retorno_expresion_simple.es_clase_variable = FALSE;

		scanner();
		retorno_termino termino_n = termino(folset | F_RESTO_EXPRESION_SIMPLE);

		retorno_expresion_simple.tipo = resolver_tipo_operador(retorno_expresion_simple.tipo, termino_n.tipo);
	}

	return  retorno_expresion_simple;
}


retorno_termino termino(set folset)
{
	retorno_termino retorno_termino;

	retorno_factor factor_1 = factor(folset | F_RESTO_TERMINO | F_FACTOR);

	retorno_termino.tipo = factor_1.tipo;
	retorno_termino.es_clase_variable = factor_1.es_clase_variable;

	while(lookahead_in(F_RESTO_TERMINO))
	{
		retorno_termino.es_clase_variable = FALSE;
		scanner();
		retorno_factor factor_n = factor(folset | F_RESTO_TERMINO | F_FACTOR);

		retorno_termino.tipo = resolver_tipo_operador(retorno_termino.tipo, factor_n.tipo);
	}

	return retorno_termino;
}


retorno_factor factor(set folset)
{
	test(F_FACTOR, folset, 57);
	retorno_factor retorno_factor;

	switch(lookahead())
	{
		case CIDENT: {
			char *identificador = (char *) malloc(sizeof(char) * TAM_LEXEMA);
			strcpy(identificador, token1.lexema);
			scanner();

			int indice_en_TS = en_tabla(identificador);

			if (indice_en_TS == NIL) {
				error_handler(71);
				entrada_TS *variable_no_existente = nueva_entrada();
				strcpy(variable_no_existente->nbre, identificador);
				variable_no_existente->clase = CLASVAR;
				variable_no_existente->ptr_tipo = resolver_tipo_en_TS(ERROR);
				indice_en_TS = insertarTS();
			}
			free(identificador);

			if(lookahead_in(CPAR_ABR)) {
				parametros_llamada_funcion parametros_llamada_funcion;
				parametros_llamada_funcion.indice_en_TS = indice_en_TS;

				retorno_llamada_funcion llamada_funcion_1 = llamada_funcion(folset, parametros_llamada_funcion);
				retorno_factor.tipo = llamada_funcion_1.tipo;
				retorno_factor.es_clase_variable = FALSE;
			}
			else {
				parametros_variable parametros_variable;
				parametros_variable.indice_en_TS = indice_en_TS;

				retorno_variable variable_1 = variable(folset, parametros_variable);
				retorno_factor.tipo = variable_1.tipo;
				retorno_factor.es_clase_variable = TRUE;
			}
			break;
		}
		case CCONS_ENT:
		case CCONS_FLO:
		case CCONS_CAR: {
			retorno_constante constante_1 = constante(folset);
			retorno_factor.tipo = constante_1.tipo;
			retorno_factor.es_clase_variable = FALSE;

			break;
		}

		case CCONS_STR:
			scanner();
			retorno_factor.tipo = STRING;
			retorno_factor.es_clase_variable = FALSE;
			break;

		case CPAR_ABR:
			scanner();
			retorno_expresion expresion_1 = expresion(folset | CPAR_CIE);

			retorno_factor.tipo = es_tipo_base(expresion_1.tipo) ? expresion_1.tipo : ERROR;
			retorno_factor.es_clase_variable = FALSE;
			match(CPAR_CIE, 21);
			break;

		case CNEG:
			scanner();
			retorno_expresion expresion_2 = expresion(folset);
			lanzar_error_si_corresponde(expresion_2.tipo);
			retorno_factor.tipo = es_tipo_base(expresion_2.tipo) ? expresion_2.tipo : ERROR;
			retorno_factor.es_clase_variable = FALSE;

			break;
	}

	test(folset, 0, 58);
	return retorno_factor;
}


retorno_variable variable(set folset, parametros_variable params) {
	retorno_variable retorno_variable;

	// test(F_VARIABLE, folset | CCOR_ABR, 59);
	retorno_variable.tipo = resolver_tipo(ts[ts[params.indice_en_TS].ets->ptr_tipo].ets->nbre);

	if (lookahead_in(CCOR_ABR)) {
		if (params.indice_en_TS != NIL && retorno_variable.tipo != ARREGLO)
			error_handler(78);
		else if (params.indice_en_TS != NIL) {
			retorno_variable.tipo = resolver_tipo(
				ts[ts[params.indice_en_TS].ets->desc.part_var.arr.ptero_tipo_base].ets->nbre);
		}

		scanner();
		retorno_expresion expresion_1 = expresion(folset | CCOR_CIE);
		match(CCOR_CIE, 22);
	}

	test(folset, NADA, 60);
	return retorno_variable;
}


retorno_llamada_funcion llamada_funcion(set folset, parametros_llamada_funcion params)
{
	entrada_TS *entrada_ts;
	retorno_llamada_funcion retorno_llamada_funcion;

	entrada_ts = ts[params.indice_en_TS].ets;
	retorno_llamada_funcion.tipo = resolver_tipo(ts[ts[params.indice_en_TS].ets->ptr_tipo].ets->nbre);

	scanner();

	if (lookahead_in(F_LISTA_EXPRESIONES)) {
		retorno_lista_expresiones lista_expresiones_1 = lista_expresiones(folset | CPAR_CIE);
	}

	match(CPAR_CIE, 21);

	test(folset, NADA, 61);
	return retorno_llamada_funcion;
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
	retorno_constante retorno_constante;
	test(F_CONSTANTE, folset, 62);


	switch(lookahead())
	{
		case CCONS_ENT:
			scanner();
			retorno_constante.tipo = INT;
			break;

		case CCONS_FLO:
			scanner();
			retorno_constante.tipo = FLOAT;
			break;

		case CCONS_CAR:
			scanner();
			retorno_constante.tipo = CHAR;
			break;
	}

	test(folset, 0, 63);

	return retorno_constante;
}

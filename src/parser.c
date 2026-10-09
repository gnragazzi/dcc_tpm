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

	int indice_TS_main = en_tabla("main");
	entrada_TS *entrada_ts_main;

	if (indice_TS_main < 0 || (entrada_ts_main = ts[indice_TS_main].ets)->clase != CLASFUNC) {
		error_handler(84);
		pop_nivel();
		return;
	}

	enum tipo tipo_retorno_main = resolver_tipo(ts[entrada_ts_main->ptr_tipo].ets->nbre);

	if (tipo_retorno_main != VOID) {
		error_handler(85);
	}

	if (entrada_ts_main->desc.part_var.sub.cant_par != 0) {
		error_handler(86);
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

				entrada_nueva_funcion->desc.part_var.sub.cant_par = 0;
				entrada_nueva_funcion->desc.part_var.sub.ptr_inf_res = NULL;

				int posicion_insertada = insertarTS();
				if (posicion_insertada != 0)
					parametros_definicion_funcion.posicion_tabla_simbolos = posicion_insertada;
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
	enum boolean tiene_retorno = FALSE;

	pushTB();

	int posicion_tabla_simbolos = params.posicion_tabla_simbolos;
	parametros_proposicion_compuesta parametros_proposicion_compuesta;

	parametros_proposicion_compuesta.tipo_retorno = params.tipo_retorno;
	parametros_proposicion_compuesta.tiene_retorno = &tiene_retorno;

	match(CPAR_ABR, 20);

	if(lookahead_in(F_LISTA_DECLARACIONES_PARAM)) {
		parametros_lista_declaraciones_param parametros_lista_declaraciones_param;
		parametros_lista_declaraciones_param.posicion_tabla_simbolos = posicion_tabla_simbolos;

		lista_declaraciones_param(folset | CPAR_CIE | F_PROPOSICION_COMPUESTA, parametros_lista_declaraciones_param);
	}

	match(CPAR_CIE, 21);

	proposicion_compuesta(folset, parametros_proposicion_compuesta);
	if (params.tipo_retorno != VOID && !tiene_retorno) {
		error_handler(88);
	}
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

	Parametro_en_TS parametro_en_ts;

	if (lookahead_in(CCOR_ABR)) {
		scanner();
		match(CCOR_CIE, 22);

		if (tipo_pasaje == REFERENCIA) {
			error_handler(92);
		}

		parametro_en_ts.puntero_tipo_dato = resolver_tipo_en_TS(ARREGLO);
		parametro_en_ts.puntero_tipo_base = resolver_tipo_en_TS(parametro_tipo);
		parametro_en_ts.tipo_pasaje = VALOR;
	} else {
		parametro_en_ts.puntero_tipo_dato = resolver_tipo_en_TS(parametro_tipo);
		parametro_en_ts.puntero_tipo_base = NIL;
		parametro_en_ts.tipo_pasaje = tipo_pasaje;
	}

	if (identificador != NULL) {
		strcpy(nueva_variable->nbre, identificador);
		nueva_variable->clase = CLASPAR;
		nueva_variable->ptr_tipo = parametro_en_ts.puntero_tipo_dato;
		nueva_variable->desc.part_var.param.ptero_tipo_base = parametro_en_ts.puntero_tipo_base;
		nueva_variable->desc.part_var.param.tipo_pje = parametro_en_ts.tipo_pasaje;

		insertarTS();
	}

	if (params.posicion_tabla_simbolos != NIL)
		insertar_parametro_en_funcion(params.posicion_tabla_simbolos, parametro_en_ts);

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

		/*  { } son puntos de reconfiguracion de esta alternativa: se entra por
		ellos y cada match anterior reporta el token obligatorio omitido */
		case CCOR_ABR:
		case CCOR_CIE:
		case CLLA_ABR:
		case CLLA_CIE: {
			entrada_nueva_variable->ptr_tipo = resolver_tipo_en_TS(ARREGLO);
			entrada_nueva_variable->desc.part_var.arr.ptero_tipo_base = resolver_tipo_en_TS(params.tipo_declaracion);
			int valor_constante_entera = -1;
			match(CCOR_ABR, 35);

			if (lookahead_in(CCONS_ENT)) {
				valor_constante_entera = atoi(token1.lexema);
				scanner();

				if (valor_constante_entera == 0) {
					error_handler(75);
				}
			}

			match(CCOR_CIE, 22);

			int cantidad_inicializadores = 0;

			if (lookahead_in(CASIGNAC | CLLA_ABR | CLLA_CIE)) {
				match(CASIGNAC, 66);
				match(CLLA_ABR, 24);
				retorno_lista_inicializadores lista_inicializadores_1 = lista_inicializadores(CLLA_CIE | folset);
				match(CLLA_CIE, 25);
				cantidad_inicializadores = lista_inicializadores_1.cantidad_inicializadores;

				if (valor_constante_entera >= 0 && valor_constante_entera < cantidad_inicializadores) {
					error_handler(76);
				}
				if (cantidad_inicializadores > 0 && !param1_es_coercionable_a_param2(lista_inicializadores_1.tipo_inicializadores, params.tipo_declaracion)) {
					error_handler(77);
				}
			}

			if (valor_constante_entera < 0 && cantidad_inicializadores == 0) {
				error_handler(75);
			}
			break;
		}
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
	retorno_lista_inicializadores retorno_lista_inicializadores;

	enum boolean hay_constante = lookahead_in(F_CONSTANTE) ? TRUE : FALSE;
	retorno_constante constante_1 = constante(folset | CCOMA | F_CONSTANTE);
	retorno_lista_inicializadores.cantidad_inicializadores = hay_constante || lookahead_in(CCOMA | F_CONSTANTE) ? 1 : 0;
	retorno_lista_inicializadores.tipo_inicializadores = constante_1.tipo;

	while(lookahead_in(CCOMA | F_CONSTANTE))
	{
		if(lookahead_in(CCOMA))
			scanner();
		else
			error_handler(64);

		retorno_constante constante_n = constante(folset | CCOMA | F_CONSTANTE);

		retorno_lista_inicializadores.cantidad_inicializadores++;
		retorno_lista_inicializadores.tipo_inicializadores = resolver_tipo_operador(retorno_lista_inicializadores.tipo_inicializadores, constante_n.tipo);
	}
	return retorno_lista_inicializadores;
}


void proposicion_compuesta(set folset, parametros_proposicion_compuesta params)
{
	test(F_PROPOSICION_COMPUESTA | F_LISTA_DECLARACIONES | F_LISTA_PROPOSICIONES | CLLA_CIE, folset, 49);

	match(CLLA_ABR, 24);

	if(lookahead_in(F_LISTA_DECLARACIONES))
		lista_declaraciones(folset | F_LISTA_PROPOSICIONES | CLLA_CIE);

	if(lookahead_in(F_LISTA_PROPOSICIONES)) {
		parametros_lista_proposiciones parametros_lista_proposiciones;
		parametros_lista_proposiciones.tipo_retorno = params.tipo_retorno;
		parametros_lista_proposiciones.tiene_retorno = params.tiene_retorno;

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
	parametros_proposicion parametros_proposicion;

	parametros_proposicion.tipo_retorno = params.tipo_retorno;
	parametros_proposicion.tiene_retorno = params.tiene_retorno;

	proposicion(folset | F_PROPOSICION, parametros_proposicion);

	while(lookahead_in(F_PROPOSICION)) {
		proposicion(folset | F_PROPOSICION, parametros_proposicion);
	}
}


void proposicion(set folset, parametros_proposicion params) {
	test(F_PROPOSICION, folset, 52);

	switch(lookahead()) {
		case CLLA_ABR:
			pushTB();

			parametros_proposicion_compuesta parametros_proposicion_compuesta;
			parametros_proposicion_compuesta.tipo_retorno = params.tipo_retorno;
			parametros_proposicion_compuesta.tiene_retorno = params.tiene_retorno;

			proposicion_compuesta(folset, parametros_proposicion_compuesta);
			break;

		case CWHILE: {
			parametros_proposicion_iteracion parametros_proposicion_iteracion;
			parametros_proposicion_iteracion.tipo_retorno = params.tipo_retorno;
			parametros_proposicion_iteracion.tiene_retorno = params.tiene_retorno;

			proposicion_iteracion(folset, parametros_proposicion_iteracion);
			break;
		}

		case CIF: {
			parametros_proposicion_seleccion parametros_proposicion_seleccion;
			parametros_proposicion_seleccion.tipo_retorno = params.tipo_retorno;
			parametros_proposicion_seleccion.tiene_retorno = params.tiene_retorno;

			proposicion_seleccion(folset, parametros_proposicion_seleccion);
			break;
		}

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

		case CRETURN: {
			*params.tiene_retorno = TRUE;

			parametros_proposicion_retorno parametros_proposicion_retorno;
			parametros_proposicion_retorno.tipo_retorno = params.tipo_retorno;

			proposicion_retorno(folset, parametros_proposicion_retorno);
			break;
		}
	}
}


void proposicion_iteracion(set folset, parametros_proposicion_iteracion params)
{
	parametros_proposicion parametros_proposicion;
	parametros_proposicion.tipo_retorno = params.tipo_retorno;
	parametros_proposicion.tiene_retorno = params.tiene_retorno;

	match(CWHILE, 27);

	match(CPAR_ABR, 20);

	retorno_expresion expresion_1 = expresion(folset | CPAR_CIE | F_PROPOSICION);

	if (!es_tipo_base(expresion_1.tipo)) {
		error_handler(97);
	}
	if (expresion_1.tipo == STRING) {
		error_handler(94);
	}

	match(CPAR_CIE, 21);

	proposicion(folset, parametros_proposicion);
}


void proposicion_seleccion(set folset, parametros_proposicion_seleccion params)
{
	parametros_proposicion parametros_proposicion;
	parametros_proposicion.tipo_retorno = params.tipo_retorno;
	parametros_proposicion.tiene_retorno = params.tiene_retorno;

	match(CIF, 28);

	match(CPAR_ABR, 20);

	retorno_expresion expresion_1 = expresion(folset | CPAR_CIE | F_PROPOSICION | F_ELSE_OPCIONAL);

	if (!es_tipo_base(expresion_1.tipo)) {
		error_handler(97);
	}
	if (expresion_1.tipo == STRING) {
		error_handler(94);
	}

	match(CPAR_CIE, 21);

	proposicion(folset | F_ELSE_OPCIONAL | F_PROPOSICION, parametros_proposicion);

	if(lookahead_in(F_ELSE_OPCIONAL))
	{
		scanner();
		proposicion(folset, parametros_proposicion);
	}
}


void proposicion_e_s(set folset) {
	switch (lookahead()) {
		case CIN: {

			parametros_variable parametros_variable;
			parametros_variable.origen_proposicion_entrada = TRUE;
			scanner();

			match(CSHR, 30);
			retorno_variable variable_1 =
					variable(folset | F_RESTO_PROP_IN | F_VARIABLE | CPYCOMA, parametros_variable);

			if (!es_tipo_base(variable_1.tipo)) {
				error_handler(95);
			}

			while (lookahead_in(F_RESTO_PROP_IN | F_VARIABLE)) {
				match(CSHR, 30);
				retorno_variable variable_n = variable(folset | F_RESTO_PROP_IN | F_VARIABLE | CPYCOMA,
				                                       parametros_variable);

				if (!es_tipo_base(variable_n.tipo)) {
					error_handler(95);
				}
			}

			match(CPYCOMA, 23);

			break;
		}
		case COUT: {

			scanner();

			match(CSHL, 31);

			retorno_expresion expresion_1 = expresion(folset | F_RESTO_PROP_OUT | F_EXPRESION | CPYCOMA);

			if (!es_tipo_base(expresion_1.tipo) && expresion_1.tipo != STRING) {
				error_handler(95);
			}

			while (lookahead_in(F_RESTO_PROP_OUT | F_EXPRESION)) {
				match(CSHL, 31);
				retorno_expresion expresion_m = expresion(folset | F_RESTO_PROP_OUT | F_EXPRESION | CPYCOMA);

			if (!es_tipo_base(expresion_m.tipo) && expresion_m.tipo != STRING) {
					error_handler(95);
				}
			}

			match(CPYCOMA, 23);

			break;
		}
		default: {
			error_handler(29);
			break;
		}
	}

	test(folset, NADA, 53);
}


void proposicion_retorno(set folset, parametros_proposicion_retorno params) {
	scanner();

	retorno_expresion expresion_1 = expresion(folset | CPYCOMA);

	if (expresion_1.tipo == STRING)
		error_handler(94);


	match(CPYCOMA, 23);

	test(folset, NADA, 54);
	if (params.tipo_retorno == VOID) {
		error_handler(89);
	} else if (!param1_es_coercionable_a_param2(expresion_1.tipo, params.tipo_retorno)) {
		error_handler(87);
	}
}


void proposicion_expresion(set folset)
{
	if(lookahead_in(F_EXPRESION)) {
		retorno_expresion expresion_1 = expresion(folset | CPYCOMA);
		if (expresion_1.tipo == STRING)
			error_handler(94);
	}

	match(CPYCOMA, 23);

	test(folset, NADA, 55);
}


retorno_expresion expresion(set folset)
{
	retorno_expresion retorno_expresion;
	retorno_expresion_simple expresion_simple_1 = expresion_simple(folset | F_RESTO_EXPRESION | F_EXPRESION_SIMPLE);
	retorno_expresion.tipo_base = expresion_simple_1.tipo == ARREGLO ? expresion_simple_1.tipo_base : ERROR;
	enum boolean se_lanzo_error_arreglo_como_todo = TRUE;

	enum tipo tipo_izquierda_asignacion = retorno_expresion.tipo = expresion_simple_1.tipo;
	enum boolean clase_izquierda_asignacion_es_variable =
			retorno_expresion.es_clase_variable = expresion_simple_1.es_clase_variable;

	while(lookahead_in(F_RESTO_EXPRESION))
	{
		switch(lookahead())
		{
			case CASIGNAC: {
				if (!clase_izquierda_asignacion_es_variable) {
					error_handler(82);
				}else if (tipo_izquierda_asignacion == ARREGLO){
					error_handler(81);
					se_lanzo_error_arreglo_como_todo = TRUE;
				}
				scanner();
				retorno_expresion_simple expresion_simple_2 = expresion_simple(folset | F_RESTO_EXPRESION | F_EXPRESION_SIMPLE);
				clase_izquierda_asignacion_es_variable = expresion_simple_2.es_clase_variable;

				if (!param1_es_coercionable_a_param2(expresion_simple_2.tipo, tipo_izquierda_asignacion)) {
					error_handler(83);
				}

				tipo_izquierda_asignacion = expresion_simple_2.tipo;

				if (expresion_simple_2.tipo == ARREGLO) {
					se_lanzo_error_arreglo_como_todo = FALSE;
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

				enum tipo tipo_coercion_operando =resolver_tipo_operador(retorno_expresion.tipo, expresion_simple_3.tipo);
				retorno_expresion.tipo = tipo_coercion_operando != ERROR ? INT : ERROR;

				break;
			}
		}
		retorno_expresion.tipo_base = ERROR;
	}

	if (!se_lanzo_error_arreglo_como_todo) {
		error_handler(81);
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
		termino_1.tipo = ERROR;
	}

	retorno_expresion_simple.tipo = (termino_1.tipo == ARREGLO && hubo_operador_previo) ? ERROR : termino_1.tipo;
	retorno_expresion_simple.tipo_base =(termino_1.tipo == ARREGLO && hubo_operador_previo) ? ERROR : termino_1.tipo_base;
	retorno_expresion_simple.es_clase_variable = !hubo_operador_previo && termino_1.es_clase_variable;


	while (lookahead_in(F_RESTO_EXPRESION_SIMPLE)) {
		retorno_expresion_simple.es_clase_variable = FALSE;
		enum boolean es_operador_logico_or = token1.codigo == COR;

		scanner();
		retorno_termino termino_n = termino(folset | F_RESTO_EXPRESION_SIMPLE);

		enum tipo tipo_coercion_operando = resolver_tipo_operador(retorno_expresion_simple.tipo, termino_n.tipo);

		retorno_expresion_simple.tipo = es_operador_logico_or && tipo_coercion_operando != ERROR? INT : tipo_coercion_operando;
		retorno_expresion_simple.tipo_base = ERROR;
	}

	return  retorno_expresion_simple;
}


retorno_termino termino(set folset)
{
	retorno_termino retorno_termino;

	retorno_factor factor_1 = factor(folset | F_RESTO_TERMINO | F_FACTOR);

	retorno_termino.tipo = factor_1.tipo;
	retorno_termino.es_clase_variable = factor_1.es_clase_variable;
	retorno_termino.tipo_base = factor_1.tipo_base;

	while(lookahead_in(F_RESTO_TERMINO))
	{
		retorno_termino.es_clase_variable = FALSE;
		enum boolean es_operador_logico_and = token1.codigo == CAND;

		scanner();
		retorno_factor factor_n = factor(folset | F_RESTO_TERMINO | F_FACTOR);

		enum tipo tipo_coercion_operando = resolver_tipo_operador(retorno_termino.tipo, factor_n.tipo);

		retorno_termino.tipo = es_operador_logico_and && tipo_coercion_operando != ERROR? INT : tipo_coercion_operando;
		retorno_termino.tipo_base = ERROR;
	}

	return retorno_termino;
}


retorno_factor factor(set folset)
{
	test(F_FACTOR, folset, 57);
	retorno_factor retorno_factor;
	retorno_factor.tipo_base = ERROR;

	switch (lookahead()) {
		case CIDENT: {
			char *identificador = (char *) malloc(sizeof(char) * TAM_LEXEMA);
			strcpy(identificador, token1.lexema);
			enum boolean es_funcion = FALSE;
			enum boolean identificador_esta_en_TS;

			int indice_en_TS = en_tabla(identificador);

			if (indice_en_TS != NIL) {
				es_funcion = ts[indice_en_TS].ets->clase == CLASFUNC;
				identificador_esta_en_TS = TRUE;
			} else {
				error_handler(71);
				entrada_TS *variable_no_existente = nueva_entrada();
				strcpy(variable_no_existente->nbre, identificador);
				variable_no_existente->clase = -1;
				variable_no_existente->ptr_tipo = resolver_tipo_en_TS(ERROR);
				indice_en_TS = insertarTS();
				identificador_esta_en_TS = FALSE;
			}
			free(identificador);

			scanner();
			if (es_funcion || (!identificador_esta_en_TS && lookahead_in(CPAR_ABR))) {
				parametros_llamada_funcion parametros_llamada_funcion;
				parametros_llamada_funcion.indice_en_TS = indice_en_TS;

				if (!identificador_esta_en_TS) {
					entrada_TS *entrada = ts[indice_en_TS].ets;
					entrada->clase = CLASFUNC;
				}

				retorno_llamada_funcion llamada_funcion_1 = llamada_funcion(folset, parametros_llamada_funcion);
				retorno_factor.tipo = llamada_funcion_1.tipo;
				retorno_factor.es_clase_variable = FALSE;
			} else {
				parametros_variable parametros_variable;
				parametros_variable.indice_en_TS = indice_en_TS;
				parametros_variable.origen_proposicion_entrada = FALSE;

				if (!identificador_esta_en_TS) {
					entrada_TS *entrada = ts[indice_en_TS].ets;
					entrada->clase = CLASVAR;
				}

				retorno_variable variable_1 = variable(folset, parametros_variable);
				retorno_factor.tipo = variable_1.tipo;
				retorno_factor.tipo_base = variable_1.tipo_base;
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

		case CNEG: {
			scanner();
			retorno_expresion expresion_2 = expresion(folset);
			lanzar_error_si_corresponde(expresion_2.tipo);
			retorno_factor.tipo = es_tipo_base(expresion_2.tipo) ? INT : ERROR;
			retorno_factor.es_clase_variable = FALSE;

			break;
		}
		default: {
			retorno_factor.es_clase_variable = FALSE;
			retorno_factor.tipo = ERROR;
		}
	}

	test(folset, 0, 58);
	return retorno_factor;
}


retorno_variable variable(set folset, parametros_variable params) {
	retorno_variable retorno_variable;

	if (params.origen_proposicion_entrada) {
		test(F_VARIABLE, folset | CCOR_ABR, 59);

		if (lookahead() & CIDENT) {
			char *identificador = (char *) malloc(sizeof(char) * TAM_LEXEMA);

			strcpy(identificador, token1.lexema);
			scanner();
			params.indice_en_TS = en_tabla(identificador);

			if (params.indice_en_TS == NIL) {
				error_handler(71);
				entrada_TS *variable_no_existente = nueva_entrada();
				strcpy(variable_no_existente->nbre, identificador);
				variable_no_existente->clase = CLASVAR;
				variable_no_existente->ptr_tipo = resolver_tipo_en_TS(ERROR);
				params.indice_en_TS = insertarTS();
			}
			free(identificador);
		} else {
			error_handler(17);
			params.indice_en_TS = NIL;
			retorno_variable.tipo = ERROR;
		}
	}

	entrada_TS *entrada_ts = params.indice_en_TS != NIL ?ts[params.indice_en_TS].ets : NULL;
	enum boolean es_parametro = entrada_ts != NULL ? entrada_ts->clase == CLASPAR : FALSE ;

	if (params.indice_en_TS != NIL)
		retorno_variable.tipo = resolver_tipo(ts[ts[params.indice_en_TS].ets->ptr_tipo].ets->nbre);

	if (lookahead_in(CCOR_ABR)) {
		if (params.indice_en_TS != NIL && retorno_variable.tipo != ARREGLO)
			error_handler(78);
		else if (params.indice_en_TS != NIL) {

			if (es_parametro) {
				retorno_variable.tipo = resolver_tipo(ts[entrada_ts->desc.part_var.param.ptero_tipo_base].ets->nbre);
			} else {
				retorno_variable.tipo = resolver_tipo(ts[entrada_ts->desc.part_var.arr.ptero_tipo_base].ets->nbre);
			}
		}

		scanner();
		retorno_expresion expresion_1 = expresion(folset | CCOR_CIE);

		if (expresion_1.tipo == STRING)
			error_handler(94);

		match(CCOR_CIE, 22);
	}else {
		if (params.indice_en_TS != NIL && retorno_variable.tipo == ARREGLO) {
			retorno_variable.tipo_base = es_parametro
				                             ? resolver_tipo(
					                             ts[entrada_ts->desc.part_var.param.ptero_tipo_base].ets->nbre)
				                             : resolver_tipo(
					                             ts[entrada_ts->desc.part_var.arr.ptero_tipo_base].ets->nbre);
		}
	}

	test(folset, NADA, 60);
	return retorno_variable;
}


retorno_llamada_funcion llamada_funcion(set folset, parametros_llamada_funcion params) {
	retorno_llamada_funcion retorno_llamada_funcion;

	entrada_TS *entrada_ts = ts[params.indice_en_TS].ets;
	retorno_llamada_funcion.tipo = resolver_tipo(ts[ts[params.indice_en_TS].ets->ptr_tipo].ets->nbre);

	enum boolean hay_par_abr = lookahead_in(CPAR_ABR) ? TRUE : FALSE;
	match(CPAR_ABR, 20);

	if (hay_par_abr && lookahead_in(F_LISTA_EXPRESIONES)) {
		parametros_lista_expresiones parametros_lista_expresiones;
		parametros_lista_expresiones.indice_en_TS = params.indice_en_TS;

		lista_expresiones(folset | CPAR_CIE, parametros_lista_expresiones);
	} else {
		enum tipo tipo_declarado = resolver_tipo(ts[entrada_ts->ptr_tipo].ets->nbre);
		if (tipo_declarado != ERROR && entrada_ts->desc.part_var.sub.cant_par > 0)
			error_handler(90);
	}

	match(CPAR_CIE, 21);

	test(folset, NADA, 61);
	return retorno_llamada_funcion;
}


void lista_expresiones(set folset, parametros_lista_expresiones params) {
	entrada_TS *entrada_funcion = ts[params.indice_en_TS].ets;
	int contador_parametros_actuales = 0;

	retorno_expresion expresion_1 = expresion(folset | CCOMA | F_EXPRESION);

	enum tipo tipo_declarado = resolver_tipo(ts[entrada_funcion->ptr_tipo].ets->nbre);
	tipo_inf_res *siguiente_parametro_lista_funcion = entrada_funcion->desc.part_var.sub.ptr_inf_res;
	int cantidad_parametros_declarados = entrada_funcion->desc.part_var.sub.cant_par;
	enum boolean corresponde_chequear_parametro = cantidad_parametros_declarados > contador_parametros_actuales;
	if (expresion_1.tipo == STRING)
		error_handler(94);

	if (tipo_declarado != ERROR && corresponde_chequear_parametro) {
		Parametro_actual parametro_actual;
		parametro_actual.tipo_dato = expresion_1.tipo;
		parametro_actual.tipo_base = expresion_1.tipo_base;
		parametro_actual.es_clase_variable = expresion_1.es_clase_variable;

		chequear_igualdad_parametro_actual_vs_parametro_TS(parametro_actual, siguiente_parametro_lista_funcion);
		siguiente_parametro_lista_funcion = siguiente_parametro_lista_funcion->ptr_sig;
	}

	contador_parametros_actuales++;

	while (lookahead_in(CCOMA | F_EXPRESION)) {
		match(CCOMA, 64);
		retorno_expresion expresion_n = expresion(folset | CCOMA | F_EXPRESION);

		if (expresion_n.tipo == STRING)
			error_handler(94);

		corresponde_chequear_parametro = cantidad_parametros_declarados > contador_parametros_actuales;

		if (tipo_declarado != ERROR && corresponde_chequear_parametro) {
			Parametro_actual parametro_actual;
			parametro_actual.tipo_dato = expresion_n.tipo;
			parametro_actual.tipo_base = expresion_n.tipo_base;
			parametro_actual.es_clase_variable = expresion_n.es_clase_variable;

			chequear_igualdad_parametro_actual_vs_parametro_TS(parametro_actual, siguiente_parametro_lista_funcion);
			siguiente_parametro_lista_funcion = siguiente_parametro_lista_funcion->ptr_sig;
		}
		contador_parametros_actuales++;
	}

	if (tipo_declarado != ERROR && cantidad_parametros_declarados != contador_parametros_actuales)
		error_handler(90);
}


retorno_constante constante(set folset)
{
	retorno_constante retorno_constante;
	retorno_constante.tipo = ERROR;
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

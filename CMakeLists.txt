cmake_minimum_required(VERSION 4.1)
project(dcc_tpm C)

set(CMAKE_C_STANDARD 11)

include_directories(src)

add_executable(dcc_tpm
        src/codigos.h
        src/conjuntos.h
        src/error.c
        src/error.h
        src/lex.yy.c
        src/parser.c
        src/parser.h
        src/util.c
        src/util.h
        src/var_globales.h
        tests/entrega1/pendientes/invalidos/01_falta_punto_coma.c
        tests/entrega1/pendientes/invalidos/01_falta_punto_coma_cin.c
        tests/entrega1/pendientes/invalidos/01_falta_punto_coma_cout.c
        tests/entrega1/pendientes/invalidos/01_falta_punto_coma_decl_global.c
        tests/entrega1/pendientes/invalidos/01_falta_punto_coma_decl_local.c
        tests/entrega1/pendientes/invalidos/01_falta_punto_coma_retorno.c
        tests/entrega1/pendientes/invalidos/02_falta_coma.c
        tests/entrega1/pendientes/invalidos/02_falta_coma_decl_init.c
        tests/entrega1/pendientes/invalidos/02_falta_coma_inicializadores.c
        tests/entrega1/pendientes/invalidos/02_falta_coma_llamada.c
        tests/entrega1/pendientes/invalidos/02_falta_coma_param.c
        tests/entrega1/pendientes/invalidos/03_falta_parentesis_cierre.c
        tests/entrega1/pendientes/invalidos/04_falta_llave_cierre.c
        tests/entrega1/pendientes/invalidos/04_falta_llave_cierre_init.c
        tests/entrega1/pendientes/invalidos/05_tipo_invalido.c
        tests/entrega1/pendientes/invalidos/05_tipo_invalido_global.c
        tests/entrega1/pendientes/invalidos/05_tipo_invalido_param.c
        tests/entrega1/pendientes/invalidos/06_falta_identificador.c
        tests/entrega1/pendientes/invalidos/06_falta_identificador_decl_multiple.c
        tests/entrega1/pendientes/invalidos/06_falta_identificador_global.c
        tests/entrega1/pendientes/invalidos/06_falta_identificador_parametro.c
        tests/entrega1/pendientes/invalidos/07_simbolo_inesperado_delimitador.c
        tests/entrega1/pendientes/invalidos/07_simbolo_inesperado_proposicion.c
        tests/entrega1/pendientes/invalidos/07_simbolo_inesperado_puntuacion.c
        tests/entrega1/pendientes/invalidos/08_error_en_expresion.c
        tests/entrega1/pendientes/invalidos/08_error_en_expresion_relacion.c
        tests/entrega1/pendientes/invalidos/08_error_en_expresion_termino.c
        tests/entrega1/pendientes/invalidos/09_cascada_misma_linea.c
        tests/entrega1/pendientes/invalidos/10_cascada_lineas_sucesivas.c
        tests/entrega1/pendientes/invalidos/11_cascada_funcion_completa.c
        tests/entrega1/pendientes/invalidos/12_cascada_bloques_anidados.c
        tests/entrega1/pendientes/invalidos/13_cascada_misma_linea_multiple.c
        tests/entrega1/pendientes/validos/04_programa_realista.c
        tests/entrega1/validos/01_declaraciones_globales.c
        tests/entrega1/validos/02_arreglos_inicializador.c
        tests/entrega1/validos/03_parametros_referencia.c
        tests/entrega1/validos/l3_llamadas_funciones.c)

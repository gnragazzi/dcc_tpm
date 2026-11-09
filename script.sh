#!/usr/bin/env bash

for f in tests/entrega1/validos/{02_if_else,07_while,09_bloques_anidados}.c \
         tests/entrega2/validos/{01_variables_locales,02_variable_global,05_tipos_variable_simple,08_asignacion_variable_simple,11_asignacion_conversion_implicita,12_es_variables_simples,14_es_string_en_cout,15_condicion_variable_simple,31_relacional_float_asigna_a_int,32_relacional_asigna_a_float,33_logico_float_asigna_a_int,36_inicializacion_variable_coercion}.c; do
  git mv "$f" "${f/validos/compilables}"
done
make -C src clean && ./scripts/test_local.sh

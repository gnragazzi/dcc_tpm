# Expectativa: cascada con reconfiguracion por la } del inicializador #
# Prueba: mismo caso que el local pero global. La { no pertenece al folset heredado y se #
# descarta en la resincronizacion del test 43 de especificador_declaracion; la entrada al #
# switch la termina disparando la } del inicializador. #

char a {1, 2};

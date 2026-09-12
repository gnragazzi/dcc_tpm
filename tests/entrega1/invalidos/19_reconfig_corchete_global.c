# Expectativa: cascada con reconfiguracion por la } del inicializador #
# Prueba: misma omision que el caso local pero en declaracion global. El ] se descarta en #
# la resincronizacion del test 43 de especificador_declaracion, cuyo c1 no lo contiene, de #
# modo que el punto de reconfiguracion que termina disparando es la } del inicializador. #

char a] = {1, 2};

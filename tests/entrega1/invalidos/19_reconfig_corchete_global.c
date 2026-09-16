# Expectativa: cascada interceptada por el test inicial de lista_declaraciones_init (Error 46), #
# ya no llega a los puntos de reconfiguracion de declarador_init #
# Prueba: misma omision que el caso local pero en declaracion global. El ] se descarta en #
# la resincronizacion del test 43 de especificador_declaracion, cuyo c1 no lo contiene. Desde #
# la devolución punto 4, el identificador faltante lo reporta el test inicial de #
# lista_declaraciones_init (Error 46) antes de llegar a los puntos de reconfiguracion #
# ( ] { } ) de declarador_init #

char a] = {1, 2};

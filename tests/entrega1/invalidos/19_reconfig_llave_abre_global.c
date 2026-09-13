# Expectativa: cascada interceptada por el test inicial de lista_declaraciones_init (Error 46), #
# ya no llega al switch de declarador_init #
# Prueba: mismo caso que el local pero global. La { no pertenece al folset heredado y se #
# descarta en la resincronizacion del test 43 de especificador_declaracion. Desde la #
# devolución punto 4, el identificador faltante lo reporta el test inicial de #
# lista_declaraciones_init (Error 46) antes de llegar al switch de declarador_init #

char a {1, 2};

# Expectativa: Error 49: Simbolo inesperado o falta simb. al comienzo de proposicion compuesta, #
# Error 25: Falta } #
# Prueba: falta el cuerpo entero de la funcion. El test inicial de proposicion_compuesta #
# resincroniza en el folset heredado (CEOF); sin la guarda de la regla 9, el cuerpo sigue #
# corriendo y match(CLLA_CIE, 25) reporta la } faltante sin consumir, formando la cascada #
# esperada por el esquema de recuperacion (devolucion punto 5). #

void main()

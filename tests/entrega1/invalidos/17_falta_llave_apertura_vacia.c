# Expectativa: Error 49: Simbolo inesperado o falta simb. al comienzo de proposicion compuesta #
# Prueba: falta la llave de apertura y el bloque queda vacio. Fija la guarda de la regla 9 en #
# proposicion_compuesta: el test inicial reporta 49 y descarta el }, queda EOF, y sin el return #
# el cuerpo sigue corriendo y agrega un 52 y un 25 sobre un token ya en estado de error. #

void main()
}

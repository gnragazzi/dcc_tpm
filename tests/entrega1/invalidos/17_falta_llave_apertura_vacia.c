# Expectativa: Error 49: Simbolo inesperado o falta simb. al comienzo de proposicion compuesta #
# Prueba: falta la llave de apertura y el bloque queda vacio. Con la } en el c2 del test inicial #
# la resincronizacion frena sobre ella sin descartar nada, el cuerpo corre con los dos guardianes #
# en silencio y match(CLLA_CIE, 25) cierra el bloque: el 49 queda como unico error. #

void main()
}

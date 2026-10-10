# Expectativa: Error 24: Falta { #
# Prueba: falta la llave de apertura y el bloque queda vacio. Con la } en el c1 del test inicial #
# la resincronizacion no descarta nada, match(CLLA_ABR, 24) reporta la { omitida, el cuerpo corre #
# con los dos guardianes en silencio y match(CLLA_CIE, 25) cierra el bloque. #

void main()
}

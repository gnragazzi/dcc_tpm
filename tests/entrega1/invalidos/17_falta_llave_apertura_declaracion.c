# Expectativa: Error 49: Simbolo inesperado o falta simb. al comienzo de proposicion compuesta #
# Prueba: falta la llave de apertura y el bloque abre con una declaracion. Fija la regla 8 sobre #
# la llave: el test inicial ya verifico CLLA_ABR, asi que el cuerpo la consume condicional y #
# silenciosamente. Con un match en su lugar se reporta un 24 de mas sobre el mismo token. #

void main()
    int x;
}

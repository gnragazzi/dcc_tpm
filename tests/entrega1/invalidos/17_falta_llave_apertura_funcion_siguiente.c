# Expectativa: Error 49: Simbolo inesperado o falta simb. al comienzo de proposicion compuesta #
# Prueba: falta la llave de apertura y el bloque vacio es seguido de otra funcion. Fija la } como #
# punto de reconfiguracion del test inicial: sin ella el test descarta la } y resincroniza en el #
# void siguiente, que lista_declaraciones lee como declaracion local y arrastra cinco errores. #

void main()
}

void f()
{
    int x;
}

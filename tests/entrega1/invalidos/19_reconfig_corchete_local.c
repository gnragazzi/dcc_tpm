# Expectativa: Error 47: Simbolo inesperado al comienzo de declarador init, Error 35: Falta [ #
# Prueba: omision del corchete de apertura en un arreglo local, con ] como lookahead del #
# test inicial. El ] esta en el c2 del test (punto de reconfiguracion de la 2da #
# alternativa), asi que el 47 reporta la llegada espuria, la resincronizacion frena sobre #
# el ] sin descartarlo y el switch entra por el case CCOR_CIE: match(CCOR_ABR, 35) nombra #
# el token omitido y el resto del inicializador se consume normalmente. #

void main()
{
    int a] = {1, 2};
}

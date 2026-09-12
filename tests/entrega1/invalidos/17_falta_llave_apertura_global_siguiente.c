# Expectativa: Error 49: Simbolo inesperado o falta simb. al comienzo de proposicion compuesta #
# Prueba: falta la llave de apertura y el bloque vacio es seguido de una declaracion global. La } #
# como punto de reconfiguracion permite que match(CLLA_CIE, 25) la consuma y cierre el bloque; #
# sin ella la } se descarta y el match reporta un 25 espurio sobre el int siguiente. #

void main()
}
int g;

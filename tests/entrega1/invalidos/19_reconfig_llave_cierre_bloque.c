# Expectativa: reconfiguracion por la } de la proposicion compuesta #
# Prueba: declaracion local sin ; justo antes del cierre del bloque. La } pertenece al #
# folset heredado de declarador_init (proposicion_compuesta la propaga hacia lista_declaraciones) #
# y a la vez es punto de reconfiguracion de la 2da alternativa: el switch entra por el case #
# CLLA_CIE y la consume como cierre del inicializador, de modo que el match(CLLA_CIE, 25) #
# de proposicion_compuesta la reclama despues. #

void main()
{
    int a
}

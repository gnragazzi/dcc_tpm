# Expectativa: Error 35: Falta [, Error 22: Falta ], Error 66: Falta = #
# Prueba: lista de inicializadores sin dimension ni =, en declaracion local. La { esta en #
# el folset heredado por F_PROPOSICION_COMPUESTA, asi que el test inicial pasa en silencio #
# y el switch entra por el case CLLA_ABR: los tres match previos de la alternativa nombran #
# los terminales obligatorios omitidos y la lista se consume entera. #

void main()
{
    int a {1, 2};
}

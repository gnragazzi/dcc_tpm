# Expectativa: Error 52: Simbolo inesperado o falta simb. al comienzo de proposicion #
# Prueba: operador binario al comienzo del cuerpo de un bloque. Fija el test intermedio de #
# proposicion_compuesta: sin el, los dos guardianes se saltean en silencio y el error lo #
# reporta match(CLLA_CIE, 25) como "falta }", sin consumir. #

void main()
{
    * a = 5;
}

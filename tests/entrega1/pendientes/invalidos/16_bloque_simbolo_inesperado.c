# Expectativa: Error 52: Simbolo inesperado o falta simb. al comienzo de proposicion #
# Prueba: operador binario al comienzo del cuerpo de un bloque. Sin el test intermedio de #
# proposicion_compuesta los dos guardianes se saltean en silencio y el error lo reporta #
# match(CLLA_CIE, 25) como "falta }", sin consumir: el bloque se cierra donde no corresponde. #

void main()
{
    * a = 5;
}

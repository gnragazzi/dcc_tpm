# Expectativa: Error 25 (Falta }) seguido de Error 50 #
# Prueba: operador binario al comienzo del cuerpo de un bloque. Devolución punto 4: sin el test #
# intermedio de proposicion_compuesta (eliminado), los dos guardianes se saltean en silencio y el #
# error lo reporta match(CLLA_CIE, 25) como "falta }", sin consumir; el test final agrega el 50. #

void main()
{
    * a = 5;
}

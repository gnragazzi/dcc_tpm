# Expectativa: en el cin, Error 56 (test de expresion_simple, sin cambios); en el fop4( , b), #
# cascada distinta desde la devolución punto 4: Error 21, 61, 23, 60 #
# Prueba: el test de expresion_simple frena en un token del folset heredado, que no esta ni en FIRST(expresion simple) ni en su resto. Ahi la guarda retorna sin correr el cuerpo, y el error 57 de factor no se dispara. Lo que sigue al token de sincronizacion se sigue analizando. El segundo caso (fop4( , b)) ya no ejercita el test intermedio de llamada_funcion (eliminado, devolución punto 4): la coma se descarta recién en el cierre del paréntesis y el resto se reinterpreta como una sentencia aparte #

void fop4(int x, int y)
{
    x = y;
}

void main()
{
    int a, b;

    a = 2; b = 3;

    cout << ) ;
    fop4( , b);
}

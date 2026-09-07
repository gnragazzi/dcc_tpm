# Expectativa: Error 56: Simbolo inesperado o falta simb. al comienzo de expresion simple #
# Prueba: el test de expresion_simple frena en un token del folset heredado, que no esta ni en FIRST(expresion simple) ni en su resto. Ahi la guarda retorna sin correr el cuerpo, y el error 57 de factor no se dispara. Lo que sigue al token de sincronizacion se sigue analizando #

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

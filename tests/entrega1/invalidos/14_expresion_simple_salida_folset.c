# Expectativa: Error 56: Simbolo inesperado o falta simb. al comienzo de expresion simple, #
# Error 57: Simbolo inesperado o falta simb. al comienzo de factor #
# Prueba: el test de expresion_simple frena en un token del folset heredado, que no esta ni en #
# FIRST(expresion simple) ni en su resto. El cuerpo corre igual: termino() delega en factor, #
# cuyo test reporta el 57 sobre ese mismo token sin consumirlo. Es la cascada que acepta el #
# esquema de teoria (devolucion punto 5). Lo que este caso fija es que el ) NO se consume: con #
# el if/else anterior (devolucion punto 6) el scanner() incondicional se lo comia y el Falta ; #
# de mas abajo salia como Falta <<. #

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

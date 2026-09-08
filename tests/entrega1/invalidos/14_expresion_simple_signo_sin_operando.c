# Expectativa: Error 57: Simbolo inesperado o falta simb. al comienzo de factor #
# Prueba: se consume el signo unario opcional de <expresion simple> y despues falta el termino. La llamada a termino() es incondicional, asi que el test de factor reporta una vez por sentencia. Un error por sentencia, y lo que sigue al error se sigue analizando #

void fop3(int x, int y)
{
    x = y;
}

void main()
{
    int a, b;

    a = 2; b = 3;

    a = + + b;
    a = - - b;
    a = !-;
    fop3(-, b);
}

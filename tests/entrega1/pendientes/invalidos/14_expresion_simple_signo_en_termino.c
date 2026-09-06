# Expectativa: Error 57: Simbolo inesperado o falta simb. al comienzo de factor #
# Prueba: el signo unario solo es legal en la cabeza de <expresion simple>. Los operandos de la repeticion son <termino> y los de <termino> son <factor>, y ni FIRST(termino) ni FIRST(factor) contienen + ni -. Cada signo mal ubicado es un error de factor, y el operando que le sigue se recupera #

void main()
{
    int a, b, c;

    a = 2; b = 3; c = 5;

    a = b - -c;
    a = b || -c;
    a = b * -c;
}

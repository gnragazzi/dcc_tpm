# Expectativa: Error 56: Simbolo inesperado o falta simb. al comienzo de expresion simple #
# Prueba: falta el operando izquierdo de ||. El || es punto de reconfiguracion propio de <expresion simple>: el test frena parado en el, y expresion_simple no puede retornar porque nadie arriba tiene un ciclo sobre + - ||. Debe entrar a su propio while y consumir el resto de la expresion #

void main()
{
    int a, b, c;

    a = 2; b = 3; c = 5;

    if(a < || c)
        b = 1;

    a = || b;
}

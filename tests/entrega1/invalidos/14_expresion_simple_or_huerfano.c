# Expectativa: Error 56 y Error 57 por cada || huerfano #
# Prueba: falta el operando izquierdo de ||. El || es punto de reconfiguracion propio de #
# <expresion simple>: esta en el c2 del test inicial pero no en su c1, asi que el test frena #
# parado en el y reporta 56. El cuerpo corre igual: termino() delega en factor, que reporta 57 #
# sobre el ||; recien despues el while de <resto expresion simple> lo consume y reconoce el #
# resto de la expresion. Fija que el || siga en el c2 del test: sin el, la resincronizacion se #
# lleva puesta la expresion entera, porque ningun nivel de arriba cicla sobre + - ||. #

void main()
{
    int a, b, c;

    a = 2; b = 3; c = 5;

    if(a < || c)
        b = 1;

    a = || b;
}

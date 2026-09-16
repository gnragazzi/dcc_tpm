# Expectativa: compilacion limpia, 0 errores sintacticos #
# Prueba: signo unario cuando el folset heredado contiene + y -. Dentro de <factor> ::= ! <expresion> nada sigue a <expresion>, asi que folset(expresion) = folset(factor), que incluye los operadores de <expresion simple> y de <termino>. El + o - que sigue al ! esta a la vez en FIRST(expresion simple) y en el folset heredado #

int fop2(int x, int y)
{
    return x + y;
}

void main()
{
    int a, b, c;
    int v[10];

    a = 2; b = 3; c = 5;

    a = !-b;
    a = !+b;
    a = !-b || c;
    a = !-b && c;
    a = !-b + c;
    a = c * !-b;
    a = !(a < b) || c;
    a = -(a < b) || c;

    c = fop2(!-a, !+b);

    v[!-a] = b;

    if(!-a < b)
        c = -a;

    while(!-a)
        a = a + 1;

    cout << !-a;
}

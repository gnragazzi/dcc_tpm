# Expectativa: compilacion limpia, 0 errores sintacticos #
# Prueba: el signo unario opcional de <expresion simple> en todos sus contextos de folset (asignacion, argumento, condicion, indice, salida). Ninguno debe reportar error ni perder tokens #

int fop(int a, int b)
{
    return a + b;
}

void main()
{
    int a, b, c;
    int v[10];

    a = 2; b = 3; c = 5;

    a = -b;
    a = +b;
    a = -b * c;
    a = -b + c - a;
    a = -b || c;
    a = -b * c || a && b;

    c = fop(-a, +b);

    v[-a] = b;
    a = v[-b];

    if(-a < b)
        c = -a;

    while(-a < b)
        a = a + 1;

    cout << -a << +b;
}

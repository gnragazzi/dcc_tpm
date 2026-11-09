# Expectativa: errores 71, 83; no se genera .o y el compilador no se rompe #
# Prueba: un error temprano seguido de asignaciones validas raras #

void main()
{
    int a, b;
    float f;
    a = x;
    f = a = b = 2;
    a = !b = 3;
    cout << (b = a) << f;
}

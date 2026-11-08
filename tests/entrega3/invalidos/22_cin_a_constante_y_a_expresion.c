# Expectativa: errores 59, 17, 95, 23, 23; no se genera .o y el compilador no se rompe #
# Prueba: cin a una constante y a una expresion #

void main()
{
    int a, b;
    cin >> 3;
    cin >> a + b;
}

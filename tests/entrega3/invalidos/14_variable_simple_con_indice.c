# Expectativa: errores 78; no se genera .o y el compilador no se rompe #
# Prueba: asignacion a una variable simple usada como arreglo #

void main()
{
    int a;
    a[0] = 1;
}

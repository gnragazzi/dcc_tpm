# Expectativa: errores 82; no se genera .o y el compilador no se rompe #
# Prueba: una suma a la izquierda de la asignacion #

void main()
{
    int a;
    a + 1 = 2;
}

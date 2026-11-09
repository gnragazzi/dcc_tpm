# Expectativa: errores 82; no se genera .o y el compilador no se rompe #
# Prueba: una constante a la izquierda de la asignacion #

void main()
{
    int a;
    3 = a;
}

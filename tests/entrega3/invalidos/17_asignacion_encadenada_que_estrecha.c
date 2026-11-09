# Expectativa: errores 83; no se genera .o y el compilador no se rompe #
# Prueba: asignacion encadenada que intenta pasar un float a un int #

void main()
{
    int i;
    float f;
    i = f = 2.5;
}

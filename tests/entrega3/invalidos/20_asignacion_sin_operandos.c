# Expectativa: errores 56, 57, 83, 82, 83, 56, 57, 83; no se genera .o y el compilador no se rompe #
# Prueba: asignaciones a las que les falta un operando #

void main()
{
    int a, b;
    a = = 3;
    a = b = ;
}

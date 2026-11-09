# Expectativa: errores 71, 78, 83; no se genera .o y el compilador no se rompe #
# Prueba: arreglo no declarado con una asignacion como indice #

void main()
{
    int a;
    x[a = 1] = 2;
}

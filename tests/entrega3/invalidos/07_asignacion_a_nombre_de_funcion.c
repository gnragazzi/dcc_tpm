# Expectativa: errores 20, 21, 82; no se genera .o y el compilador no se rompe #
# Prueba: asignacion a un identificador de funcion #

int f()
{
    return 1;
}

void main()
{
    f = 2;
}

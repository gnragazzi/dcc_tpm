# Expectativa: errores 71, 83; no se genera .o y el compilador no se rompe #
# Prueba: asignacion a una variable declarada en un bloque hermano #

void main()
{
    {
        int a;
    }
    {
        a = 1;
    }
}

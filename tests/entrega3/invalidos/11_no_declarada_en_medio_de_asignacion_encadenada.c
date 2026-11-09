# Expectativa: errores 71, 83, 83; no se genera .o y el compilador no se rompe #
# Prueba: el destino del medio de una asignacion encadenada no esta declarado #

void main()
{
    int a;
    a = x = 3;
}

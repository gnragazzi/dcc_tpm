# Expectativa: errores 73, 83; no se genera .o y el compilador no se rompe #
# Prueba: asignacion a una variable declarada void #

void main()
{
    void v;
    v = 1;
}

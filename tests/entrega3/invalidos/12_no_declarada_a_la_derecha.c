# Expectativa: errores 71, 83; no se genera .o y el compilador no se rompe #
# Prueba: un identificador no declarado en la expresion de la derecha #

void main()
{
    int a;
    a = x + 1;
}

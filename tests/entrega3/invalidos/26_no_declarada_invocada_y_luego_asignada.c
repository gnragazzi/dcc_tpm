# Expectativa: errores 71, 20, 21, 82, 83; no se genera .o y el compilador no se rompe #
# Prueba: un identificador no declarado se invoca y despues se asigna #

void main()
{
    x();
    x = 1;
}

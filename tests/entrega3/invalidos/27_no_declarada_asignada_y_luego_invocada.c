# Expectativa: errores 71, 83, 23, 56, 57; no se genera .o y el compilador no se rompe #
# Prueba: un identificador no declarado se asigna y despues se invoca #

void main()
{
    x = 1;
    x();
}

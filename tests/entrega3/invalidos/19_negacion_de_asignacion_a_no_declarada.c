# Expectativa: errores 71, 83, 83; no se genera .o y el compilador no se rompe #
# Prueba: el operando de ! asigna a un identificador no declarado #

void main()
{
    int a;
    a = !x = 3;
}

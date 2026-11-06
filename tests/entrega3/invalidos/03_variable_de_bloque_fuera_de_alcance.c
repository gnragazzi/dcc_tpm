# Expectativa: Error 71: Identificador no declarado, Error 95 por el tipo erroneo que queda en cout, y no se genera .o #
# Prueba: una variable declarada en un bloque se usa despues de que el bloque termino #

void main()
{
    int a;
    {
        int b = 1;
    }
    cout << b;
}

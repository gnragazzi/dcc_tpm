# Expectativa: errores 71, 83, 95; no se genera .o y el compilador no se rompe #
# Prueba: cout de una asignacion a un identificador no declarado #

void main()
{
    cout << (x = 1);
}

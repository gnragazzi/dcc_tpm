# Expectativa: imprime b #
# Prueba: un bloque vacio es una rama valida #

void main()
{
    if (1) { } else { cout << "a"; }
    if (0) { }
    cout << "b";
}

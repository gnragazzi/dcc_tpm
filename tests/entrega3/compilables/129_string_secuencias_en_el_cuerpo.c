# Expectativa: imprime una fila por vuelta, con las columnas separadas por tab #
# Prueba: strings con secuencias dentro de un while #

void main()
{
    int i = 0;
    while (i < 3)
    {
        cout << i << "\t" << i * 2 << "\n";
        i = i + 1;
    }
}

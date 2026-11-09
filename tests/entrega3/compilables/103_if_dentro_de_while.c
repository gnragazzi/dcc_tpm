# Expectativa: imprime 5 5 #
# Prueba: un if sin bloque dentro del cuerpo: cuenta pares e impares #

void main()
{
    int i = 0;
    int p = 0;
    int q = 0;
    while (i < 10)
    {
        if (i - i / 2 * 2 == 0) p = p + 1; else q = q + 1;
        i = i + 1;
    }
    cout << p << " " << q;
}

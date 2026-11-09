# Expectativa: imprime 111 #
# Prueba: programa: pasos de Collatz desde 27 #

void main()
{
    int n = 27;
    int pasos = 0;
    while (n != 1)
    {
        if (n - n / 2 * 2 == 1) n = 3 * n + 1; else n = n / 2;
        pasos = pasos + 1;
    }
    cout << pasos;
}

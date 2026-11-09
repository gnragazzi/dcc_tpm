# Expectativa: imprime 120 #
# Prueba: programa: factorial de 5 #

void main()
{
    int n = 5;
    int f = 1;
    while (n > 1)
    {
        f = f * n;
        n = n - 1;
    }
    cout << f;
}

# Expectativa: imprime 12 #
# Prueba: la condicion se reevalua con los valores actuales #

void main()
{
    char b = '1';
    char c = '2';
    int n = 0;
    while (b < c)
    {
        n = n + 1;
        b = c;
    }
    cout << n << b;
}

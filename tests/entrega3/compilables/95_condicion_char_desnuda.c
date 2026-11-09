# Expectativa: imprime 3 #
# Prueba: while sobre un char sin operar: se evalua un solo byte #

char z;

void main()
{
    char c = 'a';
    int n = 0;
    while (c)
    {
        n = n + 1;
        if (n == 3) c = z;
    }
    cout << n;
}

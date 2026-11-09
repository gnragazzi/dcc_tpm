# Expectativa: imprime 2 3 5 7 11 13 17 19 f #
# Prueba: programa: primos hasta 20 con while anidados e if #

void main()
{
    int n = 2;
    while (n <= 20)
    {
        int d = 2;
        int p = 1;
        while (d * d <= n)
        {
            if (n - n / d * d == 0) p = 0;
            d = d + 1;
        }
        if (p)
        {
            cout << n << " ";
        }
        n = n + 1;
    }
    cout << "f";
}

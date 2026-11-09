# Expectativa: imprime 4 1.000000 #
# Prueba: while comparando un float #

void main()
{
    float f = 0.0;
    int n = 0;
    while (f < 1.0)
    {
        f = f + 0.25;
        n = n + 1;
    }
    cout << n << " " << f;
}

# Expectativa: imprime 5 0.000000 #
# Prueba: while sobre un float sin operar #

void main()
{
    float f = 2.5;
    int n = 0;
    while (f)
    {
        f = f - 0.5;
        n = n + 1;
    }
    cout << n << " " << f;
}

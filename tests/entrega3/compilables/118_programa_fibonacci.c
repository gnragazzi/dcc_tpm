# Expectativa: imprime 0 1 1 2 3 5 8 13 21 34 f #
# Prueba: programa: primeros diez numeros de Fibonacci #

void main()
{
    int a = 0;
    int b = 1;
    int i = 0;
    while (i < 10)
    {
        int t;
        cout << a << " ";
        t = a + b;
        a = b;
        b = t;
        i = i + 1;
    }
    cout << "f";
}

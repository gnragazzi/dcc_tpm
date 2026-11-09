# Expectativa: imprime 11 #
# Prueba: una rama con locales que no se ejecuta no altera la pila #

void main()
{
    int a = 11;
    if (0)
    {
        int x = 1;
        int y = 2;
        cout << x + y;
    }
    cout << a;
}

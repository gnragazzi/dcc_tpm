# Expectativa: imprime 1 2 9 #
# Prueba: un bloque hermano posterior al while reutiliza la pila #

void main()
{
    int m = 9;
    {
        int a = 1;
        while (a < 1) a = a + 1;
        cout << a << " ";
    }
    {
        int b = 2;
        cout << b << " ";
    }
    cout << m;
}

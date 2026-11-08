# Expectativa: imprime 7 8 1 #
# Prueba: proposiciones de expresion que dejan un valor sin usar, seguidas de un bloque que declara #

void main()
{
    int a = 1;
    a + 1;
    3;
    a;
    'c';
    2.5;
    (a);
    {
        int x = 7;
        int y = 8;
        cout << x << " " << y;
    }
    cout << " " << a;
}

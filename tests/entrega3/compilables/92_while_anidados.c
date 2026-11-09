# Expectativa: imprime 123246369 #
# Prueba: dos while anidados: tabla de multiplicar #

void main()
{
    int i = 1;
    while (i <= 3)
    {
        int j = 1;
        while (j <= 3)
        {
            cout << i * j;
            j = j + 1;
        }
        i = i + 1;
    }
}

# Expectativa: imprime 3 3 3 #
# Prueba: el cuerpo modifica variables globales y de bloques exteriores #

int g;

void main()
{
    int a = 0;
    {
        int b = 0;
        int i = 3;
        while (i)
        {
            g = g + 1;
            a = a + 1;
            b = b + 1;
            i = i - 1;
        }
        cout << g << " " << a << " " << b;
    }
}

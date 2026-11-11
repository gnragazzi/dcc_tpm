# Expectativa: imprime 13 3 #
# Prueba: globales y locales homonimas en distintos niveles dentro de un while #

int n = 0;
int i = 5;

void main()
{
    int i = 0;
    while (i < 3)
    {
        if (i < 2) { int n = 100; n = n + 1; } else n = n + 10;
        n = n + 1;
        i = i + 1;
    }
    cout << n << " " << i;
}

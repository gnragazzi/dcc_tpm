# Expectativa: imprime 1024.000000 #
# Prueba: programa: potencia con acumulador float #

void main()
{
    float x = 1.0;
    int i = 0;
    while (i < 10)
    {
        x = x * 2;
        i = i + 1;
    }
    cout << x;
}

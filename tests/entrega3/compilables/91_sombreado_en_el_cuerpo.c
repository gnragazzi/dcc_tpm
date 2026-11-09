# Expectativa: imprime 561 #
# Prueba: una local del cuerpo sombrea a la exterior sin modificarla #

void main()
{
    int x = 1;
    int i = 0;
    while (i < 2)
    {
        int x = 5;
        x = x + i;
        cout << x;
        i = i + 1;
    }
    cout << x;
}

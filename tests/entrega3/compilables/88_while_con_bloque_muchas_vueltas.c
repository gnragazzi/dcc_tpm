# Expectativa: imprime 20000 #
# Prueba: 20000 vueltas con bloque no desbordan el stack #

void main()
{
    int i = 20000;
    int s = 0;
    while (i)
    {
        s = s + 1;
        i = i - 1;
    }
    cout << s;
}

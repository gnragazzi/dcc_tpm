# Expectativa: imprime 20000 #
# Prueba: las locales del cuerpo se liberan en cada vuelta #

void main()
{
    int i = 20000;
    int s = 0;
    while (i)
    {
        int a = 1;
        float f = 2.5;
        char c = 'x';
        s = s + a;
        i = i - 1;
    }
    cout << s;
}

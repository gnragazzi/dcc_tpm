# Expectativa: imprime 11 33 #
# Prueba: tras un while sin bloque se conservan las locales exteriores #

void main()
{
    int a = 11;
    int guarda = 33;
    {
        int n = 3;
        while (n) n = n - 1;
    }
    cout << a << " " << guarda;
}

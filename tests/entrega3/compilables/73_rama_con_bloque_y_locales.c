# Expectativa: imprime 231 #
# Prueba: las ramas con bloque manejan sus locales y sombreado #

void main()
{
    int v = 1;
    if (v)
    {
        int v = 2;
        cout << v;
        {
            int w = 3;
            cout << w;
        }
    }
    else
    {
        int v = 4;
        cout << v;
    }
    cout << v;
}

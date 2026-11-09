# Expectativa: imprime 0 #
# Prueba: cada iteracion libera todo lo apilado; si una cadena deja bytes, 6000 vueltas desbordan el stack #

void main()
{
    int i = 6000;
    int r;
    char c;
    while (i)
    {
        r = c = 'a';
        i = i - 1;
    }
    cout << i;
}

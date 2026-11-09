# Expectativa: imprime a 1.500000 0 #
# Prueba: 20000 vueltas con ramas de distinto tamano no desbordan ni desbalancean #

char c;
float f;

void main()
{
    int i = 20000;
    while (i)
    {
        if (i > 10000) c = 'a'; else f = 1.5;
        i = i - 1;
    }
    cout << c << " " << f << " " << i;
}

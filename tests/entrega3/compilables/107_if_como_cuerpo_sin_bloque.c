# Expectativa: imprime a 1.500000 0 #
# Prueba: un if sin bloque como cuerpo del while, muchas vueltas #

char c;
float f;

void main()
{
    int i = 20000;
    while (i = i - 1) if (i > 10000) c = 'a'; else f = 1.5;
    cout << c << " " << f << " " << i;
}

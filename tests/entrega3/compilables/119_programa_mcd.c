# Expectativa: imprime 6 #
# Prueba: programa: maximo comun divisor por restas, cuerpo sin bloque #

void main()
{
    int a = 48;
    int b = 18;
    while (a != b) if (a > b) a = a - b; else b = b - a;
    cout << a;
}

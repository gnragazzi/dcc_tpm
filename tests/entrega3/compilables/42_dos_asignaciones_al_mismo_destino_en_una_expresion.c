# Expectativa: imprime 12 4 #
# Prueba: orden de evaluacion de izquierda a derecha #

void main()
{
    int a, b;
    a = (b = 3) * (b = 4);
    cout << a << " " << b;
}

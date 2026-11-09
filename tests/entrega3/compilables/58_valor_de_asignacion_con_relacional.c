# Expectativa: imprime 1.000000 1.500000 #
# Prueba: el valor de una asignacion tiene el tipo del destino aunque el lado derecho sea relacional #

void main()
{
    char b = '1';
    char c = '2';
    int s = 2;
    float g;
    float h;
    cout << (g = b < c) << " " << (h = s < 3) + 0.5;
}

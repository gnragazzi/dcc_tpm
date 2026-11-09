# Expectativa: imprime 2.000000 1.000000 f #
# Prueba: la condicion del while toma el tipo del destino #

void main()
{
    float g;
    int n = 2;
    while (g = n)
    {
        cout << g << " ";
        n = n - 1;
    }
    cout << "f";
}

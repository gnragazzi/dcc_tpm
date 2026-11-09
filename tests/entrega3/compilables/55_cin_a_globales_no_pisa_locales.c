# Expectativa: imprime 10 x 11 22 (entrada: 10 x) #
# Prueba: leer globales desde un bloque no altera la pila del bloque que lo contiene #

int g;
char k;

void main()
{
    int a = 11;
    int b = 22;
    {
        cin >> g >> k;
    }
    cout << g << " " << k << " " << a << " " << b;
}

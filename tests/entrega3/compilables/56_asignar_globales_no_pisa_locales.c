# Expectativa: imprime 5 x 11 22 #
# Prueba: asignar globales desde un bloque no altera la pila del bloque que lo contiene #

int g;
char k;

void main()
{
    int a = 11;
    int b = 22;
    {
        g = 5;
        k = 'x';
    }
    cout << g << " " << k << " " << a << " " << b;
}

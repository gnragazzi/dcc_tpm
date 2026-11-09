# Expectativa: imprime 11 33 #
# Prueba: una expresion sin asignacion como rama no deja valores en la pila #

void main()
{
    int a = 11;
    int guarda = 33;
    {
        if (0) 3 + 4; else 'x';
        if (1) 1.5;
    }
    cout << a << " " << guarda;
}

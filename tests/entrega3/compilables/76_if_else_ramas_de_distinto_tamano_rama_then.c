# Expectativa: imprime 11 33 x #
# Prueba: ramas sin bloque que asignan tipos de distinto tamano: se toma la de 1 byte #

char c;
float f;

void main()
{
    int a = 11;
    int guarda = 33;
    {
        if (1) c = 'x'; else f = 2.5;
    }
    cout << a << " " << guarda << " " << c;
}

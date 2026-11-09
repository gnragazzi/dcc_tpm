# Expectativa: imprime 11 33 2.500000 #
# Prueba: ramas sin bloque que asignan tipos de distinto tamano: se toma la de 4 bytes #

char c;
float f;

void main()
{
    int a = 11;
    int guarda = 33;
    {
        if (0) c = 'x'; else f = 2.5;
    }
    cout << a << " " << guarda << " " << f;
}

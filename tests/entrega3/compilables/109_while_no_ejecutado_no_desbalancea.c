# Expectativa: imprime 11 33 0 #
# Prueba: una asignacion en un cuerpo no ejecutado no debe contarse como apilada #

int g;

void main()
{
    int a = 11;
    int guarda = 33;
    {
        while (0) g = 1;
    }
    cout << a << " " << guarda << " " << g;
}

# Expectativa: imprime 11 33 22 0 #
# Prueba: una asignacion en una rama no ejecutada no debe contarse como apilada #

int g;

void main()
{
    int a = 11;
    {
        int b = 22;
        int guarda = 33;
        {
            if (0) g = 1;
        }
        cout << a << " " << guarda << " " << b << " " << g;
    }
}

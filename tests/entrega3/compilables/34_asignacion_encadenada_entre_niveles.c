# Expectativa: imprime 4 4 #
# Prueba: una asignacion encadenada escribe en variables de cuatro niveles distintos #

int g;

void main()
{
    int l;
    {
        int b;
        g = l = b = 4;
    }
    cout << g << " " << l;
}

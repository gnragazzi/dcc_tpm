# Expectativa: imprime 11 #
# Prueba: asignacion a una global desde un bloque anidado de dos niveles #

int g = 1;

void main()
{
    {
        {
            g = g + 10;
        }
    }
    cout << g;
}

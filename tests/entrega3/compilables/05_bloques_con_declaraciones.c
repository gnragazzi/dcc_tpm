# Expectativa: genera .o y su ejecucion termina sin imprimir nada #
# Prueba: bloques anidados y hermanos que declaran variables, con y sin inicializador #

int g = 1;

void main()
{
    int m = 2;
    {
        int a = 3;
        float b;
        {
            char c = 'z';
            int d = 4;
            {
                float e = 5.5;
            }
        }
        {
            int f = 6;
        }
    }
    {
        char h;
        int i = 7;
    }
}

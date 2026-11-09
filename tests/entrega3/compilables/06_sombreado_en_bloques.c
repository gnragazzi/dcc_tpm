# Expectativa: genera .o y su ejecucion termina sin imprimir nada #
# Prueba: el mismo nombre declarado en el nivel global, en main y en bloques anidados, con distinto tipo #

int v = 1;

void main()
{
    float v = 2.5;
    {
        char v = 'c';
        {
            int v = 4;
        }
    }
}

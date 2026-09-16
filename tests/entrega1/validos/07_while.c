# Expectativa: compilacion limpia, 0 errores sintacticos #
# Prueba: bucles while simples y anidados con condiciones relacionales #

void main()
{
    int i;
    int j;
    int total;

    i = 0;
    total = 0;

    while(i < 10)
    {
        j = 0;
        while(j < 5)
        {
            total = total + 1;
            j = j + 1;
        }
        i = i + 1;
    }
}

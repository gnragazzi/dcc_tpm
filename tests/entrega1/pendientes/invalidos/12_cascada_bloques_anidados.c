# Expectativa: Errores sintácticos en bloques anidados recuperados limpiamente #
# Prueba: Errores en cascada en estructuras de control anidadas (Consignas 13 y 14) #

void main()
{
    int i, sum, limite;
    i = 0;
    sum = 0;
    limite = 10;

    while(i < limite)
    {
        if(i <= 5)
        {
            * sum = sum + i;
            i = i + 1
        }
        else
        {
            sum = sum + ;
        }
    }
}

# Expectativa: cascada de errores en bloques anidados. Devolución punto 4: sin el test intermedio #
# de proposicion_compuesta (eliminado), un símbolo intruso al comienzo de un bloque hace que ese #
# bloque se dé por cerrado en el primer } que encuentra, y el resto de su contenido se reinterpreta #
# como sentencias del nivel exterior #
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

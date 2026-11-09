# Expectativa: sin errores, Warning 36 y no se genera .o #
# Prueba: un arreglo declarado en un bloque anidado queda fuera del alcance de la generacion de codigo #

void main()
{
    int a = 1;
    {
        int v[3];
    }
}

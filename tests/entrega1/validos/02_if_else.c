# Expectativa: compilacion limpia, 0 errores sintacticos #
# Prueba: proposiciones if, if-else anidados y operadores logicos #

void main()
{
    int a;
    int b;
    int max;

    a = 15;
    b = 20;

    if(a > b)
    {
        max = a;
    }
    else
    {
        max = b;
    }

    if(a > 0 && b > 0)
    {
        max = max + 1;
    }

    if(a == 0 || b == 0)
    {
        max = 0;
    }
}

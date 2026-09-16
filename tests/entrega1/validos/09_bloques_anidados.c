# Expectativa: compilacion limpia, 0 errores sintacticos #
# Prueba: proposiciones compuestas anidadas con declaraciones locales #

void main()
{
    int x;
    x = 10;

    {
        int y;
        y = x * 2;

        {
            int z;
            z = y + 5;
            x = z;
        }
    }
}

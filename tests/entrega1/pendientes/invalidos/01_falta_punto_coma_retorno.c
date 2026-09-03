# Expectativa: Error 23: Falta ; #
# Prueba: Omision de punto y coma al final de proposicion de retorno #

int fcalc(int x)
{
    return x + 1
}

void main()
{
    int res;
    res = fcalc(5);
}

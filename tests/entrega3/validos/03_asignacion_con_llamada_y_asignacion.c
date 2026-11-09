# Expectativa: sin errores, Warning 36 y no se genera .o #
# Prueba: una llamada y una asignacion en la misma expresion #

int f()
{
    return 1;
}

void main()
{
    int a;
    a = f() + (a = 2);
}

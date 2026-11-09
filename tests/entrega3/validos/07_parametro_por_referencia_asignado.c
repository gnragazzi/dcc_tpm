# Expectativa: sin errores, Warning 36 y no se genera .o #
# Prueba: asignacion encadenada a un parametro por referencia #

void p(int &x)
{
    x = x = 1;
}

void main()
{
    int a;
    p(a);
}

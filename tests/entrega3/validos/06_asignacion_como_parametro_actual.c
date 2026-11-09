# Expectativa: sin errores, Warning 36 y no se genera .o #
# Prueba: una asignacion como parametro actual #

void p(int x)
{
}

void main()
{
    int a;
    p(a = 3);
}

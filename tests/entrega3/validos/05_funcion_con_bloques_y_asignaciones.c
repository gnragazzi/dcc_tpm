# Expectativa: sin errores, Warning 36 y no se genera .o #
# Prueba: una funcion con parametros, bloques y asignaciones encadenadas #

int f(int x)
{
    int y;
    {
        int z;
        z = x;
        y = z = z + 1;
    }
    return y;
}

void main()
{
    int r;
    r = f(2);
    cout << r;
}

# Expectativa: sin errores, Warning 36 y no se genera .o #
# Prueba: un arreglo global en un programa que por lo demas es compilable #

int v[2];

void main()
{
    int a, b;
    a = b = 1;
    cout << a;
}

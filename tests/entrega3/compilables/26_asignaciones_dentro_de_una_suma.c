# Expectativa: imprime 2 3 6.500000 #
# Prueba: dos asignaciones como operandos de la misma expresion #

void main()
{
    int a, b;
    float f;
    f = (a = 2) + (b = 3) * 1.5;
    cout << a << " " << b << " " << f;
}

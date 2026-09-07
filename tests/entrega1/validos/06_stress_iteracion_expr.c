# Expectativa: compilacion limpia, 0 errores sintacticos #
# Prueba: itera intensamente expresion, expresion_simple y termino (con recursion anidada via parentesis y llamada a funcion) para comparar el comportamiento del parser con y sin test en los while de esas tres producciones #

int fop(int a, int b)
{
    return a + b;
}

void main()
{
    int a, b, c, d, x, y, z, w;

    a = 2; b = 3; c = 5; d = 7;

    z = a * b * c * d * a * b * c * d && a && b && c;

    y = a + b - c + d - a + b - c + d || a || b;

    x = a < b < c < d <= a >= b != c == d;

    w = (a + b) * (c - d) / (fop(a, b) + a) && (d || a);
}

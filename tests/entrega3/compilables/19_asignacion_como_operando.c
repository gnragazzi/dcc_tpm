# Expectativa: imprime 1 3 22.000000 #
# Prueba: una asignacion entre parentesis usada como operando (ejemplo de la teoria de sistema de ejecucion) #

void main()
{
    int a = 1, b = 2, c = 3;
    float d;
    d = 5.5 * (a + (b = c));
    cout << a << " " << b << " " << d;
}

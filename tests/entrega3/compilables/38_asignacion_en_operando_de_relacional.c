# Expectativa: imprime 1 5 #
# Prueba: una asignacion como operando derecho de un relacional #

void main()
{
    int a = 1, b;
    cout << (a < (b = 5)) << " " << b;
}

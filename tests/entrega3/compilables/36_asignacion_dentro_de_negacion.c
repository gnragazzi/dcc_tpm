# Expectativa: imprime 3 0 #
# Prueba: el operando de ! es una expresion completa que contiene una asignacion #

void main()
{
    int i, j;
    j = !i = 3;
    cout << i << " " << j;
}

# Expectativa: imprime A2 #
# Prueba: una asignacion como operando de la condicion #

void main()
{
    int x;
    if ((x = 2) > 1) cout << "A"; else cout << "B";
    cout << x;
}

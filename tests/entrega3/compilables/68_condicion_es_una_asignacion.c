# Expectativa: imprime BC 3 #
# Prueba: la condicion usa el valor asignado y la variable queda modificada #

void main()
{
    int x;
    if (x = 0) cout << "A"; else cout << "B";
    if (x = 3) cout << "C"; else cout << "D";
    cout << " " << x;
}

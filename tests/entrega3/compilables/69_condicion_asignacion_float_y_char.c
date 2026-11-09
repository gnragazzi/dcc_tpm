# Expectativa: imprime A1.000000CxE #
# Prueba: la condicion toma el tipo del destino de la asignacion #

void main()
{
    float g;
    char c;
    int s = 1;
    if (g = s) cout << "A"; else cout << "B";
    cout << g;
    if (c = 'x') cout << "C";
    cout << c;
    if (g = 0) cout << "D"; else cout << "E";
}

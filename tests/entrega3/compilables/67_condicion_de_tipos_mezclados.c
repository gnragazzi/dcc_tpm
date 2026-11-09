# Expectativa: imprime BCDF #
# Prueba: condiciones que combinan int y float #

void main()
{
    int s = 2;
    if (s - 2.0) cout << "A"; else cout << "B";
    if (s * 0.5) cout << "C";
    if (s > 1.5) cout << "D";
    if (1.5 > s) cout << "E"; else cout << "F";
}

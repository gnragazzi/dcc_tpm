# Expectativa: imprime ACDEGHJ #
# Prueba: operar char deja un int: la condicion debe evaluarlo como int #

void main()
{
    char b = '1';
    char c = '2';
    if (b + c) cout << "A";
    if (b - b) cout << "B"; else cout << "C";
    if (-b) cout << "D";
    if (b < c) cout << "E";
    if (c < b) cout << "F"; else cout << "G";
    if (b && c) cout << "H";
    if (!b) cout << "I"; else cout << "J";
}

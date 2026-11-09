# Expectativa: imprime dos otro #
# Prueba: else if encadenados: se ejecuta solo la primera rama verdadera #

void main()
{
    int n = 2;
    if (n == 1) cout << "uno"; else if (n == 2) cout << "dos"; else if (n == 3) cout << "tres"; else cout << "otro";
    cout << " ";
    n = 7;
    if (n == 1) cout << "uno"; else if (n == 2) cout << "dos"; else if (n == 3) cout << "tres"; else cout << "otro";
}

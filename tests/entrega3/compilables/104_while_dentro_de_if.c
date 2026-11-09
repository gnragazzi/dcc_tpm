# Expectativa: imprime 3210 #
# Prueba: un while como rama de un if #

void main()
{
    int n = 3;
    if (n) while (n) { cout << n; n = n - 1; } else cout << "no";
    cout << n;
}

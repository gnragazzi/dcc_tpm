# Expectativa: imprime 7 1 (entrada: 5 7) #
# Prueba: una rama puede leer de la entrada #

void main()
{
    int n;
    int m;
    cin >> n;
    if (n) cin >> m; else m = 1;
    cout << m << " ";
    if (n - 5) cin >> m; else m = 1;
    cout << m;
}

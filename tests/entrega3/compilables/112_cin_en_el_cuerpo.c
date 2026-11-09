# Expectativa: imprime 12 (entrada: 3 4 5 0) #
# Prueba: lectura con centinela #

void main()
{
    int n;
    int s = 0;
    cin >> n;
    while (n)
    {
        s = s + n;
        cin >> n;
    }
    cout << s;
}

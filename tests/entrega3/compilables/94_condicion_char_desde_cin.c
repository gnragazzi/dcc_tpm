# Expectativa: imprime abc! (entrada: a b c .) #
# Prueba: la condicion compara un char leido de la entrada #

void main()
{
    char c;
    cin >> c;
    while (c != '.')
    {
        cout << c;
        cin >> c;
    }
    cout << "!";
}

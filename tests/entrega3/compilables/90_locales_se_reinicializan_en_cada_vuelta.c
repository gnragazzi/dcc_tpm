# Expectativa: imprime 0 10 20 f #
# Prueba: cada vuelta crea e inicializa las locales de nuevo #

void main()
{
    int i = 0;
    while (i < 3)
    {
        int v;
        v = i * 10;
        cout << v << " ";
        v = v + 1;
        i = i + 1;
    }
    cout << "f";
}

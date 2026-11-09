# Expectativa: imprime 30 10 (entrada: 10 20) #
# Prueba: lectura a una global y a una variable de bloque #

int g;

void main()
{
    {
        int b;
        cin >> g >> b;
        cout << g + b;
    }
    cout << " " << g;
}

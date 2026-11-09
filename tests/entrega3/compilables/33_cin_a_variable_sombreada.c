# Expectativa: imprime 9 1 (entrada: 9) #
# Prueba: cin escribe en la declaracion mas cercana #

void main()
{
    int v = 1;
    {
        int v;
        cin >> v;
        cout << v;
    }
    cout << " " << v;
}

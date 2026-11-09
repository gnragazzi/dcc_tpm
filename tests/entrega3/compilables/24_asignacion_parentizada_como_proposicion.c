# Expectativa: imprime 5 9 5 #
# Prueba: asignaciones entre parentesis usadas como proposicion, seguidas de un bloque que declara #

void main()
{
    int a;
    (a = 4);
    ((a = a + 1));
    {
        int x = 9;
        cout << a << " " << x;
    }
    cout << " " << a;
}

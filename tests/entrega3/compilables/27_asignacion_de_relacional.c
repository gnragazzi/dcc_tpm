# Expectativa: imprime 1 0.000000 1 #
# Prueba: la asignacion tiene menor precedencia que el relacional: g = (2 > 3) #

void main()
{
    int r;
    float g;
    char c = 'a';
    r = 3 < 5;
    g = 2 > 3;
    cout << r << " " << g;
    r = c == 97;
    cout << " " << r;
}

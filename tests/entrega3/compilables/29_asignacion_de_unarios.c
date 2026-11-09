# Expectativa: imprime -5 -2.500000 5 -97 2.500000 -5.000000 #
# Prueba: signo menos y mas sobre int, float, char y parentesis #

void main()
{
    int i = 5;
    float f = 2.5;
    char c = 'a';
    int j;
    float g;
    j = -i;
    cout << j << " ";
    g = -f;
    cout << g << " ";
    j = +i;
    cout << j << " ";
    j = -c;
    cout << j << " ";
    g = -(-f);
    cout << g << " ";
    g = -i;
    cout << g;
}

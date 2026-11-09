# Expectativa: imprime abc 60 0.750000 c40 0.250000 #
# Prueba: variables de 1 y 4 bytes intercaladas; lectura y asignacion de cada una #

void main()
{
    char c1 = 'a';
    int i1 = 10;
    char c2 = 'b';
    float f1 = 0.5;
    int i2 = 20;
    char c3 = 'c';
    float f2 = 0.25;
    int i3 = 30;
    cout << c1 << c2 << c3 << " " << i1 + i2 + i3 << " " << f1 + f2;
    i2 = i1 + i3;
    c2 = c3;
    f1 = f2;
    cout << " " << c2 << i2 << " " << f1;
}

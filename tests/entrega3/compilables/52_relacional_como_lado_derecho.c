# Expectativa: imprime 1 1 1.000000 0.000000 0 1 #
# Prueba: en una asignacion, el relacional compara sus operandos y no el tipo del destino #

void main()
{
    char b = '1';
    char c = '2';
    float f = 1.5;
    int r;
    int q;
    int t;
    int u;
    float g;
    float h;
    r = b < c;
    q = f < 2.5;
    g = b < c;
    h = b > c;
    t = c < b;
    u = c > b;
    cout << r << " " << q << " " << g << " " << h << " " << t << " " << u;
}

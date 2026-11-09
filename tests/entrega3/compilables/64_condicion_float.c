# Expectativa: imprime ADEG #
# Prueba: una condicion float distinta de cero es verdadera #

float g;

void main()
{
    float f = 0.5;
    if (f) cout << "A"; else cout << "B";
    if (g) cout << "C"; else cout << "D";
    if (0.25) cout << "E";
    if (0.0) cout << "F"; else cout << "G";
}

# Expectativa: imprime 2599 2552 77.000000 5.500000 4.500000 0 1 #
# Prueba: el operando izquierdo queda debajo y se convierte cuando el derecho resulta mas ancho #

void main()
{
    char b = '1';
    char c = '2';
    char d = '3';
    int s = 2;
    float f = 1.5;
    cout << b + c * d << " " << s + c * d << " " << s + c * 1.5 << " " << f + s * 2;
    cout << " " << f * (s + 1) << " " << b * !c << " " << (b < c + d);
}

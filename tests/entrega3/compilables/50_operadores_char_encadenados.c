# Expectativa: imprime 150 124950 1 -52 #
# Prueba: tras el primer operador entre char, los siguientes operan sobre un int #

void main()
{
    char b = '1';
    char c = '2';
    char d = '3';
    cout << b + c + d << " " << b * c * d << " " << -b + c << " " << b - c - d;
}

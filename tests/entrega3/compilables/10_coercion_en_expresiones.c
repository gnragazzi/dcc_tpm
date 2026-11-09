# Expectativa: imprime 7.500000 104 97.500000 3 3.500000 #
# Prueba: operandos de distinto tipo en la misma operacion #

void main()
{
    int i = 7;
    float f = 0.5;
    char c = 'a';
    cout << i + f << " " << c + i << " " << c + f << " " << i / 2 << " " << i / 2.0;
}

# Expectativa: imprime ADE #
# Prueba: una condicion char ocupa un byte y se evalua como tal #

char z;

void main()
{
    char c = 'a';
    if (c) cout << "A"; else cout << "B";
    if (z) cout << "C"; else cout << "D";
    if ('x') cout << "E"; else cout << "F";
}

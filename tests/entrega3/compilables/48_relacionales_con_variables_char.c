# Expectativa: imprime 1 1 1 1 1 #
# Prueba: relacionales entre variables char y entre char e int #

void main()
{
    char c = 'a';
    char d = 'b';
    cout << (c < d) << " " << (d > c) << " " << (c == 97) << " " << (97 == c) << " " << (c != d);
}

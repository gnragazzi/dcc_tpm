# Expectativa: imprime 195 1 194 -97 97 #
# Prueba: operaciones entre char: el resultado es entero (promocion de C; la MAC tambien deja un int en la pila) #

void main()
{
    char c = 'a';
    char d = 'b';
    cout << c + d << " " << d - c << " " << c * 2 << " " << -c << " " << c + 0;
}

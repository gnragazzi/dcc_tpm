# Expectativa: seis veces Error 83 y no se genera .o #
# Prueba: un operador entre char deja un int y la MAC no tiene conversion de int a char #

void main()
{
    char a;
    char b = '1';
    char c = '2';
    a = b + c;
    a = b * c;
    a = -b;
    a = !b;
    a = b && c;
    a = b < c;
}

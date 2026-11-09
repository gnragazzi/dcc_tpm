# Expectativa: imprime 1 1 0 1 0 #
# Prueba: los logicos operan con el tipo de sus operandos y dejan un int #

void main()
{
    char b = '1';
    char c = '2';
    float f = 1.5;
    float g = 0.0;
    cout << (b && c) << " " << (b || c) << " " << (f && g) << " " << (f || g) << " " << !f;
}

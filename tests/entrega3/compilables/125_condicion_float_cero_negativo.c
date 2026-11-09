# Expectativa: imprime B #
# Prueba: el cero negativo es falso: la condicion float debe compararse como float #

void main()
{
    float f = 0.0;
    float g;
    g = -f;
    if (g) cout << "A"; else cout << "B";
}

# Expectativa: imprime 99 7 7 7 #
# Prueba: los destinos intermedios de una cadena se descuentan en el bloque activo #

int g;

void main()
{
    int a;
    {
        int b;
        int guarda = 33;
        {
            int c;
            g = a = b = c = 7;
        }
        cout << guarda + guarda * 2 << " " << b << " ";
    }
    cout << g << " " << a;
}

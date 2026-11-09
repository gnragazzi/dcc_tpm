# Expectativa: imprime 7 22 #
# Prueba: cada nivel modifica variables de niveles exteriores y se leen al salir #

int g = 0;

void main()
{
    int a = 0;
    {
        int b = 0;
        {
            int c = 0;
            g = a = b = c = 7;
            c = c + 1;
            b = b + c;
        }
        a = a + b;
    }
    cout << g << " " << a;
}

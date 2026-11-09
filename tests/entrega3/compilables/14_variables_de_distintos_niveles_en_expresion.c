# Expectativa: imprime 127 85 #
# Prueba: una expresion lee variables globales, de main y de dos bloques anidados #

int g = 100;

void main()
{
    int m = 20;
    {
        int b = 3;
        {
            int c = 4;
            cout << g + m + b + c << " " << g - m * b / c;
        }
    }
}

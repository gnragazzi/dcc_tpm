# Expectativa: imprime 9 3.000000 #
# Prueba: globales antes de main modificadas en un bloque anidado y una global declarada despues de main #

int g = 7;
float h = 1.5;

void main()
{
    int a = 2;
    {
        g = g + a;
        h = h * a;
    }
    cout << g << " " << h;
}

char c = 'z';

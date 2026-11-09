# Requiere V2 (cout) #
# Expectativa: los inicializadores quedan convertidos al tipo de la variable #
# Prueba: coercion char a int, int a float y char a float en la inicializacion #

int gi = 'a';
float gf = 3;

void main()
{
    float lf = 'b';
    cout << gi << " " << gf << " " << lf;
}

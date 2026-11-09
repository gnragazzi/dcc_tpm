# Requiere V2 (cout) #
# Expectativa: cada uso de v toma la declaracion mas cercana y al salir de un bloque vuelve la anterior #
# Prueba: sombreado en tres niveles y acceso a una global desde el bloque mas profundo #

int v = 1;
int g = 9;

void main()
{
    int v = 2;
    {
        int v = 3;
        {
            int v = 4;
            cout << v << " " << g << " ";
        }
        cout << v << " ";
    }
    cout << v;
}

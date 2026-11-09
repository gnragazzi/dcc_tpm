# Expectativa: imprime 30 7 31 #
# Prueba: asignacion a la declaracion mas cercana sin pisar las exteriores #

int v = 1;
int w = 1;

void main()
{
    int v = 2;
    {
        int v = 3;
        v = 30;
        w = w + v;
        cout << v << " ";
    }
    v = v + 5;
    cout << v << " " << w;
}

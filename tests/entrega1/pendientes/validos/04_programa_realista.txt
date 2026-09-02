# Expectativa: compilacion limpia, 0 errores sintacticos #
# Prueba: programa realista que atraviesa todas las producciones de la gramatica #

int glob, base;
float pesos[5];
int pares[3] = {2, 4, 6};

int fcalc(int n, int & total, int arr[])
{
    int i, sum;
    i = 0;
    sum = 0;

    while(i < n && !(i == 5))
    {
        if(i < 3)
        {
            sum = sum + arr[i];
        }
        else
        {
            sum = sum + i * 2;
        }
        i = i + 1;
    }

    total = sum;
    return sum;
}

void fshow(char letra)
{
    int dato;
    cout << "Ingrese dato: \n";
    cin >> dato;

    if(dato != 0)
    {
        cout << "Letra: " << letra << " Valor: " << dato << "\n";
    }
}

void main()
{
    int cant, res;
    char opt;

    cant = 3;
    base = 10;
    opt = 'X';

    cout << "Iniciando ejecucion realista\n";

    res = fcalc(cant, base, pares);

    {
        int temp;
        temp = res + base;

        if(temp >= 20 || temp == 10)
        {
            cout << "Resultado favorable: " << temp << "\n";
        }
        else
        {
            cout << "Resultado menor: " << temp << "\n";
        }
    }

    fshow(opt);
    cout << "Fin del programa\n";
}

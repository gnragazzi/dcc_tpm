# Expectativa: compilación limpia, 0 errores sintácticos #
# Prueba: programa realista con cobertura total de la gramática BNFE #

int glob = 10;
float tasa = 2.5;
char marca = 'Z';
int a, b, c;
int p1, p2, p3, p4;
int base;
int uno[1] = {42};
int duo[2] = {10, 20};
int pares[3] = {2, 4, 6};
float pesos[5];
int primos[] = {3, 5, 7};

void finit()
{
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

float fdiv(float x, float y)
{
    float res;
    if(y > 0.0)
    {
        res = x / y;
    }
    else
    {
        res = 0.0;
    }
    return res;
}

int fcalc(int n, int & total, int arr[])
{
    int i, sum, paso;
    i = 0;
    sum = 0;
    paso = +1;

    while(i < n && !(i == 5))
    {
        if(i <= 2)
        {
            sum = sum + arr[i] * 1 / paso;
        }
        else
        {
            sum = sum + (i * 2) - paso;
        }
        i = i + paso;
        ;
    }

    total = sum;
    return sum;
}

void main()
{
    int cant, res;
    float val, ratio;
    char opt;

    cant = 3;
    base = 10;
    opt = 'X';
    val = -2.5;

    finit();

    cout << "Iniciando ejecucion realista\n";

    cin >> cant >> base;
    cin >> a >> b >> c;

    res = fcalc(cant, base, pares);
    ratio = fdiv(tasa, 1.25);

    {
        int temp;
        temp = res + base;

        if(temp >= 20 || temp == 10 || temp <= 5)
        {
            cout << "Resultado favorable: " << temp << "\n";
        }
        else
        {
            cout << "Resultado menor: " << temp << "\n";
        }
    }

    {
        int local;
    }

    a = b = c = 0;

    while(cant > 0)
        cant = cant - 1;

    fshow(opt);
    cout << "Fin de programa con ratio: " << ratio << "\n";
}

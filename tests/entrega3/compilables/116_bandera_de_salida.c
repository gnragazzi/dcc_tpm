# Expectativa: imprime 3 #
# Prueba: un if dentro del cuerpo controla la salida del while #

void main()
{
    int i = 0;
    int seguir = 1;
    while (seguir && (i < 10))
    {
        if (i == 3) seguir = 0; else i = i + 1;
    }
    cout << i;
}

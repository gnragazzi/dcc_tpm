# Expectativa: imprime 0 #
# Prueba: 20000 vueltas sin bloque: el valor de la asignacion no debe acumularse en el stack #

void main()
{
    int n = 20000;
    while (n) n = n - 1;
    cout << n;
}

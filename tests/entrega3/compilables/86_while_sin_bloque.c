# Expectativa: imprime 0 #
# Prueba: el cuerpo puede ser una asignacion sin bloque #

void main()
{
    int n = 5;
    while (n) n = n - 1;
    cout << n;
}

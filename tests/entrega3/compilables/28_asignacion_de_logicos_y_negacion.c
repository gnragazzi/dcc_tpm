# Expectativa: imprime 0 1 1 1 1 #
# Prueba: asignacion del resultado de &&, || y ! #

void main()
{
    int i;
    i = 1 && 0;
    cout << i << " ";
    i = 0 || 2.5;
    cout << i << " ";
    i = !0;
    cout << i << " ";
    i = !!5;
    cout << i << " ";
    i = !(3 > 4);
    cout << i;
}

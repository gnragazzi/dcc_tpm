# Expectativa: Múltiples errores en la misma línea reportados sin colapso #
# Prueba: Tres errores sintácticos encadenados en una misma línea (Consigna 13) #

void main()
{
    int a, b, c;
    int total;

    a = 10 + ; ) b = 20; c = * 5;

    total = a + b + c;
    cout << total;
}

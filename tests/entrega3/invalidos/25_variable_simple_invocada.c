# Expectativa: errores 23, 56, 57; no se genera .o y el compilador no se rompe #
# Prueba: una variable simple usada como funcion y luego asignada #

void main()
{
    int a;
    a();
    a = 1;
}

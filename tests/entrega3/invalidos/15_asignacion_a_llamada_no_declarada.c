# Expectativa: errores 71, 82, 83; no se genera .o y el compilador no se rompe #
# Prueba: asignacion al resultado de llamar a una funcion no declarada #

void main()
{
    g() = 1;
}

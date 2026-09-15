# Expectativa: compilacion limpia, 0 errores sintacticos #
# Prueba: arreglo local con dimension e inicializador, declaracion escalar y bloque anidado #
# con declaracion propia: ninguna forma valida entra por un punto de reconfiguracion. #

void main()
{
    int v[3] = {1, 2, 3};
    int w;
    {
        int z;
    }
}

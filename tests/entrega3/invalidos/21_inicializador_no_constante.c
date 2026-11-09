# Expectativa: errores 63, 62, 83, 64; no se genera .o y el compilador no se rompe #
# Prueba: inicializadores que no son constantes #

int g = 1 + 2;

void main()
{
    int a = g;
}

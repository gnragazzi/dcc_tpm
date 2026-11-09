# Expectativa: tres veces Error 83 y no se genera .o #
# Prueba: los errores semanticos dentro de ramas y cuerpos se reportan y evitan el objeto #

void main()
{
    char a;
    char b = '1';
    if (b) a = b + b; else a = -b;
    while (b) a = b * b;
}

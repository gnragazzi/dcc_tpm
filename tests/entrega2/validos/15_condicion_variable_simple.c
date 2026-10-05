# Expectativa: compilacion limpia, 0 errores semanticos #
# Prueba: variables simples char, int y float como condicion de if y while #

void main(){
    char c;
    int i;
    float f;

    if (c)
        i = 1;
    if (i)
        i = 2;
    while (f)
        i = 3;
}

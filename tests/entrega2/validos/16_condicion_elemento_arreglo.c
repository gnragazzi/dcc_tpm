# Expectativa: compilacion limpia, 0 errores semanticos #
# Prueba: elemento de arreglo como condicion de if y while #

void main(){
    int a[2];
    int i;

    if (a[0])
        i = 1;
    while (a[1])
        i = 2;
}

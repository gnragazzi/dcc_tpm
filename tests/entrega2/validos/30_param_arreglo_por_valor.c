# Expectativa: compilacion limpia, 0 errores semanticos #
# Prueba: parametro arreglo por valor con el nombre de un arreglo #

void f(int a[]){}

void main(){
    int v[2];
    f(v);
}

# Expectativa: compilacion limpia, 0 errores semanticos #
# Prueba: parametro por referencia con un elemento de arreglo #

void f(int & a){}

void main(){
    int v[2];
    f(v[0]);
}

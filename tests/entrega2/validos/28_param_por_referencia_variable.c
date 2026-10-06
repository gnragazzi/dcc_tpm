# Expectativa: compilacion limpia, 0 errores semanticos #
# Prueba: parametro por referencia con una variable simple #

void f(int & a){}

void main(){
    int x;
    f(x);
}

# Expectativa: compilacion limpia, 0 errores semanticos #
# Prueba: parametro por valor con una expresion #

void f(int a){}

void main(){
    int x;
    f(x + 1);
}

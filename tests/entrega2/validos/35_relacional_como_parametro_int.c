# Expectativa: compilacion limpia, 0 errores semanticos #
# Prueba: resultado de un operador relacional como parametro actual por valor de tipo int #

void f(int a){}

void main(){
    float x, y;
    f(x != y);
}

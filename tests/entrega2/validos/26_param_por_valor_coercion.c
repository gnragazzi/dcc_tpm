# Expectativa: compilacion limpia, 0 errores semanticos #
# Prueba: parametros por valor con coercion (char a int, char a float, int a float) #

void f(int a, float b, float c){}

void main(){
    char x;
    int y;
    f(x, x, y);
}

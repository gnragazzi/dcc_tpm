# Expectativa: compilacion limpia, 0 errores semanticos #
# Prueba: parametros reconocidos por posicion, con nombres distintos de los formales #

void f(int a, float b){}

void main(){
    int b;
    float a;
    f(b, a);
}

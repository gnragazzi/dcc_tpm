# Expectativa: compilacion limpia, 0 errores semanticos #
# Prueba: resultado de operadores logicos entre floats asignado a un int (el resultado es int) #

void main(){
    float a, b;
    int res;
    res = (a && b);
    res = (a || b);
    res = !a;
}

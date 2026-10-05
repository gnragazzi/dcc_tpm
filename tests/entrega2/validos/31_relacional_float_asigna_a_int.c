# Expectativa: compilacion limpia, 0 errores semanticos #
# Prueba: resultado de un operador relacional entre floats asignado a un int (el resultado es int) #

void main(){
    float a, b;
    int res;
    a = 1.0;
    b = 2.0;
    res = (a == b);
}

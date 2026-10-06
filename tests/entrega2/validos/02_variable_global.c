# Expectativa: compilacion limpia, 0 errores semanticos #
# Prueba: uso de una variable global dentro de main #

int a, c;

void main(){
    int b, a = 1;
    c = 2;
}

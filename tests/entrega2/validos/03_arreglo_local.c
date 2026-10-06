# Expectativa: compilacion limpia, 0 errores semanticos #
# Prueba: declaracion y uso de un arreglo local con inicializador #

void main(){
    int a, b[1] = {0};
    
    a = b[0] + 1;
}

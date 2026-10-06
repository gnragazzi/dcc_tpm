# Expectativa: compilacion limpia, 0 errores semanticos #
# Prueba: arreglo global con indice fuera de rango (no se chequea en semantico) #

int a[] = {1,2,3};

void main(){
    int b = 1;
    a[0] = b; 
}

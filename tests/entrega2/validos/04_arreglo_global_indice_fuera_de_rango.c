# Expectativa: compilacion limpia, 0 errores semanticos #
# Prueba: arreglo global con indice fuera de rango (no se chequea en semantico) #

int a[] = {1,2,3};

void main(){
    int b = a[4] + 1; // no chequeamos (en análisis semántico) que el índice esté entre 0 y n-1
}

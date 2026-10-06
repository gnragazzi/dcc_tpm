# Expectativa: compilacion limpia, 0 errores semanticos #
# Prueba: main como procedimiento sin parametros, declarado despues de otra funcion #

int fun(){
    return 1;
}

void main(){
    int a;
    a = fun();
}

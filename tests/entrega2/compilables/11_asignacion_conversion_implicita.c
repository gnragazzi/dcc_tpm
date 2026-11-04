# Expectativa: compilacion limpia, 0 errores semanticos #
# Prueba: asignaciones con conversion implicita permitida (char a float, int a float, char a int) #

void main(){
    char caracter;
    int entero;
    float flotante;

    flotante = caracter;
    flotante = entero;
    entero = caracter;
}

# Expectativa: compilacion limpia, 0 errores semanticos #
# Prueba: retorno con coercion permitida (char a int, char a float, int a float) #

int fi(char a){
    return a;
}

float fc(char a){
    return a;
}

float ff(int a){
    return a;
}

void main(){}

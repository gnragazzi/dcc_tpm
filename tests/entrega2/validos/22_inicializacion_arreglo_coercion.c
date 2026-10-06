# Expectativa: compilacion limpia, 0 errores semanticos #
# Prueba: inicializacion de arreglo con valores coercionables al tipo del arreglo (char a int, char a float, int a float) #

int a[2] = {1, 'a'};
float b[3] = {1, 'a', 2.5};
char c[2] = {'a', 'b'};

void main(){
    float d[2] = {1, 'a'};
}

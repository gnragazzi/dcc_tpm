# Expectativa: Error 62: Simbolo inesperado o falta simb. al comienzo de constante, #
# Error 77: El tipo de los valores inicializadores del arreglo debe coincidir con su declaracion #
# Prueba: el 77 por la posicion vacia se reporta aunque el resto de los valores sea coercionable #
# al tipo base (char e int a float) #

void main() {
    float f[3] = {'a', , 2};
}

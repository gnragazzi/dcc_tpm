# Expectativa: Error 83 (char inicializado con float); Errores 81, 94 y 83 (string asignado a arreglo) #
# Prueba: chequeo de tipos en la inicializacion de una variable simple y constante string fuera de #
# una proposicion de E/S en el lado derecho de una asignacion (devolucion 2da entrega, punto 6) #

void main(){
    char c = 3.14;
    char str[20];
    str = "no es string";
}

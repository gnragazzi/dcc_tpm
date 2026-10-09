# Expectativa: Error 17: Falta identificador #
# Prueba: parametro formal sin identificador; se da de alta igual en la lista de parametros de f #
# y la llamada con la cantidad y el tipo correctos no reporta errores (devolucion 2da entrega, punto 1) #

int f(int) {
    return 1;
}

void main() {
    int a;
    a = f(3);
}

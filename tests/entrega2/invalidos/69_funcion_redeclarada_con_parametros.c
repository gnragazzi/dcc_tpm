# Expectativa: Error 72: Identificador ya declarado #
# Prueba: los parametros de una funcion redeclarada no se agregan a la firma de la primera #
# declaracion, que es la que queda en TS: la llamada con un solo int es correcta #

int f(int a) { return a; }

int f(float b, int c) { return 1; }

void main() {
    int x;
    x = f(3);
}

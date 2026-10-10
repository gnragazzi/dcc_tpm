# Expectativa: Error 20: Falta (, Error 21: Falta ) #
# Prueba: llamada a una funcion sin parametros escrita sin parentesis; solo se reportan los #
# parentesis faltantes, el + 1 sigue siendo parte de la expresion (devolucion 2da entrega, punto 3) #

int fun() { return 3; }

void main() {
    int x;
    x = fun + 1;
}

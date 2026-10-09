# Expectativa: Error 20: Falta (, Error 90: La CANTIDAD de parametros actuales no coincide con la #
# cantidad de parametros formales, Error 21: Falta ) #
# Prueba: llamada sin parentesis a una funcion que si tiene parametros: ademas de los parentesis, #
# falta el parametro actual #

int g(int a) { return a; }

void main() {
    int x;
    x = g + 1;
}

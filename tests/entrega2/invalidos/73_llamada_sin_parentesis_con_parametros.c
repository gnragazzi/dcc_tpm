# Expectativa: Error 20: Falta (, Error 21: Falta ) #
# Prueba: llamada sin parentesis a una funcion que si tiene parametros: sin el (, la llamada esta #
# mal formada y no se chequea la cantidad de parametros; solo se informan los parentesis #
# faltantes #

int g(int a) { return a; }

void main() {
    int x;
    x = g + 1;
}

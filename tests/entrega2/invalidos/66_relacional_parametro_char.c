# Expectativa: Error 91: El TIPO de los parametros actuales no coincide con el de los parametros formales #
# Prueba: resultado de un operador relacional (int) como parametro actual de un formal char #

void f(char a){}

void main(){
    float x, y;
    f(x != y);
}

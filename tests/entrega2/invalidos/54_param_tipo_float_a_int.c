# Expectativa: Error 91: El TIPO de los parametros actuales no coincide con el de los parametros formales #
# Prueba: parametro actual float para un formal int #

void f(int a){}

void main(){
    f(1.5);
}

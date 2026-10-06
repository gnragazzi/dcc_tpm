# Expectativa: Error 91: El TIPO de los parametros actuales no coincide con el de los parametros formales #
# Prueba: parametros actuales en distinto orden que los formales (el primero es float para un formal int) #

void f(int a, float b){}

void main(){
    f(1.5, 2);
}

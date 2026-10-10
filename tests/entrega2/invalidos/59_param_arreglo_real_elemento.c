# Expectativa: Error 91: El TIPO de los parametros actuales no coincide con el de los parametros formales #
# Prueba: elemento de arreglo como parametro actual de un formal arreglo: es una variable de tipo int, no un arreglo (devolucion 2da entrega, punto 7) #

void f(int a[]){}

void main(){
    int v[2];
    f(v[0]);
}

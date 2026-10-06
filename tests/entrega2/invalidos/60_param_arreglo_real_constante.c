# Expectativa: Error 98: Si el parametro formal es un arreglo, en el parametro real solo debe haber un identificador #
# Prueba: constante como parametro actual de un formal arreglo #

void f(int a[]){}

void main(){
    f(1);
}

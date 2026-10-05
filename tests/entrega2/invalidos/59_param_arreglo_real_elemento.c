# Expectativa: Error 98: Si el parametro formal es un arreglo, en el parametro real solo debe haber un identificador #
# Prueba: elemento de arreglo como parametro actual de un formal arreglo #

void f(int a[]){}

void main(){
    int v[2];
    f(v[0]);
}

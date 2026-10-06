# Expectativa: Error 93: Si el pasaje es por REFERENCIA, el parametro real debe ser una variable #
# Prueba: constante como parametro actual de un formal por referencia #

void f(int & a){}

void main(){
    f(1);
}

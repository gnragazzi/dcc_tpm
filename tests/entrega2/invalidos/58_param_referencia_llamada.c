# Expectativa: Error 93: Si el pasaje es por REFERENCIA, el parametro real debe ser una variable #
# Prueba: llamada a funcion como parametro actual de un formal por referencia #

int g(){
    return 1;
}

void f(int & a){}

void main(){
    f(g());
}

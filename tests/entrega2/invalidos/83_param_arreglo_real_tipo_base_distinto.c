# Expectativa: Error 91: El TIPO de los parametros actuales no coincide con el de los parametros formales #
# Prueba: arreglo como parametro actual de un formal arreglo con distinto tipo base #

void proc(int a [ ]){ }

void main( ){
    float c[2];
    proc(c);
}

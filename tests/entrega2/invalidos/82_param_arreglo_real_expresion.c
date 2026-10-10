# Expectativa: Error 98 en cada llamada #
# Prueba: expresiones que no son un identificador como parametro actual de un formal arreglo #

void proc(int a [ ]){ }

void main( ){
    int a;
    int b[3];
    proc(a + 1);
    proc((b));
}

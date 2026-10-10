# Expectativa: Error 91 en proc(a) y en proc(b[1]); proc(b) es correcto #
# Prueba: variable simple y elemento de arreglo como parametro actual de un formal arreglo: hay #
# un identificador, pero de tipo distinto al formal (devolucion 2da entrega, punto 7) #

void proc(int a [ ]){ }

void main( ){
    int a;
    int b[3];
    proc(a);
    proc(b);
    proc(b[1]);
}

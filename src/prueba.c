# Expectativa: Error 71: Identificador no declarado #
# Prueba: variable declarada en un bloque interno usada fuera de el #

void main(){
    int x;
    {
        int a = 0;
    }
    x = a;
}


***

void main(){
    int a;
    a[0] = 1;
}

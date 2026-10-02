# Expectativa: Error 71: Identificador no declarado #
# Prueba: llamada a funcion declarada despues y variable local de main usada en ella #

void main(){
    int a;
    fun();
}

int fun(){
    a = 1;
}

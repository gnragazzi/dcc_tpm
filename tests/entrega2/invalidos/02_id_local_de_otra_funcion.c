# Expectativa: Error 71: Identificador no declarado #
# Prueba: variable local de main usada en otra funcion #

int fun(){
    a = 1;
}

void main(){
    int a;
    fun();
}

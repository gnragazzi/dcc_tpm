# Expectativa: Error 91: El TIPO de los parametros actuales no coincide con el de los parametros formales #
# Prueba: constante string como parametro actual #

int fun(int a){
    return 1;
}

void main(){
    fun("1");
}

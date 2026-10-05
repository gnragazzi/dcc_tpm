# Expectativa: Error 97: Las condiciones de las prop. de seleccion e iteracion solo pueden ser de tipo char, int y float #
# Prueba: constante string como condicion de if #

void main(){
    int x = 0;
    if("a")
        x = x + 1;
}

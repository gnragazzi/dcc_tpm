# Expectativa: Error 97: Las condiciones de las prop. de seleccion e iteracion solo pueden ser de tipo char, int y float #
# Prueba: llamada a funcion void en la condicion de if #

void fun(){}

void main(){
    int i;

    if (fun())
        i = 1;
}

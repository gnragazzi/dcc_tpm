# Expectativa: Error 82: En el lado izquierdo de una asignacion debe haber una variable #
# Prueba: llamada a funcion en el lado izquierdo de una asignacion #

int fun(){}

void main(){
    int a, b;
    fun() = 1;
}

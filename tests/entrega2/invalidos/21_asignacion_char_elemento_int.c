# Expectativa: Error 83: Los tipos de ambos lados de la asignacion deben ser estructuralmente equivalentes #
# Prueba: asignacion de un elemento de arreglo int a char #

void main(){
    char caracter;
    int entero[3];
    float flotante;

    caracter = entero[1];
}

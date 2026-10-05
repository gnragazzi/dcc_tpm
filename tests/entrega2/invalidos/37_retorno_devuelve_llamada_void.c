# Expectativa: Error 87: El tipo del valor de retorno no coincide con el tipo de la funcion #
# Prueba: funcion int que retorna una llamada a un procedimiento #

void proc(){}

int fun(){
    return proc();
}

void main(){}

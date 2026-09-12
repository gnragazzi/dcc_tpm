# Expectativa: Error 17: Falta identificador, Error 45: Simbolo inesperado despues de declarar un parametro #
# Prueba: ] suelto tras el especificador de tipo. Con [ y ] en el folset, especificador tipo frena en el ] y el error lo reporta el nivel correcto #

void f(int ] , int b)
{
}

void main()
{
}

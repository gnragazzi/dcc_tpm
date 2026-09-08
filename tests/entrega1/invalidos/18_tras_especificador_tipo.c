# Expectativa: Error 42: Simbolo inesperado despues de especificador de tipo #
# Prueba: operador binario inmediatamente despues del especificador de tipo. Cubre el especificador_tipo (test 42): sin ese test la suite no detecta su ausencia. #

int + a;
void main()
{
}

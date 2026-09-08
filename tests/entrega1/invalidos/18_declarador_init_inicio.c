# Expectativa: Error 47: Simbolo inesperado al comienzo de declarador init #
# Prueba: simbolo invalido al comienzo del declarador init, en declaracion local. Cubre el declarador_init (test 47): sin ese test la suite no detecta su ausencia. #

void main()
{
    int a * ;
}

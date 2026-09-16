# Expectativa: Error 61: Simbolo inesperado despues de llamada a funcion #
# Prueba: simbolo invalido despues de una invocacion a funcion. Cubre el llamada_funcion (test 61): sin ese test la suite no detecta su ausencia. #

void fop(int x)
{
}
void main()
{
    int a;
    a = fop(a) ] ;
}

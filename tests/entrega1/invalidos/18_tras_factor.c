# Expectativa: Error 58: Simbolo inesperado despues de factor #
# Prueba: simbolo invalido despues de una expresion parentizada usada como factor. Cubre el factor (test 58): sin ese test la suite no detecta su ausencia. #

void main()
{
    int a;
    int b;
    a = (b) ] ;
}

# Expectativa: Error 52: Simbolo inesperado o falta simb. al comienzo de proposicion #
# Prueba: Separador coma no perteneciente a FIRST(proposicion) en cuerpo de if #

void main()
{
    int a;
    a = 1;
    if(a > 0)
        , a = 5;
}

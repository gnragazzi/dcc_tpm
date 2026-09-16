# Expectativa: Error 46: Simbolo inesperado o falta simb. al comienzo de lista decl. init, luego Error 17: Falta identificador #
# Prueba: Omisión de identificador en declaración local de variable. Devolución punto 4: #
# lista_declaraciones_init ahora lleva test inicial y lo reporta antes que el match(CIDENT) #

void main()
{
    int ;
}

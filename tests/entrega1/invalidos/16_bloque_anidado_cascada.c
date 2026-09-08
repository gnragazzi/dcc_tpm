# Expectativa: Error 52: Simbolo inesperado o falta simb. al comienzo de proposicion #
# Prueba: un unico simbolo intruso en el bloque mas interno de cinco anidados. Con el test #
# intermedio de proposicion_compuesta: un error. Sin el, el desfasaje de llaves suma un error #
# por cada nivel de anidamiento. Consignas 13 y 14. #

void main()
{
    {
        {
            {
                {
                    * int a;
                }
            }
        }
    }
}

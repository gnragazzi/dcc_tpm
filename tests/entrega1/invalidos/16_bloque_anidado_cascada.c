# Expectativa: cascada de un error de } (25) por cada nivel de anidamiento (5), más un error 51 final #
# Prueba: un unico simbolo intruso en el bloque mas interno de cinco anidados. Devolución punto 4: #
# sin el test intermedio de proposicion_compuesta (eliminado), el desfasaje de llaves suma un error #
# por cada nivel de anidamiento en lugar de uno solo. Consignas 13 y 14. #

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

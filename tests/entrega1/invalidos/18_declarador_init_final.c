# Expectativa: Errores 22, 48 en ese orden #
# Prueba: simbolo invalido tras el limite del arreglo en el declarador init. Cubre el declarador_init (test 48): sin ese test la suite no detecta su ausencia. #

int a[ 3 * ] ;
void main()
{
}

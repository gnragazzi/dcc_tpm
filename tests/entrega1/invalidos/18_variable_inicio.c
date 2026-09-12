# Expectativa: Errores 59, 17, 23 en ese orden #
# Prueba: constante donde se espera una variable, en una proposicion de entrada. Cubre el variable (test 59): sin ese test la suite no detecta su ausencia. El test no reconfigura (la constante ya esta en el folset heredado), asi que match(ident) reporta la ausencia del identificador sobre el mismo token. #

void main()
{
    int x;
    cin >> 5;
}

# Expectativa: Errores 59, 17 en ese orden #
# Prueba: falta el identificador de la variable y el test reconfigura al corchete, que es punto interno de variable. Cubre la otra mitad del match(ident): la cadena reconfigurada deja un lookahead que no es identificador y match reporta su ausencia antes de que el cuerpo procese el subindice. #

void main()
{
    int x;
    cin >> [x];
}

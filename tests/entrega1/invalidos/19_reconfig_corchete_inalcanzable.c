# Expectativa: cascada desde el test final de declaracion (falta ;) #
# Prueba: omision del corchete de apertura con el limite del arreglo escrito. El #
# lookahead del test inicial es cons_ent, que pertenece al folset heredado por F_PROPOSICION #
# (via F_PROPOSICION_EXPRESION), de modo que el test pasa en silencio y el switch resuelve #
# la derivacion vacia: el ] no llega a ser lookahead del test inicial y la deteccion queda #
# en el match(CPYCOMA, 23) de declaracion. #

void main()
{
    int a 3] = {1, 2};
}

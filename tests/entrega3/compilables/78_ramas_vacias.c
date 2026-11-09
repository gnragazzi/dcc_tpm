# Expectativa: imprime bd #
# Prueba: la proposicion vacia es una rama valida #

void main()
{
    if (1) ; else cout << "a";
    if (0) ;
    cout << "b";
    if (0) cout << "c"; else ;
    cout << "d";
}

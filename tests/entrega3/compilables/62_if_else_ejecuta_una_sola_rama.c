# Expectativa: imprime ad #
# Prueba: con else se ejecuta exactamente una de las dos ramas #

void main()
{
    if (1) cout << "a"; else cout << "b";
    if (0) cout << "c"; else cout << "d";
}

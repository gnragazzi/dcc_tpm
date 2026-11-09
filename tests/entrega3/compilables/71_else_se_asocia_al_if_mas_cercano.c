# Expectativa: imprime bf #
# Prueba: if anidados sin llaves: el else pertenece al if mas cercano #

void main()
{
    if (1) if (0) cout << "a"; else cout << "b";
    if (0) if (1) cout << "c"; else cout << "d";
    if (0) { if (1) cout << "e"; } else cout << "f";
}

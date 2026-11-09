# Requiere V3 (asignacion), V4 (relacionales) y V5 (while) #
# Expectativa: imprime 5000 sin desbordar la pila de ejecucion #
# Prueba: un bloque con declaraciones dentro de un while se ejecuta miles de veces; la memoria de cada vuelta se tiene que liberar #

void main()
{
    int i = 0;
    while (i < 5000) {
        int x = 1;
        i = i + x;
    }
    cout << i;
}
